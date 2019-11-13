//
// Created by Zfans on 2019/11/13.
//

#ifndef GRAPHBYADJACENCYLIST_DIJKSTRA_H
#define GRAPHBYADJACENCYLIST_DIJKSTRA_H

#include <cstring>
#include "Vector.h"

const int maxn = 10000;
const int INF = 0x3f3f3f3f;

struct DEdge {
    int from, to, weight;

    DEdge() = default;

    DEdge(int u, int v, int w) : from(u), to(v), weight(w) {}
};

struct Dijkstra {
    int vertexNum;
    Vector<DEdge> edges;
    Vector<int> G[1000];  //图
    bool done[maxn]; //访问标记
    int d[maxn];  //结点为下标 从零开始  值为路径长度
    int p[maxn];

    void init(int n) {
        this->vertexNum = n;
        for (int i = 0; i <= n; i++)
            G[i].clear();
        edges.clear();
    }

    void addEdge(int u, int v, int w) {
        edges.push_back(DEdge(u, v, w));
        G[u].push_back(edges.size() - 1);
    }

    void dijkstra(int startVertexIndex) {
        memset(done, 0, sizeof(done));
        for (int i = 0; i < vertexNum; i++) { d[i] = INF; }
        for (int l : G[startVertexIndex]) {
            d[edges[l].to] = edges[l].weight;
            p[edges[l].to] = l;
        }
        d[startVertexIndex] = 0;
        done[startVertexIndex] = true;
        for (int i = 0; i < vertexNum; ++i) {
            int min = INF;
            int nextVertexIndex = 0;
            for (int j = 0; j < vertexNum; ++j) {
                if (!done[j] && d[j] < min) {
                    min = d[j];
                    nextVertexIndex = j;
                }
            }
            done[nextVertexIndex] = true;
            for (int k : G[nextVertexIndex]) {
                int temp = min + edges[k].weight;
                if (!done[edges[k].to] &&
                    (temp < d[edges[k].to])) {//!done[edges[G[nextVertexIndex][k]].to]&&
                    d[edges[k].to] = temp;
                    p[edges[k].to] = k;
                }
            }
        }
    }
};


#endif //GRAPHBYADJACENCYLIST_DIJKSTRA_H
