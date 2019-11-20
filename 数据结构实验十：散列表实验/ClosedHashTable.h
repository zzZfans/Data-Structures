//
// Created by Zfans on 2019/11/18.
//

#ifndef HASHTABLE_CLOSEDHASHTABLE_H
#define HASHTABLE_CLOSEDHASHTABLE_H

#include <vector>

const int DefaultSize = 1024;

enum KindOfStatus {  //元素分类（活动/空/删）
    Active,
    Empty,
    Deleted
};

template<class T>
struct element {
    unsigned long long key;
    T value;
};

template<class T>
class ClosedHashTable {
public:
    explicit ClosedHashTable(int divisor, int capacity = DefaultSize);//构造函数

    ~ClosedHashTable() {   //析构函数
        delete[]hashTable;
        delete[]status;
    }

    ClosedHashTable<T> &operator=(const ClosedHashTable<T> &otherHashTable);

    bool Search(unsigned long long key, T &value);//在散列表中搜索key,如果存在 通过value返回
    bool Insert(unsigned long long key, const T &value); //在散列表中插入value
    bool Remove(unsigned long long key);//在散列表中删除关键字为key的元素
    void makeEmpty();  //置散列表为空
    [[nodiscard]] const std::vector<int> &getAsl() const;

private:
    int divisor;//散列函数的除数
    int currentSize, capacity;//当前元素个数 容量
    int detectionTimes;  //探测次数
    int LinearDetectionTimes;//线性探测次数
    element<T> *hashTable;   //散列表存储数组
    KindOfStatus *status; //状态数组
    [[nodiscard]] int FindPos(unsigned long long key);//散列函数：计算初始桶号
    std::vector<int> ASL;

};

template<class T>
ClosedHashTable<T>::ClosedHashTable(const int divisor, int capacity) {//构造函数
    this->divisor = divisor;
    this->capacity = capacity;
    detectionTimes = 0;
    LinearDetectionTimes = 0;
    if (this->divisor > capacity)
        this->divisor = capacity;
    currentSize = 0;
    hashTable = new element<T>[capacity];
    status = new KindOfStatus[capacity];
    for (int i = 0; i < capacity; ++i) {
        status[i] = Empty;
    }
}

template<class T>
int ClosedHashTable<T>::FindPos(const unsigned long long key) {
    //搜索在一个散列表中关键码与key匹配的元素，搜索成功，则函数返回该元素的位置，
    //否则返回插入点（如果有足够的空间）
    detectionTimes++;
    int InitBucketNum = key % divisor;       //计算初始桶号
    int LineProbePoint = InitBucketNum;     //线性探测指针
    int currentLinearDetectionTimes = 0;  //探测次数
    do {
        currentLinearDetectionTimes++;
        if (status[LineProbePoint] == Empty ||
            (status[LineProbePoint] == Active && hashTable[LineProbePoint].key == key)) {//找到
            LinearDetectionTimes += currentLinearDetectionTimes;
            ASL.push_back(LinearDetectionTimes / detectionTimes);
            return LineProbePoint;
        }
        LineProbePoint = (LineProbePoint + 1) % capacity;//当做循环表处理，找下一个空桶
    } while (LineProbePoint != InitBucketNum);  //转一圈回到开始点，表已满，失败
    LinearDetectionTimes += currentLinearDetectionTimes;
    ASL.push_back(LinearDetectionTimes / detectionTimes);
    return LineProbePoint;
}

template<class T>
bool ClosedHashTable<T>::Search(const unsigned long long key, T &value) {
    //使用线性探查法在散列表（每个桶容纳一个元素）中搜索key。如果key在表中存在，
    //则函数返回true，并用应用参数value返回找到的元素；如果key不在表中，则返回false。
    int pos = FindPos(key); //搜索
    if (status[pos] != Active || hashTable[pos].key != key)
        return false;
    value = hashTable[pos].value;
    return true;
}

template<class T>
void ClosedHashTable<T>::makeEmpty() {  //清除散列表
    for (int i = 0; i < capacity; ++i) {
        status[i] = Empty;
    }
    currentSize = 0;
}

template<class T>
ClosedHashTable<T> &ClosedHashTable<T>::operator=(const ClosedHashTable<T> &otherHashTable) {
    //重载函数：复制一个散列表ht2
    if (this != &otherHashTable) {           //防止自我复制
        delete[] hashTable;
        delete[] status;
        capacity = otherHashTable.capacity;
        detectionTimes = otherHashTable.detectionTimes;
        LinearDetectionTimes = otherHashTable.LinearDetectionTimes;
        hashTable = new element<T>[capacity];
        status = new KindOfStatus[capacity];
        for (int i = 0; i < capacity; ++i) {   //从源散列表向目标散列表传送
            hashTable[i] = otherHashTable.hashTable[i];
            status[i] = otherHashTable.status[i];
        }
        currentSize = otherHashTable.currentSize;   //传送当前元素个数
    }
    return *this;   //返回目标散列表结构指针
}

template<class T>
bool ClosedHashTable<T>::Insert(const unsigned long long key, const T &value) {
    //在HashTable表中搜索value。若找到则不再插入，若未找到，但表已满，则不再插入，返回false；
    //若找到位置的标指是Empty或Deleted，不论表是否已满，value插入，返回true。
    int pos = FindPos(key);//用散列函数计算桶号
    if (status[pos] != Active) {  //该桶空，存放新元素
        hashTable[pos].key = key;
        hashTable[pos].value = value;
        status[pos] = Active;
        currentSize++;
        return true;
    }
    if (status[pos] == Active && hashTable[pos].value == value) {
        std::cout << "表中已有此元素，不再重复插入！" << std::endl;
        return false;
    }
    std::cout << "表已满，不能插入！" << std::endl;
    return false;
}

template<class T>
bool ClosedHashTable<T>::Remove(const unsigned long long key) {
    //在ht表中删除元素key。若表中找不到k1，或虽然找到k1，但它已经逻辑删除过
    //则返回false，否则在表中删除元素k1，返回true，并在引用参数e1中得到它
    int pos = FindPos(key);
    if (status[pos] == Active && hashTable[pos].key == key) {   //找到要删元素，且是活动元素
        status[pos] = Deleted;            //做逻辑删除标志，并不真正物理删除
        currentSize--;                 //删除操作完成，返回成功标志
        return true;
    } else
        return false;            //表中无被删元素，返回不成功标志
}

template<class T>
const std::vector<int> &ClosedHashTable<T>::getAsl() const {
    return ASL;
}


#endif //HASHTABLE_CLOSEDHASHTABLE_H
