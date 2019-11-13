//
// Created by Zfans on 2019/11/11.
//

#ifndef GRAPHBYADJACENCYLIST_HEAP_H
#define GRAPHBYADJACENCYLIST_HEAP_H

#include<iostream>

using namespace std;

constexpr auto DefaultSize = 1024;

template<class T>
class MinHeap {
private:
    T *heap;//定义存放元素的数组
    int currentSize;//堆中当前元素个数
    int maxHeapSize;//堆最多存放元素个数
    void siftDown(int start, int m);//从start到m下滑形成最小堆
    void siftUp(int start);//从start到0上滑形成最小堆
public:
    explicit MinHeap(int sz = DefaultSize);//构造函数，建立空堆
    MinHeap(T s[], int n);//构造函数，通过一个数组建堆
    ~MinHeap();//析构函数
    bool Insert(T &x);//插入
    bool Remove(T &x);//删除堆顶的最小元素
    bool IsEmpty();//判断对是否空
    bool IsFull();//判断对是否满
    bool Traverses(ostream &out);//输出
    bool Find(T x);//查找
    void MakeEmpty();//堆置空
    void HeapSort();//小堆堆排序
    friend ostream &operator<<(ostream &out, MinHeap<T> &p) {
        out << "小堆堆的输出：";
        p.Traverses(out);
        out << endl;
        return out;
    }
};

template<class T>
MinHeap<T>::MinHeap(int sz) {//构造函数，建立空堆
    maxHeapSize = sz;
    heap = new T[maxHeapSize];
    if (heap == NULL) {
        cout << "内存分配失败！" << endl;
        return;
    }
    currentSize = 0;
}

template<class T>
MinHeap<T>::MinHeap(T s[], int n) {//构造函数，通过一个数组建堆
    maxHeapSize = (DefaultSize > n) ? DefaultSize : n;
    heap = new T[maxHeapSize];
    if (heap == NULL) {
        cout << "内存分配失败！" << endl;
        return;
    }
    for (int i = 0; i < n; i++) {
        heap[i] = s[i];
    }
    currentSize = n;//当前堆大小
    int currentPos = (currentSize - 2) / 2;//找到最后一个分支结点
    while (currentPos >= 0) {
        siftDown(currentPos, currentSize - 1);
        currentPos--;
    }
}

template<class T>
MinHeap<T>::~MinHeap() {
    delete[]heap;
}

template<class T>
bool MinHeap<T>::IsEmpty() {
    return currentSize == 0;
}

template<class T>
bool MinHeap<T>::IsFull() {
    return currentSize == maxHeapSize;
}

template<class T>
void MinHeap<T>::MakeEmpty() {
    currentSize = 0;
}

template<class T>
bool MinHeap<T>::Traverses(ostream &out) {
    if (currentSize == 0) {
        return false;
    }
    for (int i = 0; i < currentSize; i++) {
        out << heap[i] << " ";
    }
    return true;
}

template<class T>
void MinHeap<T>::siftDown(int start, int m) {//从start到m下滑形成最小堆
    int i = start;
    int j = 2 * i + 1;
    T temp = heap[i];
    while (j <= m) {
        if (j < m && heap[j] > heap[j + 1]) {
            j++;
        }
        if (temp <= heap[j]) {
            break;
        } else {
            heap[i] = heap[j];
            i = j;
            j = 2 * j + 1;
        }
    }
    heap[i] = temp;
}

template<class T>
void MinHeap<T>::siftUp(int start) {//从start到0上滑形成最小堆
    int j = start;
    int i = (start - 1) / 2;
    T temp = heap[j];
    while (j > 0) {
        if (heap[i] <= temp) {
            break;
        } else {
            heap[j] = heap[i];
            j = i;
            i = (i - 1) / 2;
        }
    }
    heap[j] = temp;
}

template<class T>
bool MinHeap<T>::Insert(T &x) {//插入
    if (currentSize == maxHeapSize) {
        cout << "Heap Full!" << endl;
        return false;
    }
    heap[currentSize] = x;
    siftUp(currentSize);
    currentSize++;
    return true;
}

template<class T>
bool MinHeap<T>::Remove(T &x) {//删除堆顶的最小元素
    if (currentSize == 0) {
        cout << "Heap Empty!" << endl;
        return false;
    }
    x = heap[0];
    heap[0] = heap[currentSize - 1];
    currentSize--;
    siftDown(0, currentSize - 1);
    return true;
}

template<class T>
void MinHeap<T>::HeapSort() {//小堆堆排序
    if (currentSize == 0) {
        return;
    }
    T *s = new T[maxHeapSize];
    int num = currentSize;
    T m;
    for (int i = 0; i < num; i++) {
        Remove(s[i]);
    }
    for (int i = 0; i < num; i++) {
        heap[i] = s[i];
    }
    currentSize = num;
}

template<class T>
bool MinHeap<T>::Find(T x) {//查找
    for (int i = 0; i < currentSize; i++) {
        if (x == heap[i]) {
            return true;
        }
    }
    return false;
}


#endif //GRAPHBYADJACENCYLIST_HEAP_H
