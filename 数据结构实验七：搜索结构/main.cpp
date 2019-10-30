#include <iostream>
#include <chrono>
#include "SeqList.h"
#include "BinarySearchTree.h"

using namespace std;
using namespace chrono;

const int Size = 10000;//整数个数

int BinarySearch(int target, int *arr, int length, int &ComparisonTimes) {
    int start = 0, end = length - 1;
    while (end >= start) {
        int mid = end + (start - end) / 2;
        ComparisonTimes++;
        if (arr[mid] > target) {
            end = mid - 1;
        } else if (arr[mid] < target) {
            start = mid + 1;
        } else
            return mid;
    }
    return -1;
}

int main() {
    srand((unsigned) time(nullptr));

    int a = 0, b = INT_MAX;

    SeqList<int> seqList;

    for (int i = 0; i < Size; ++i) { //随机产生Size个整数（要求互不相同）存储于顺序表中
        int number = (rand() % (b - a + 1)) + a;//[a,b] 的随机整数
        if (!seqList.QuerySpecifiedElement(number))
            seqList.push_back(number);
        else
            i--;
    }

    int randomNumber[Size];
    for (int j = 0; j < Size; ++j) {
        seqList.getDataByIndex(j + 1, randomNumber[j]);
    }

    seqList.Sort();//将顺序表变为有序顺序表

    int seqListTemp[Size];
    for (int j = 0; j < Size; ++j) {
        seqList.getDataByIndex(j + 1, seqListTemp[j]);
    }

    int TotalNumberOfComparisons = 0;

    auto seqListStart = system_clock::now();
    for (int k = 0; k < Size; ++k) {
        int ComparisonTimes = 0;
        BinarySearch(seqListTemp[k], seqListTemp, seqList.Length(), ComparisonTimes);
        TotalNumberOfComparisons += ComparisonTimes;
    }
    auto seqListEnd = system_clock::now();
    auto duration = duration_cast<microseconds>(seqListEnd - seqListStart);
    cout << "有序顺序表的折半搜索平均搜索长度为：" << TotalNumberOfComparisons / seqList.Length() << endl;
    cout << "有序顺序表的折半搜索总用时为："
         << (double(duration.count()) * microseconds::period::num / microseconds::period::den) * 1000
         << "ms"
         << endl;

    BinarySearchTree<int, int> BST;

    for (int l = 0; l < Size; ++l) {
        BST.insert(randomNumber[l], randomNumber[l]);
    }

    TotalNumberOfComparisons = 0;

    auto BinarySearchTreeStart = system_clock::now();
    for (int m = 0; m < Size; ++m) {
        int ComparisonTimes = 0;
        BST.existence(randomNumber[m], ComparisonTimes);
        TotalNumberOfComparisons += ComparisonTimes;
    }
    auto BinarySearchTreeEnd = system_clock::now();
    duration = duration_cast<microseconds>(BinarySearchTreeEnd - BinarySearchTreeStart);
    cout << "二叉搜索树的查找平均搜索长度为：" << TotalNumberOfComparisons / seqList.Length() << endl;
    cout << "二叉搜索树的查找总用时为：" << (double(duration.count()) * microseconds::period::num / microseconds::period::den) * 1000
         << "ms"
         << endl;

    return 0;
}