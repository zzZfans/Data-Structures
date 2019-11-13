//
// Created by Zfans on 2019/11/11.
//

#ifndef GRAPHBYADJACENCYLIST_MINIMUMSPANNINGTREE_H
#define GRAPHBYADJACENCYLIST_MINIMUMSPANNINGTREE_H

#include <iostream>
#include <vector>
#include "GraphByAdjacencyList.h"
#include "UFSets.h"
#include "Heap.h"

const int defaultSize = 1024;

template<class T, class E>
struct MSTEdgeNode {        //最小生成树边结点的类声明
    int tail, head;   //两顶点位置
    E key;   //边权值

    //MSTEdgeNode() : tail(-1), head(-1), key(0) {}//构造函数
    bool operator<=(MSTEdgeNode<T, E> &R) {
        return key <= R.key;
    }

    bool operator<(MSTEdgeNode<T, E> &R) {
        return key < R.key;
    }

    bool operator>(MSTEdgeNode<T, E> &R) {
        return key > R.key;
    }
};

template<class T, class E>
class MinimumSpanningTree {   //最小生成树的类定义
protected:
    MSTEdgeNode<T, E> *edgeValue;//用边值数组表示树
    int maxSize;  //数组的最大元素个数
    int Size;   //当前个数
public:
    explicit MinimumSpanningTree(int size = defaultSize) : maxSize(size), Size(0) {
        edgeValue = new MSTEdgeNode<T, E>[size];
    }

    bool Insert(MSTEdgeNode<T, E> &item);

    void Kruskal(GraphByAdjacencyList<T, E> &G, MinimumSpanningTree<T, E> &MST);

    void Prim(GraphByAdjacencyList<T, E> &G, T u0, MinimumSpanningTree<T, E> &MST);

    void DisplayTree();
};

template<class T, class E>
bool MinimumSpanningTree<T, E>::Insert(MSTEdgeNode<T, E> &item) {
    if (Size == maxSize) {
        return false;
    }
    edgeValue[Size] = item;
    Size++;
    return true;
}

template<class T, class E>
void MinimumSpanningTree<T, E>::Kruskal(GraphByAdjacencyList<T, E> &G, MinimumSpanningTree<T, E> &MST) {
    MSTEdgeNode<T, E> ed;
    int u, v, count;
    int n = G.getNumVertices();
    int m = G.getNumEdges();
    MinHeap<MSTEdgeNode<T, E>> H(m);
    UFSets F(n);
    for (u = 0; u < n; ++u) {
        for (v = u + 1; v < n; ++v) {
            if (G.getEdgeWeight(u, v) != 0) {
                ed.tail = u;
                ed.head = v;
                ed.key = G.getEdgeWeight(u, v);
                H.Insert(ed);
            }
        }
    }
    count = 1;
    while (count < n) {
        H.Remove(ed);
        u = F.Find(ed.tail);
        v = F.Find(ed.head);
        if (u != v) {
            F.Union(u, v);
            MST.Insert(ed);
            count++;
        }
    }
}

template<class T, class E>
void MinimumSpanningTree<T, E>::DisplayTree() {
    for (int i = 0; i < Size; ++i) {
        cout << "(" << edgeValue[i].head << "," << edgeValue[i].tail << "," << edgeValue[i].key << ")" << endl;
    }
}

template<class T, class E>
void MinimumSpanningTree<T, E>::Prim(GraphByAdjacencyList<T, E> &G, const T u0, MinimumSpanningTree<T, E> &MST) {
    MSTEdgeNode<T, E> ed;
    int i, v, count;
    int n = G.getNumVertices();
    int m = G.getNumEdges();
    int u = G.getVertexIndex(u0);
    MinHeap<MSTEdgeNode<T, E>> H(m);
    bool *Vmst = new bool[n];
    for (i = 0; i < n; ++i) {
        Vmst[i] = false;
    }
    Vmst[u] = true;
    count = 1;
    do {
        v = G.getFirstNeighbor(u);
        while (v != -1) {
            if (!Vmst[v]) {
                ed.tail = u;
                ed.head = v;
                ed.key = G.getEdgeWeight(u, v);
                H.Insert(ed);
            }
            v = G.getNextNeighbor(u, v);
        }
        while (!H.IsEmpty() && count < n) {
            H.Remove(ed);
            if (!Vmst[ed.head]) {
                MST.Insert(ed);
                u = ed.head;
                Vmst[u] = true;
                count++;
                break;
            }
        }
    } while (count < n);
}

#endif //GRAPHBYADJACENCYLIST_MINIMUMSPANNINGTREE_H
