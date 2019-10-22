//
// Created by Zfans on 2019/10/13.
//

#ifndef HEAP_HEAP_H
#define HEAP_HEAP_H

#include <iostream>

using namespace std;

const int defaultSize = 1024;

enum HeapType {
    MinHeap, MaxHeap
};

template<class T>
class Heap {

private:

    T *HeapArray; //存放元素的数组
    int Size; //元素个数
    int Capacity;//容量
    int Type;//区分大根堆（1）小根堆（0）
    int getTopTotalCompareCount;

protected:

    void siftUp(int start);//从start到0上滑调整成为最小堆

    void siftDown(int start, int end);//从start到end下滑调整成为最小堆

public:

    Heap();//默认构造函数

    Heap(T *arr, int size);//带参构造函数

    ~Heap();//析构函数

    int getSize() const;//获取元素个数

    int getCapacity() const;//获取容量

    T *getHeapArray() const;//获取数组

    int getType() const;//获取堆类型

    void DisPlayHeap() const;//显示堆

    bool ExpansionCapacity();     //扩展容量

    void makeEmpty();//置空

    bool Insert(const T x); //插入x到最堆中
    bool Remove(); //删除堆顶
    T getTop();//取堆顶
    bool isEmpty() const; //判空
    void HeapSort();//堆排序

    void toMinHeap();//转换为小根堆

    void toMaxHeap();//转换为大根堆

    int getGetTopTotalCompareCount() const;//获取总对比次数
};

template<class T>
int Heap<T>::getSize() const {
    return Size;
}

template<class T>
void Heap<T>::siftDown(int start, int end) {
    int Child = 2 * start + 1; //左孩子
    T Father = HeapArray[start];
    if (Type == MinHeap) {
        while (Child <= end) {
            if (Child < end && HeapArray[Child] > HeapArray[Child + 1])
                Child++;//右孩子
            if (Father <= HeapArray[Child]) {
                getTopTotalCompareCount++;
                break;
            } else {
                getTopTotalCompareCount++;
                HeapArray[start] = HeapArray[Child];
                start = Child;
                Child = 2 * Child + 1; //左孩子
            }
        }
    } else {
        while (Child <= end) {
            if (Child < end && HeapArray[Child] < HeapArray[Child + 1])
                Child++;//右孩子
            if (Father > HeapArray[Child]) {
                getTopTotalCompareCount++;
                break;
            } else {
                getTopTotalCompareCount++;
                HeapArray[start] = HeapArray[Child];
                start = Child;
                Child = 2 * Child + 1; //左孩子
            }
        }
    }
    HeapArray[start] = Father;
}

template<class T>
void Heap<T>::siftUp(int start) {
    int Father = (start - 1) / 2;
    T Child = HeapArray[start];
    if (Type == MinHeap) {
        while (start > 0) {
            if (HeapArray[Father] <= Child)
                break;
            else {
                HeapArray[start] = HeapArray[Father];
                start = Father;
                Father = (Father - 1) / 2;
            }
        }
    } else {
        while (start > 0) {
            if (HeapArray[Father] > Child)
                break;
            else {
                HeapArray[start] = HeapArray[Father];
                start = Father;
                Father = (Father - 1) / 2;
            }
        }
    }
    HeapArray[start] = Child;
}

template<class T>
Heap<T>::Heap(T *arr, int size) {
    Size = size;
    Capacity = defaultSize < Size ? Size : defaultSize;
    Type = 0;
    getTopTotalCompareCount = 0;
    HeapArray = new T[Capacity];
    if (HeapArray == nullptr) {
        cerr << "内存分配错误！" << endl;
        exit(1);
    }
    for (int i = 0; i < Size; ++i)
        HeapArray[i] = arr[i];
    int currentPos = (Size - 2) / 2;
    while (currentPos >= 0) {
        siftDown(currentPos, Size - 1);
        currentPos--;
    }
}

template<class T>
void Heap<T>::DisPlayHeap() const {
    for (int i = 0; i < Size; ++i)
        cout << HeapArray[i] << " ";
}

template<class T>
bool Heap<T>::ExpansionCapacity() {
    T *newHeapArray = new T[Size + defaultSize];
    if (newHeapArray == nullptr) {
        cerr << "内存分配错误！" << endl;
        exit(1);
    }
    Capacity += defaultSize;
    T *srcptr = HeapArray;
    T *destprt = newHeapArray;
    int n = Size;
    while (n--)*destprt++ = *srcptr++;
    delete[] HeapArray;
    HeapArray = newHeapArray;
    return true;
}

template<class T>
int Heap<T>::getCapacity() const {
    return Capacity;
}

template<class T>
void Heap<T>::makeEmpty() {
    delete[] HeapArray;
    Size = 0;
    Capacity = defaultSize;
    Type = 0;
    HeapArray = new T[defaultSize];
    if (HeapArray == nullptr) {
        cerr << "内存分配错误！" << endl;
        exit(1);
    }
}

template<class T>
Heap<T>::~Heap() {
    delete[] HeapArray;
}

template<class T>
Heap<T>::Heap() {
    Size = 0;
    Capacity = defaultSize;
    Type = 0;
    getTopTotalCompareCount = 0;
    HeapArray = new T[defaultSize];
    if (HeapArray == nullptr) {
        cerr << "内存分配错误！" << endl;
        exit(1);
    }
}

template<class T>
bool Heap<T>::isEmpty() const {
    return !Size;
}

template<class T>
bool Heap<T>::Insert(const T x) {
    HeapArray[Size] = x;
    siftUp(Size);
    Size++;
    return true;
}

template<class T>
bool Heap<T>::Remove() {
    HeapArray[0] = HeapArray[Size - 1];
    Size--;
    siftDown(0, Size - 1);
    return true;
}

template<class T>
T *Heap<T>::getHeapArray() const {
    return HeapArray;
}

template<class T>
void Heap<T>::HeapSort() {
    int tempSize = Size;
    T *Temp = new T[tempSize];
    for (int i = 0; i < tempSize; ++i) {
        Temp[i] = HeapArray[0];
        Remove();
    }
    for (int j = 0; j < tempSize; ++j)
        HeapArray[j] = Temp[j];
    Size = tempSize;
    delete[] Temp;
}

template<class T>
void Heap<T>::toMinHeap() {
    Type = MinHeap;
    int currentPos = (Size - 2) / 2;
    while (currentPos >= 0) {
        siftDown(currentPos, Size - 1);
        currentPos--;
    }
}

template<class T>
void Heap<T>::toMaxHeap() {
    Type = MaxHeap;
    int currentPos = (Size - 2) / 2;
    while (currentPos >= 0) {
        siftDown(currentPos, Size - 1);
        currentPos--;
    }
}

template<class T>
int Heap<T>::getType() const {
    return Type;
}

template<class T>
T Heap<T>::getTop() {
    T t = HeapArray[0];
    HeapArray[0] = HeapArray[Size - 1];
    Size--;
    siftDown(0, Size - 1);
    return t;
}

template<class T>
int Heap<T>::getGetTopTotalCompareCount() const {
    return getTopTotalCompareCount;
}

#endif //HEAP_HEAP_H