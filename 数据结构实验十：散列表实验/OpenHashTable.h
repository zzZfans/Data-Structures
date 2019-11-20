//
// Created by Zfans on 2019/11/19.
//

#ifndef HASHTABLE_OPENHASHTABLE_H
#define HASHTABLE_OPENHASHTABLE_H

#include <cassert>
#include <iostream>

template<class T>
struct ChainNode {   //各桶中同义词子表的链结点定义
    unsigned long long key{};
    T value;             //元素
    ChainNode<T> *link;     //链指针

    explicit ChainNode(ChainNode<T> *link) : link(link) {}

    ChainNode(unsigned long long int key, T value, ChainNode<T> *link) :
            key(key), value(value), link(link) {}
};

template<class T>
class OpenHashTable {   //散列表（表头指针向量）定义
public:
    explicit OpenHashTable(int divisor, int bucketSize = DefaultSize);//散列表的构造函数
    ~OpenHashTable() {   //析构函数
        delete[]hashTable;
    }

    bool Search(unsigned long long key, T &value);//在散列表中搜索k1
    bool Insert(unsigned long long key, const T &value); //在散列表中插入value
    bool Remove(unsigned long long key);//在散列表中删除关键字为key的元素
    [[nodiscard]] const std::vector<int> &getAsl() const;

private:
    int divisor{};//除数（必须是质数）
    int bucketSize{}; //桶的个数
    int elementSize;//元素个数
    int detectionTimes;  //探测次数
    int LinearDetectionTimes;//线性探测次数
    ChainNode<T> **hashTable; //散列表定义
    ChainNode<T> *FindPos(unsigned long long key);//散列
    std::vector<int> ASL;

};

template<class T>
OpenHashTable<T>::OpenHashTable(int divisor, int bucketSize) {//构造函数
    this->divisor = divisor;
    this->bucketSize = bucketSize;
    if (this->divisor > this->bucketSize)
        this->divisor = this->bucketSize;
    detectionTimes = 0;
    LinearDetectionTimes = 0;
    elementSize = 0;
    hashTable = new ChainNode<T> *[bucketSize];//创建头结点
    for (int i = 0; i < bucketSize; ++i) {
        hashTable[i] = new ChainNode<T>(nullptr);
    }
    assert(hashTable != nullptr);  //断言：判断存储分配成功否
}

template<class T>
ChainNode<T> *OpenHashTable<T>::FindPos(const unsigned long long key) {
    //在散列表hashTable中搜索关键码为key的元素。函数返回一个指向散列表中某位置的指针；
    //若元素不存在，则返回nullptr。
    detectionTimes++;
    int j = key % divisor;        //计算散列地址
    ChainNode<T> *p = hashTable[j]->link;           //扫描第j链的同义词子表
    int currentLinearDetectionTimes = 0;  //探测次数
    currentLinearDetectionTimes++;
    while (p != nullptr && p->key != key) {
        currentLinearDetectionTimes++;
        p = p->link;
    }
    LinearDetectionTimes += currentLinearDetectionTimes;
    ASL.push_back(LinearDetectionTimes / detectionTimes);
    return p;   //返回
}

template<class T>
bool OpenHashTable<T>::Insert(const unsigned long long key, const T &value) {
    ChainNode<T> *p = FindPos(key);
    if (p == nullptr) {
        auto *newOne = new ChainNode<T>(key, value, p);
        int j = key % divisor;        //计算散列地址
        ChainNode<T> *t = hashTable[j];
        while (t->link != nullptr) {
            t = t->link;
        }
        t->link = newOne;
        elementSize++;
        return true;
    } else if (p->value == value) {
        std::cout << "表中已有此元素，不再重复插入！" << std::endl;
        return false;
    }
}

template<class T>
bool OpenHashTable<T>::Search(const unsigned long long key, T &value) {
    ChainNode<T> *p = FindPos(key);
    if (p == nullptr)
        return false;
    value = p->value;
    return true;
}

template<class T>
bool OpenHashTable<T>::Remove(const unsigned long long key) {
    ChainNode<T> *p = FindPos(key);
    if (p == nullptr) {
        return false;
    }
    int j = key % divisor;        //计算散列地址
    ChainNode<T> *t = hashTable[j];
    while (t->link != p) {
        t = t->link;
    }
    t->link = p->link;
    delete p;
    elementSize--;
    return true;
}

template<class T>
const std::vector<int> &OpenHashTable<T>::getAsl() const {
    return ASL;
}


#endif //HASHTABLE_OPENHASHTABLE_H
