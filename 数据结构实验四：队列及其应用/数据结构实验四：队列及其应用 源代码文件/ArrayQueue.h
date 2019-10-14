//
// Created by Zfans on 2019/09/28.
//

#ifndef ARRAYQUEUE_ARRAYQUEUE_H
#define ARRAYQUEUE_ARRAYQUEUE_H

using namespace std;

const int defaultSize = 64;

template<class T>
class ArrayQueue {
private:
    T *Arr;     //存放数据的数组
    int begin;
    int end;
    int maxSize;    //最大容量
public:
    ArrayQueue();

    ~ArrayQueue();

    bool push(T x);//入队
    bool pop();//出队
    bool empty();//判空
    unsigned int size(); //大小
    T front();//取队首
    T back();//取队尾
    bool ExpansionCapacity();     //扩展容量
    void PrintBinomialCoefficients(int n);//打印二项式系数
};

template<class T>
ArrayQueue<T>::ArrayQueue() {
    begin = 0;
    end = 0;
    maxSize = defaultSize;
    Arr = new T[defaultSize];
    if (!Arr) {
        cerr << "Arr malloc error!" << endl;
    }
}

template<class T>
ArrayQueue<T>::~ArrayQueue() {
    if (Arr) {
        delete[]Arr;
        Arr = NULL;
    }
}

template<class T>
bool ArrayQueue<T>::empty() {
    if (begin == end)
        return true;
    return false;
}

template<class T>
unsigned int ArrayQueue<T>::size() {
    return (end - begin + maxSize) % maxSize;
}

template<class T>
bool ArrayQueue<T>::push(T x) {
    if ((end + 1) % maxSize == begin)
        ExpansionCapacity();
    Arr[end] = x;
    end = (end + 1) % maxSize;
    return true;
}

template<class T>
bool ArrayQueue<T>::ExpansionCapacity() {
    T *newArr = new T[maxSize + defaultSize];
    if (!newArr) {
        cerr << "Arr malloc error!" << endl;
    }
    maxSize += defaultSize;
    unsigned int length = size();
    T *p = newArr;
    while (!empty()) {
        *p++ = front();
        pop();
    }
    begin = 0;
    end = length;
    delete[] Arr;
    Arr = newArr;
    return true;
}

template<class T>
bool ArrayQueue<T>::pop() {
    if (empty())
        return false;
    begin = (begin + 1) % maxSize;
    return true;
}

template<class T>
T ArrayQueue<T>::front() {
    if (empty())
        return false;
    return Arr[begin];
}

template<class T>
T ArrayQueue<T>::back() {
    if (empty())
        return false;
    return Arr[end - 1];
}

template<class T>
void ArrayQueue<T>::PrintBinomialCoefficients(int n) {
    int **arr = new int *[n];
    for (int l = 0; l < n; ++l) {
        arr[l] = new int[n];
    }
    for (int i = 0; i < n; i++) {
        arr[i][0] = 1;
        arr[i][i] = 1;
    }
    for (int i = 2; i < n; i++) {
        for (int j = 1; j < i; j++) {
            arr[i][j] = arr[i - 1][j - 1] + arr[i - 1][j];
        }
    }
    string maxNum = to_string(arr[n - 1][n / 2]);
    string maxNumLengthSpace;
    for (int m = 0; m < maxNum.length(); m++) {
        maxNumLengthSpace += " ";
    }

    int i = 1, j, s = 0, k = 0, t, u;
    push(i);
    push(i);
    for (; i <= n; i++) {
        if (i != 1)
            cout << endl;
        for (int space = n - i; space > 0; space--) {
            cout << maxNumLengthSpace << " ";
        }
        push(k);
        for (j = 1; j <= i + 2; j++) {
            t = front();
            pop();
            u = s + t;
            push(u);
            s = t;
            string num = to_string(s);
            string moreNumLengthSpace;
            for (int a = 0; a <= (maxNum.length() - num.length()); a++) {
                moreNumLengthSpace += " ";
            }
            if (j != i + 2)
                cout << s << maxNumLengthSpace << moreNumLengthSpace << " ";
        }
    }
    for (int i1 = 0; i1 < n; ++i1) {
        delete[] arr[i1];
    }
    delete[] arr;
}

#endif //ARRAYQUEUE_ARRAYQUEUE_H
