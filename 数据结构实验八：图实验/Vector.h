//
// Created by Twiliness on 2019/11/12.
//

#ifndef CGO_VECTOR_H
#define CGO_VECTOR_H

#include <cstddef>
#include <memory>
#include <type_traits>

template <typename T, class Alloc = std::allocator<T>> struct Vector {
  using atraits = std::allocator_traits<Alloc>;

public:
  using allocator_type = Alloc;
  using value_type = typename atraits::value_type;
  using size_type = typename atraits::size_type;
  using difference_type = typename atraits::difference_type;
  using reference = T &;
  using const_reference = const T &;
  using pointer = typename atraits::pointer;
  using const_pointer = typename atraits::const_pointer;
  using iterator = pointer;
  using const_iterator = const_pointer;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  Vector() : Vector(Alloc()) {}

  Vector(const Alloc &alloc) : m_capacity(0), m_alloc(alloc) {
    m_begin = m_end = nullptr;
  }

  explicit Vector(size_t count, const Alloc &alloc = Alloc()) : Vector(alloc) {
    resize(count);
  }

  explicit Vector(size_t count, const T &value, const Alloc &alloc = Alloc())
      : Vector(alloc) {
    assign_impl(count, value);
  }

  template <class InputIterator,
            typename = decltype(*std::declval<InputIterator>())>
  Vector(InputIterator first, InputIterator last, const Alloc &alloc = Alloc())
      : Vector(alloc) {
    assign_impl(first, last);
  }

  Vector(std::initializer_list<T> l, const Alloc &alloc = Alloc())
      : Vector(alloc) {
    assign_impl(l);
  }

  Vector(const Vector &v)
      : Vector(v, atraits::select_on_container_copy_construction(
                      v.get_allocator())) {}

  Vector(const Vector &v, const Alloc &alloc) : Vector(alloc) {
    assign_impl(v.begin(), v.end());
  }

  Vector(Vector &&v)
      : m_capacity(v.m_capacity), m_alloc(std::move(v.m_alloc)),
        m_begin(v.m_begin), m_end(v.m_end) {
    v.m_begin = v.m_end = nullptr;
    v.m_capacity = 0;
  }

  ~Vector() {
    clear();

    if (m_begin) {
      atraits::deallocate(m_alloc, m_begin, m_capacity);
    }
  }

  Vector &operator=(const Vector &v) {
    if (this == &v) {
      // prevent self usurp
      return *this;
    }

    clear();

    assign_impl(v.begin(), v.end());

    return *this;
  }

  Vector &operator=(Vector &&v) {
    clear();

    m_alloc = std::move(v.m_alloc);
    m_capacity = v.m_capacity;
    m_begin = v.m_begin;
    m_end = v.m_end;

    v.m_begin = v.m_end = nullptr;
    v.m_capacity = 0;

    return *this;
  }

  void assign(size_type count, const T &value) {
    clear();
    assign_impl(count, value);
  }

  template <class InputIterator,
            typename = decltype(*std::declval<InputIterator>())>
  void assign(InputIterator first, InputIterator last) {
    clear();
    assign_impl(first, last);
  }

  void assign(std::initializer_list<T> ilist) {
    clear();
    assign_impl(ilist);
  }

  allocator_type get_allocator() const { return m_alloc; }

  const_reference at(size_type i) const { return *(m_begin + i); }

  reference at(size_type i) { return *(m_begin + i); }

  const_reference operator[](size_type i) const { return at(i); }

  reference operator[](size_type i) { return at(i); }

  const_reference front() const { return at(0); }

  reference front() { return at(0); }

  const_reference back() const { return *(m_end - 1); }

  reference back() { return *(m_end - 1); }

  const_pointer data() const noexcept { return m_begin; }

  pointer data() noexcept { return m_begin; }

  // iterators
  iterator begin() noexcept { return m_begin; }

  const_iterator begin() const noexcept { return m_begin; }

  const_iterator cbegin() const noexcept { return m_begin; }

  iterator end() noexcept { return m_end; }

  const_iterator end() const noexcept { return m_end; }

  const_iterator cend() const noexcept { return m_end; }

  int * rbegin() noexcept { return reverse_iterator(end()); }

  const_reverse_iterator rbegin() const noexcept {
    return const_reverse_iterator(end());
  }

  const_reverse_iterator crbegin() const noexcept {
    return const_reverse_iterator(end());
  }

  reverse_iterator rend() noexcept { return reverse_iterator(begin()); }

  const_reverse_iterator rend() const noexcept {
    return const_reverse_iterator(begin());
  }

  const_reverse_iterator crend() const noexcept {
    return const_reverse_iterator(begin());
  }

  // capacity
  bool empty() const noexcept { return m_begin == m_end; }

  size_t size() const noexcept { return m_end - m_begin; }

  size_t max_size() const noexcept { return m_alloc.max_size(); }

  void reserve(size_t desired_capacity) {
    if (desired_capacity <= m_capacity) {
      return;
    }

    size_type new_cap = find_capacity(desired_capacity);

    auto new_buf = atraits::allocate(m_alloc, new_cap);
    const auto s = size();

    // now we need to transfer the existing elements into the new buffer
    for (size_type i = 0; i < s; ++i) {
      atraits::construct(m_alloc, new_buf + i, std::move(*(m_begin + i)));
    }

    if (m_begin) {
      // free old elements
      for (size_type i = 0; i < s; ++i) {
        atraits::destroy(m_alloc, m_begin + i);
      }

      atraits::deallocate(m_alloc, m_begin, m_capacity);
    }

    m_begin = new_buf;
    m_end = new_buf + s;
    m_capacity = new_cap;
  }

  size_t capacity() const noexcept { return m_capacity; }

  void shrink_to_fit() {
    const auto s = size();

    if (s == m_capacity)
      return;

    if (s == 0) {
      atraits::deallocate(m_alloc, m_begin, m_capacity);
      m_capacity = 0;
      m_begin = m_end = nullptr;
      return;
    }

    auto new_buf = atraits::allocate(m_alloc, s);

    // now we need to transfer the existing elements into the new buffer
    for (size_type i = 0; i < s; ++i) {
      atraits::construct(m_alloc, new_buf + i, std::move(*(m_begin + i)));
    }

    // free old elements
    for (size_type i = 0; i < s; ++i) {
      atraits::destroy(m_alloc, m_begin + i);
    }

    atraits::deallocate(m_alloc, m_begin, m_capacity);

    m_begin = new_buf;
    m_end = new_buf + s;
    m_capacity = s;
  }

  // modifiers
  void clear() noexcept {
    for (auto p = m_begin; p != m_end; ++p) {
      atraits::destroy(m_alloc, p);
    }

    m_end = m_begin;
  }

  iterator insert(const_iterator position, const value_type &val) {
    auto pos = grow_at(position, 1);
    atraits::construct(m_alloc, pos, val);
    return pos;
  }

  iterator insert(const_iterator position, value_type &&val) {
    auto pos = grow_at(position, 1);
    atraits::construct(m_alloc, pos, std::move(val));
    return pos;
  }

  iterator insert(const_iterator position, size_type count,
                  const value_type &val) {
    auto pos = grow_at(position, count);
    for (size_type i = 0; i < count; ++i) {
      atraits::construct(m_alloc, pos + i, val);
    }
    return pos;
  }

  template <typename InputIterator,
            typename = decltype(*std::declval<InputIterator>())>
  iterator insert(const_iterator position, InputIterator first,
                  InputIterator last) {
    auto pos = grow_at(position, last - first);
    size_type i = 0;
    auto np = pos;
    for (auto p = first; p != last; ++p, ++np) {
      atraits::construct(m_alloc, np, *p);
    }
    return pos;
  }

  iterator insert(const_iterator position, std::initializer_list<T> ilist) {
    auto pos = grow_at(position, ilist.size());
    size_type i = 0;
    for (auto &elem : ilist) {
      atraits::construct(m_alloc, pos + i, elem);
      ++i;
    }
    return pos;
  }

  template <typename... Args>
  iterator emplace(const_iterator position, Args &&... args) {
    auto pos = grow_at(position, 1);
    atraits::construct(m_alloc, pos, std::forward<Args>(args)...);
    return pos;
  }

  iterator erase(const_iterator position) { return shrink_at(position, 1); }

  iterator erase(const_iterator first, const_iterator last) {
    return shrink_at(first, last - first);
  }

  void push_back(const_reference val) {
    auto pos = grow_at(m_end, 1);
    atraits::construct(m_alloc, pos, val);
  }

  void push_back(T &&val) {
    auto pos = grow_at(m_end, 1);
    atraits::construct(m_alloc, pos, std::move(val));
  }

  template <typename... Args> void emplace_back(Args &&... args) {
    auto pos = grow_at(m_end, 1);
    atraits::construct(m_alloc, pos, std::forward<Args>(args)...);
  }

  void pop_back() { shrink_at(m_end - 1, 1); }

  void resize(size_type n, const value_type &v) {
    if (n <= m_capacity) {
      const auto new_end = m_begin + n;

      while (m_end > new_end) {
        atraits::destroy(m_alloc, --m_end);
      }

      while (new_end > m_end) {
        atraits::construct(m_alloc, m_end++, v);
      }
    } else {
      reserve(n);

      const auto new_end = m_begin + n;

      while (new_end > m_end) {
        atraits::construct(m_alloc, m_end++, v);
      }
    }
  }

  void resize(size_type n) {
    if (n <= m_capacity) {
      const auto new_end = m_begin + n;

      while (m_end > new_end) {
        atraits::destroy(m_alloc, --m_end);
      }

      while (new_end > m_end) {
        atraits::construct(m_alloc, m_end++);
      }
    } else {
      reserve(n);

      const auto new_end = m_begin + n;

      while (new_end > m_end) {
        atraits::construct(m_alloc, m_end++);
      }
    }
  }

private:
  size_type find_capacity(size_type desired_capacity) const {
    if (m_capacity == 0) {
      return desired_capacity;
    } else {
      auto new_cap = m_capacity;

      while (new_cap < desired_capacity) {
        // grow by roughly 1.5
        new_cap *= 3;
        ++new_cap;
        new_cap /= 2;
      }

      return new_cap;
    }
  }

  // increase the size by splicing the elements in such a way that
  // a hole of uninitialized elements is left at position, with size num
  // returns the (potentially new) address of the hole
  T *grow_at(const T *cp, size_t num) {
    auto position = const_cast<T *>(cp);

    const auto s = size();

    if (s + num <= m_capacity) {
      m_end = m_begin + s + num;

      for (auto p = m_end - num - 1; p >= position; --p) {
        atraits::construct(m_alloc, p + num, std::move(*p));
        atraits::destroy(m_alloc, p);
      }

      return position;
    } else {
      // we need to transfer the elements into the a buffer
      size_type new_cap = find_capacity(s + num);

      auto new_buf = atraits::allocate(m_alloc, new_cap);

      position = new_buf + (position - m_begin);

      auto p = m_begin;
      auto np = new_buf;

      for (; np != position; ++p, ++np) {
        atraits::construct(m_alloc, np, std::move(*p));
      }

      np += num;
      for (; p != m_end; ++p, ++np) {
        atraits::construct(m_alloc, np, std::move(*p));
      }

      // destroy old
      if (m_begin) {
        for (p = m_begin; p != m_end; ++p) {
          atraits::destroy(m_alloc, p);
        }

        atraits::deallocate(m_alloc, m_begin, m_capacity);
      }

      m_capacity = new_cap;
      m_begin = new_buf;
      m_end = new_buf + s + num;

      return position;
    }
  }

  T *shrink_at(const T *cp, size_t num) {
    auto position = const_cast<T *>(cp);

    const auto s = size();
    if (s - num == 0) {
      clear();
      return m_end;
    }

    for (auto p = position, np = position + num; np != m_end; ++p, ++np) {
      atraits::destroy(m_alloc, p);
      atraits::construct(m_alloc, p, std::move(*np));
    }

    for (auto p = m_end - num; p != m_end; ++p) {
      atraits::destroy(m_alloc, p);
    }

    m_end -= num;

    return ++position;
  }

  // grows buffer only on empty vectors
  void safe_grow(size_t capacity) {
    if (capacity <= m_capacity)
      return;

    if (m_begin) {
      atraits::deallocate(m_alloc, m_begin, m_capacity);
    }

    m_capacity = find_capacity(capacity);
    m_begin = m_end = atraits::allocate(m_alloc, m_capacity);
  }

  void assign_impl(size_type count, const T &value) {
    safe_grow(count);

    for (size_type i = 0; i < count; ++i) {
      atraits::construct(m_alloc, m_end, value);
      ++m_end;
    }
  }

  template <class InputIterator>
  void assign_impl(InputIterator first, InputIterator last) {
    auto isize = last - first;
    safe_grow(isize);

    for (auto p = first; p != last; ++p) {
      atraits::construct(m_alloc, m_end, *p);
      ++m_end;
    }
  }

  void assign_impl(std::initializer_list<T> ilist) {
    safe_grow(ilist.size());

    for (auto &elem : ilist) {
      atraits::construct(m_alloc, m_end, elem);
      ++m_end;
    }
  }

  pointer m_begin;
  pointer m_end;

  size_t m_capacity;

  Alloc m_alloc;
};

template <typename T, class Alloc>
bool operator==(const Vector<T, Alloc> &a, const Vector<T, Alloc> &b) {
  if (a.size() != b.size())
    return false;

  for (size_t i = 0; i < a.size(); ++i)
    if (a[i] != b[i])
      return false;

  return true;
}

template <typename T, class Alloc>
bool operator!=(const Vector<T, Alloc> &a, const Vector<T, Alloc> &b) {
  if (a.size() != b.size())
    return true;

  for (size_t i = 0; i < a.size(); ++i)
    if (a[i] != b[i])
      return true;

  return false;
}

#endif // CGO_VECTOR_H
