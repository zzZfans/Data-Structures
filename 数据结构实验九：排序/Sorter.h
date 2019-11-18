//
// Created by Zfans on 2019/10/30.
//

#ifndef SORT_SORTER_H
#define SORT_SORTER_H

template<class T>
class Sorter {

private:

    int ComparisonTimes, TimesOfMovement;//比较次数计数变量、移动次数计数变量

public:
    Sorter() {
        ComparisonTimes = 0;
        TimesOfMovement = 0;
    }

    ~Sorter() {}

    //冒泡（交换）排序
    std::pair<int, int> bubble_sort(T arr[], int len) {
        int i, j;
        for (i = 0; i < len - 1; i++)
            for (j = 0; j < len - 1 - i; j++) {
                ComparisonTimes++;
                if (arr[j] > arr[j + 1]) {
                    TimesOfMovement += 2;
                    swap(&arr[j], &arr[j + 1]);
                }
            }
        std::pair<int, int> result;
        result.first = ComparisonTimes;
        result.second = TimesOfMovement;
        ZeroClearing();
        return result;
    }

    //选择排序
    std::pair<int, int> selection_sort(T arr[], int len) {
        int i, j;
        for (i = 0; i < len - 1; i++) {
            T min = i;
            for (j = i + 1; j < len; j++) {    //走訪未排序的元素
                if (arr[j] < arr[min])    //找到目前最小值
                    min = j;    //紀錄最小值
                ComparisonTimes++;
            }
            TimesOfMovement += 2;
            swap(&arr[min], &arr[i]);    //做交換
        }
        std::pair<int, int> result;
        result.first = ComparisonTimes;
        result.second = TimesOfMovement;
        ZeroClearing();
        return result;
    }

//插入排序
    std::pair<int, int> insertion_sort(T arr[], int len) {
        int i, j;
        T temp;
        for (i = 1; i < len; i++) {
            temp = arr[i];
            for (j = i; j > 0 && arr[j - 1] > temp; j--) {
                ComparisonTimes++;
                arr[j] = arr[j - 1];
            }
            TimesOfMovement += 2;
            arr[j] = temp;
        }
        std::pair<int, int> result;
        result.first = ComparisonTimes;
        result.second = TimesOfMovement;
        ZeroClearing();
        return result;
    }

//归并排序
    std::pair<int, int> merge_sort(T arr[], int len) {
        T *a = arr;
        T *b = (T *) malloc(len * sizeof(T));
        int seg, start;
        for (seg = 1; seg < len; seg += seg) {
            for (start = 0; start < len; start += seg + seg) {
                int low = start, mid = min(start + seg, len), high = min(start + seg + seg, len);
                int k = low;
                int start1 = low, end1 = mid;
                int start2 = mid, end2 = high;
                while (start1 < end1 && start2 < end2) {
                    ComparisonTimes++;
                    b[k++] = a[start1] < a[start2] ? a[start1++] : a[start2++];
                }
                while (start1 < end1) {
                    TimesOfMovement++;
                    b[k++] = a[start1++];
                }
                while (start2 < end2) {
                    TimesOfMovement++;
                    b[k++] = a[start2++];
                }
            }
            T *temp = a;
            a = b;
            b = temp;
        }
        if (a != arr) {
            T i;
            for (i = 0; i < len; i++)
                b[i] = a[i];
            b = a;
        }
        free(b);
        std::pair<int, int> result;
        result.first = ComparisonTimes;
        result.second = TimesOfMovement;
        ZeroClearing();
        return result;
    }

//希尔排序
    std::pair<int, int> shell_sort(T arr[], int len) {
        int gap, i, j;
        T temp;
        for (gap = len >> 1; gap > 0; gap = gap >> 1)
            for (i = gap; i < len; i++) {
                temp = arr[i];
                for (j = i - gap; j >= 0 && arr[j] > temp; j -= gap) {
                    ComparisonTimes++;
                    arr[j + gap] = arr[j];
                }
                TimesOfMovement += 2;
                arr[j + gap] = temp;
            }
        std::pair<int, int> result;
        result.first = ComparisonTimes;
        result.second = TimesOfMovement;
        ZeroClearing();
        return result;
    }

    //快速排序
    void QuickSort(int A[], int low, int high, int &CT, int &TOM) { //快排母函数
        if (low < high) {
            int pivot = Paritition1(A, low, high, CT, TOM);
            QuickSort(A, low, pivot - 1, CT, TOM);
            QuickSort(A, pivot + 1, high, CT, TOM);
        }
    }

    //堆排序
    void heap_sort(int arr[], int len, int &CT, int &TOM) {
        // 初始化，i從最後一個父節點開始調整
        for (int i = len / 2 - 1; i >= 0; i--)
            max_heapify(arr, i, len - 1, CT, TOM);
        // 先將第一個元素和已经排好的元素前一位做交換，再從新調整(刚调整的元素之前的元素)，直到排序完畢
        for (int i = len - 1; i > 0; i--) {
            TOM++;
            std::swap(arr[0], arr[i]);
            max_heapify(arr, 0, i - 1, CT, TOM);
        }
    }

private:
    //堆排序子函数
    void max_heapify(int arr[], int start, int end, int &CT, int &TOM) {
        // 建立父節點指標和子節點指標
        int dad = start;
        int son = dad * 2 + 1;
        while (son <= end) { // 若子節點指標在範圍內才做比較
            if (son + 1 <= end && arr[son] < arr[son + 1]) { // 先比較兩個子節點大小，選擇最大的
                CT++;
                son++;
            }
            if (arr[dad] > arr[son]) // 如果父節點大於子節點代表調整完畢，直接跳出函數
                return;
            else { // 否則交換父子內容再繼續子節點和孫節點比較
                TOM++;
                std::swap(arr[dad], arr[son]);
                dad = son;
                son = dad * 2 + 1;
            }
        }
    }

//快排子函数
    int Paritition1(int A[], int low, int high, int &CT, int &TOM) {
        int pivot = A[low];
        while (low < high) {
            while (low < high && A[high] >= pivot) {
                CT++;
                --high;
            }
            TOM++;
            A[low] = A[high];
            while (low < high && A[low] <= pivot) {
                CT++;
                ++low;
            }
            TOM++;
            A[high] = A[low];
        }
        TOM++;
        A[low] = pivot;
        return low;
    }

//冒泡（交换）排序&选择排序使用
    void swap(T *a, T *b) {
        T temp = *a;
        *a = *b;
        *b = temp;
    }

//归并排序使用
    T min(T x, T y) {
        return x < y ? x : y;
    }

    void ZeroClearing() {
        ComparisonTimes = 0;
        TimesOfMovement = 0;
    };
};

#endif //SORT_SORTER_H
