#include <iostream>
#include <ctime>
#include "Heap.h"

using namespace std;

struct object {
    int value;
    int priority;

    bool operator>(const object &b) const {
        return this->priority > b.priority;
    }

    bool operator<=(const object &b) const {
        return this->priority <= b.priority;
    }

    bool operator<(const object &b) const {
        return this->priority < b.priority;
    }

    friend ostream &operator<<(ostream &out, object &object) {
        out << "priority：" << object.priority << " "
            << "value：" << object.value << endl;
        return out;
    }
};

void SchemeOne(object *arr, int size) {
    cout << "方案一测试：" << endl;
    object *obArr = new object[size];
    for (int i = 0; i < size; ++i) {
        obArr[i] = arr[i];
    }
    int size_t = size, totalCompareCount = 0;
    for (int j = 0; j < size; ++j) {
        int minPriorityObjectIndex = 0;
        for (int i = 0; i < size_t; ++i) {
            if (obArr[minPriorityObjectIndex].priority > obArr[i].priority) {
                swap(obArr[minPriorityObjectIndex], obArr[i]);
                totalCompareCount++;
            }
        }
        //  cout << obArr[minPriorityObjectIndex];
        swap(obArr[minPriorityObjectIndex], obArr[size_t - 1]);
        size_t--;
    }
    cout << "SchemeOne单个对象平均比较次数：" << totalCompareCount / size << endl;
}

void SchemeTwo(object *arr, int size) {
    cout << "方案二测试：" << endl;
    object *obArr = new object[size];
    for (int i = 0; i < size; ++i) {
        obArr[i] = arr[i];
    }
    int totalCompareCount = 0;
    //直接插入排序
    for (int i = 1; i < size; i++) {
        object temp = obArr[i]; // 保存当前位置的值
        int j = i - 1;
        while (j >= 0 && obArr[j].priority > temp.priority) { // 往前找插入的位置
            obArr[j + 1] = obArr[j]; // 往后移
            j--;
            totalCompareCount++;
        }
        obArr[j + 1] = temp;
    }
    for (int k = 0; k < size; ++k) {
        // cout << obArr[k];
    }
    cout << "SchemeTwo单个对象平均比较次数：" << totalCompareCount / size << endl;
}

void SchemeThe(object *arr, int size) {
    cout << "方案三测试：" << endl;
    Heap<object> SchemeTheHeap(arr, size);
    for (int j = 0; j < size; ++j) {
        object t = SchemeTheHeap.getTop();
        //cout << t;
    }
    cout << "SchemeThe单个对象平均比较次数：" << SchemeTheHeap.getGetTopTotalCompareCount() / size << endl;
}

int main() {
    int tempA[] = {53, 17, 78, 9, 45, 65, 87, 23};
    Heap<int> Heap01(tempA, 8);
    cout << "创建了一个大小为" << Heap01.getSize() << "的int型";
    if (Heap01.getType())
        cout << "大根堆";
    else
        cout << "小根堆";
    cout << "\n堆容量为：" << Heap01.getCapacity();
    cout << "\n当大小超过堆容量时，堆容量会自动扩展，每次增长一个默认长度。";
    cout << "\n目前堆的情况：";
    Heap01.DisPlayHeap();
    cout << "\n插入一个元素19：";
    Heap01.Insert(19);
    Heap01.DisPlayHeap();
    cout << "\n删除堆顶元素9：";
    Heap01.Remove();
    Heap01.DisPlayHeap();
    if (Heap01.isEmpty())
        cout << "\n此时堆为空";
    else
        cout << "\n此时堆不为空";
    cout << "\n堆排序（从小到大）：";
    Heap01.HeapSort();
    Heap01.DisPlayHeap();
    cout << "\n转换为";
    if (Heap01.getType())
        cout << "大根堆：";
    else
        cout << "小根堆：";
    Heap01.toMaxHeap();
    Heap01.DisPlayHeap();
    cout << "\n堆排序（从大到小）：";
    Heap01.HeapSort();
    Heap01.DisPlayHeap();
    cout << "\n转换为";
    if (Heap01.getType())
        cout << "大根堆：";
    else
        cout << "小根堆：";
    Heap01.toMinHeap();
    Heap01.DisPlayHeap();
    cout << "\n执行makeEmpty()后：";
    Heap01.makeEmpty();
    if (Heap01.isEmpty())
        cout << "此时堆为空";
    else
        cout << "此时堆不为空";
    cout << "\n堆大小：" << Heap01.getSize()
         << "\n堆容量：" << Heap01.getCapacity();

    srand((unsigned) time(nullptr));
    int a = 20000, b = 100000;//n属于[a,b];
    int n = (rand() % (b - a + 1)) + a;
    cout << "\n共产生" << n << "个对象。" << endl;
    object *arr = new object[n];
    for (int i = 0; i < n; ++i) {
        arr[i].value = rand() % INT_MAX;
        arr[i].priority = rand() % INT_MAX;
    }
    clock_t SchemeOneStart, SchemeOneEnd;
    SchemeOneStart = clock();
    SchemeOne(arr, n);
    SchemeOneEnd = clock();
    cout << "SchemeOne总用时：" <<
         ((double) (SchemeOneEnd - SchemeOneStart) / CLOCKS_PER_SEC) * 1000 << "ms" << endl;

    clock_t SchemeTwoStart, SchemeTwoEnd;
    SchemeTwoStart = clock();
    SchemeTwo(arr, n);
    SchemeTwoEnd = clock();
    cout << "SchemeTwo总用时：" <<
         ((double) (SchemeTwoEnd - SchemeTwoStart) / CLOCKS_PER_SEC) * 1000 << "ms" << endl;

    clock_t SchemeTheStart, SchemeTheEnd;
    SchemeTheStart = clock();
    SchemeThe(arr, n);
    SchemeTheEnd = clock();
    cout << "SchemeThe总用时：" <<
         ((double) (SchemeTheEnd - SchemeTheStart) / CLOCKS_PER_SEC) * 1000 << "ms" << endl;

    return 0;
}