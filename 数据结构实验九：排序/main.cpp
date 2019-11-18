#include <iostream>
#include <chrono>
#include "Sorter.h"

using namespace std;
using namespace chrono;

const int Size = 60000;//整数个数

int main() {
    srand((unsigned) time(nullptr));

    int min = 0, max = INT_MAX;

    int arr[Size];

    for (int i = 0; i < Size; ++i) { //随机产生Size个整数
        arr[i] = (rand() % (max - min + 1)) + min;
    }

    int arrTemp01[Size], arrTemp02[Size], arrTemp03[Size], arrTemp04[Size], arrTemp05[Size], arrTemp06[Size], arrTemp07[Size];
    int *arrTemps[] = {arrTemp01, arrTemp02, arrTemp03, arrTemp04, arrTemp05, arrTemp06, arrTemp07};

    for (int j = 0; j < 7; ++j) {
        for (int i = 0; i < Size; ++i) {
            arrTemps[j][i] = arr[i];
        }
    }

    pair<int, int> result;

    Sorter<int> sorter;

    auto start = system_clock::now();
    result = sorter.bubble_sort(arrTemps[0], Size);
    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "冒泡排序的比较次数：" << result.first << "   移动次数：" << result.second
         << "   总耗时："
         << (double(duration.count()) * microseconds::period::num / microseconds::period::den) * 1000
         << "ms"
         << endl;

    start = system_clock::now();
    result = sorter.selection_sort(arrTemps[1], Size);
    end = system_clock::now();
    duration = duration_cast<microseconds>(end - start);
    cout << "选择排序的比较次数：" << result.first << "   移动次数：" << result.second
         << "   总耗时："
         << (double(duration.count()) * microseconds::period::num / microseconds::period::den) * 1000
         << "ms"
         << endl;

    start = system_clock::now();
    result = sorter.insertion_sort(arrTemps[2], Size);
    end = system_clock::now();
    duration = duration_cast<microseconds>(end - start);
    cout << "插入排序的比较次数：" << result.first << "   移动次数：" << result.second
         << "   总耗时："
         << (double(duration.count()) * microseconds::period::num / microseconds::period::den) * 1000
         << "ms"
         << endl;

    start = system_clock::now();
    result = sorter.merge_sort(arrTemps[3], Size);
    end = system_clock::now();
    duration = duration_cast<microseconds>(end - start);
    cout << "归并排序的比较次数：" << result.first << "   移动次数：" << result.second
         << "   总耗时："
         << (double(duration.count()) * microseconds::period::num / microseconds::period::den) * 1000
         << "ms"
         << endl;

    start = system_clock::now();
    result = sorter.shell_sort(arrTemps[4], Size);
    end = system_clock::now();
    duration = duration_cast<microseconds>(end - start);
    cout << "希尔排序的比较次数：" << result.first << "   移动次数：" << result.second
         << "   总耗时："
         << (double(duration.count()) * microseconds::period::num / microseconds::period::den) * 1000
         << "ms"
         << endl;

    int CT = 0, TOM = 0;
    start = system_clock::now();
    sorter.QuickSort(arrTemps[5], 0, Size - 1, CT, TOM);
    end = system_clock::now();
    duration = duration_cast<microseconds>(end - start);
    cout << "快速排序的比较次数：" << CT << "   移动次数：" << TOM
         << "   总耗时："
         << (double(duration.count()) * microseconds::period::num / microseconds::period::den) * 1000
         << "ms"
         << endl;

    CT = 0, TOM = 0;
    start = system_clock::now();
    sorter.heap_sort(arrTemps[6], Size, CT, TOM);
    end = system_clock::now();
    duration = duration_cast<microseconds>(end - start);
    cout << "堆排序的比较次数：" << CT << "   移动次数：" << TOM
         << "   总耗时："
         << (double(duration.count()) * microseconds::period::num / microseconds::period::den) * 1000
         << "ms"
         << endl;

    return 0;
}