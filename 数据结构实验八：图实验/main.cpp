#include <iostream>
#include "MinimumSpanningTree.h"
#include "GraphByAdjacencyList.h"
#include "Dijkstra.h"

//图测试数据 7 9 0 1 2 3 4 5 6 0 1 28 1 2 16 2 3 12 3 4 22 4 5 25 5 0 10 4 6 24 6 1 14 3 6 18
//最短路径测试数据 7 12 0 0 1 4 0 3 6 0 2 6 1 4 7 1 2 1 3 2 2 3 5 5 2 4 6 2 5 4 4 6 6 5 4 1 5 6 8

using namespace std;

int main() {
    GraphByAdjacencyList<int, int> G;
    cin >> G;
    cout << "顶点数量，边数量 （顶点1，顶点2，权值）" << endl;
    cout << G;
    cout << "获取顶点1的度：" << G.getVertexDegree(1);
    cout << endl;
    cout << "获取顶点2的度：" << G.getVertexDegree(2);
    cout << endl;
    cout << "获取顶点3的度：" << G.getVertexDegree(3);
    cout << endl;

    cout << "DFS遍历图：";
    G.DFS(G, 1);
    cout << endl;

    cout << "BFS遍历图：";
    G.BFS(G, 1);
    cout << endl;

    MinimumSpanningTree<int, int> Prim;

    cout << "Prim算法生成最小生成树（顶点1，顶点2，权值）：";

    Prim.Prim(G, 0, Prim);
    cout << endl;

    Prim.DisplayTree();

    MinimumSpanningTree<int, int> Kruskal;

    cout << "Kruskal算法生成最小生成树（顶点1，顶点2，权值）：";

    Kruskal.Kruskal(G, Kruskal);
    cout << endl;

    Kruskal.DisplayTree();

    Dijkstra D;

    int n, m, s;

    cin >> n >> m >> s;

    D.init(n);

    int u, v, w;

    while (m--) {
        cin >> u >> v >> w;

        D.addEdge(u, v, w);
        D.addEdge(v, u, w);
    }

    D.dijkstra(s);

    for (int i = 1; i < n; i++) {
        cout << s << " to " << i << " with length " << D.d[i] << " and path ";
        Vector<int> path;
        int edgeIndex = D.p[i];
        while (D.edges[edgeIndex].from != 0) {
            path.push_back(D.edges[edgeIndex].to);
            edgeIndex = D.p[D.edges[edgeIndex].from];
        }
        path.push_back(D.edges[edgeIndex].to);
        path.push_back(D.edges[edgeIndex].from);
        for (int j = int(path.size()) - 1; j >= 0; --j) {
            cout << path[j];
            if (j != 0)
                cout << "->";
        }
        cout << endl;
    }
    return 0;
}