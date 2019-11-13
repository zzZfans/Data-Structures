//
// Created by Zfans on 2019/11/04.
//

#ifndef GRAPHBYADJACENCYLIST_GRAPHBYADJACENCYLIST_H
#define GRAPHBYADJACENCYLIST_GRAPHBYADJACENCYLIST_H

#include <queue>

const int DefaultVertices = 1024;                //默认最大顶点数（=Size）

template<class T, class E>
struct Edge {              //边结点定义

    int dest{};         //边的另一顶点位置（目的地）
    E weight;           //边上的权值

    Edge<T, E> *nextEdge;             //下一条边链指针

    Edge() = default;             //构造函数

    Edge(int num, E weight) : dest(num), weight(weight), nextEdge(nullptr) {}        //构造函数

    bool operator!=(Edge<T, E> &R) const {         //判边不等否
        return dest != R.dest;
    }
};

template<class T, class E>
struct Vertex {            //顶点的定义
    T value;                   //顶点的值
    Edge<T, E> *edgeHead;//边链表的头指针
};

template<class T, class E>
class GraphByAdjacencyList {
private:
    Vertex<T, E> *NodeTable;//顶点表（各边链表的头结点）
    int maxVertices;//图中最大顶点数
    int numEdges;//当前边数
    int numVertices;//当前顶点数

    friend std::istream &operator>>(std::istream &in, GraphByAdjacencyList<T, E> &Graph) {//输入
        //通过从输入流对象in输入n个顶点信息和e条无向边的信息建立用邻接表表示的图G。邻接表初始化的工作已经在构造函数中完成。
        int i, VertexIndex01, VertexIndex02, numberOfVertex, numberOfEdge;
        T t_vertex01, t_vertex02;
        E weight;
        in >> numberOfVertex >> numberOfEdge;  //输入顶点数n和边数m
        for (i = 0; i < numberOfVertex; ++i) {//建立顶点表数据
            in >> t_vertex01;
            Graph.insertVertex(t_vertex01);
        }
        i = 0;
        while (i < numberOfEdge) {
            in >> t_vertex01 >> t_vertex02 >> weight; //输入端点信息
            VertexIndex01 = Graph.getVertexIndex(t_vertex01);    //查顶点号
            VertexIndex02 = Graph.getVertexIndex(t_vertex02);
            if (VertexIndex01 == -1 || VertexIndex02 == -1)
                std::cout << "边两端点信息有误，重新输入！" << std::endl;
            else {
                Graph.insertEdge(VertexIndex01, VertexIndex02, weight);
                i++;
            }
        }
        return in;
    }

    friend std::ostream &operator<<(std::ostream &out, GraphByAdjacencyList<T, E> &Graph) {//输出
        //输出图的所有顶点和边的信息
        int i, j, numberOfVertex, numberOfEdge;
        T NodeValue01, NodeValue02;
        E edgeWeight;
        numberOfVertex = Graph.getNumVertices();
        numberOfEdge = Graph.getNumEdges();
        out << numberOfVertex << "," << numberOfEdge << std::endl;
        for (i = 0; i < numberOfVertex; ++i) {
            for (j = i + 1; j < numberOfVertex; ++j) {
                edgeWeight = Graph.getEdgeWeight(i, j);
                if (edgeWeight > 0 && edgeWeight < INT_MAX) {
                    NodeValue01 = Graph.getNodeValue(i);
                    NodeValue02 = Graph.getNodeValue(j);
                    out << "(" << NodeValue01 << "," << NodeValue02 << "," << edgeWeight << ")" << std::endl;
                }
            }
        }
        return out;
    }

    void DFS(GraphByAdjacencyList<T, E> &Graph, int index, bool *visited);//子过程

public:

    explicit GraphByAdjacencyList(int size = DefaultVertices);//构造函数

    ~GraphByAdjacencyList();//析构函数

    T getNodeValue(int index) {//取位置为i的顶点中的值
        return (index >= 0 && index < this->numVertices ? NodeTable[index].value : 0);
    }

    E getEdgeWeight(int vertex01, int vertex02);//返回边（v1，v2）上的权值

    bool insertVertex(const T &vertexValue);//在图中插入一个顶点vertex

    bool removeVertex(int vertexIndex);//在图中删除一个顶点v

    bool insertEdge(int vertex01, int vertex02, E weight);//在图中插入一条边（v1，v2）

    bool removeEdge(int vertex01, int vertex02);//在图中删除一条边（v1，v2）

    virtual int getFirstNeighbor(int vertexIndex);//取顶点v的第一个邻接顶点

    virtual int getNextNeighbor(int vertexIndex, int currentNeighborDest);//取邻接顶点w的下一邻接顶点

    [[nodiscard]] bool GraphEmpty() const {//判图空否
        return !numEdges;
    }

    [[nodiscard]] bool GraphFull() const {//判图满否
        return numVertices == maxVertices || numEdges == maxVertices * (maxVertices - 1) / 2;
    }

    [[nodiscard]] int getNumEdges() const;

    [[nodiscard]] int getNumVertices() const;

    [[nodiscard]] int getVertexDegree(int vertexValue) const;

    void DFS(GraphByAdjacencyList<T, E> &Graph, const T &vertexValue);

    void BFS(GraphByAdjacencyList<T, E> &Graph, const T &vertexValue);

    int getVertexIndex(const T vertexValue) {//给出顶点vertex在图中的位置
        for (int i = 0; i < this->numVertices; ++i) {
            if (NodeTable[i].value == vertexValue) return i;
        }
        return -1;
    }
};

template<class T, class E>
GraphByAdjacencyList<T, E>::GraphByAdjacencyList(int size) {
    this->maxVertices = size;
    this->numVertices = 0;
    this->numEdges = 0;
    NodeTable = new Vertex<T, E>[this->maxVertices];//创建顶点表数组
    if (NodeTable == nullptr) {
        std::cerr << "存储分配错误！" << std::endl;
        exit(1);
    }
    for (int i = 0; i < this->maxVertices; ++i) {
        NodeTable[i].edgeHead = nullptr;
    }
}

template<class T, class E>
GraphByAdjacencyList<T, E>::~GraphByAdjacencyList() {
//析构函数：删除一个邻接表
    for (int i = 0; i < this->numVertices; ++i) {//删除各边链表中的结点
        Edge<T, E> *p = NodeTable[i].edgeHead;//找到其对应边链表的首结点
        while (p != nullptr) {//不断地删除第一个结点
            NodeTable[i].edgeHead = p->nextEdge;
            delete p;
            p = NodeTable[i].edgeHead;
        }
    }
    delete[] NodeTable;//删除顶点表数组
}

template<class T, class E>
int GraphByAdjacencyList<T, E>::getFirstNeighbor(int vertexIndex) {
    //给出顶点位置为v的第一个邻接顶点的位置，如果找不到，则函数返回-1。
    if (vertexIndex != -1) {              //顶点v存在
        Edge<T, E> *p = NodeTable[vertexIndex].edgeHead;//对应边链表第一个边结点
        if (p != nullptr) {//存在，返回第一个邻接顶点
            return p->dest;
        }
    }
    return -1;//第一个邻接顶点不存在
}

template<class T, class E>
int GraphByAdjacencyList<T, E>::getNextNeighbor(int vertexIndex, int currentNeighborDest) {
    //给出顶点v的邻接顶点w的下一个邻接顶点的位置，若没有下一个邻接顶点，则函数返回-1
    if (vertexIndex != -1) {//顶点v存在
        Edge<T, E> *p = NodeTable[vertexIndex].edgeHead;//对应边链表第一个边结点
        while (p != nullptr && p->dest != currentNeighborDest) {//寻找邻接顶点w
            p = p->nextEdge;
        }
        if (p != nullptr && p->nextEdge != nullptr) {
            return p->nextEdge->dest;//返回下一个邻接顶点
        }
    }
    return -1;//下一邻接顶点不存在
}

template<class T, class E>
E GraphByAdjacencyList<T, E>::getEdgeWeight(int vertex01, int vertex02) {
    //函数返回边（vertex01,vertex02）上的权值，若该边不在图中，则函数返回权值0。
    if (vertex01 != -1 && vertex02 != -1) {
        Edge<T, E> *p = NodeTable[vertex01].edgeHead;//v1的第一条关联的边
        while (p != nullptr && p->dest != vertex02) {//寻找邻接顶点v2
            p = p->nextEdge;
        }
        if (p != nullptr) {//找到此边，返回权值
            return p->weight;
        }
    }
    return 0;//边（vertex01，vertex02）不存在
}

template<class T, class E>
bool GraphByAdjacencyList<T, E>::insertVertex(const T &vertexValue) {
    //在图的顶点表中插入一个新顶点vertex。若插入成功，函数返回true，否则返回false。
    if (this->numVertices == this->maxVertices)
        return false;//顶点表满，不能插入
    NodeTable[this->numVertices].value = vertexValue;//插入在表的最后
    this->numVertices++;
    return true;
}

template<class T, class E>
bool GraphByAdjacencyList<T, E>::removeVertex(int vertexIndex) {
    //在图中删除一个指定顶点v，v是顶点号。若删除成功，函数返回true，否则返回false。
    if (this->numVertices == 1 || vertexIndex < 0 || vertexIndex >= this->numVertices)
        return false;//表空或顶点号超出范围
    Edge<T, E> *p, *s, *t;
    int i, k;
    while (NodeTable[vertexIndex].edgeHead != nullptr) {//删除第v个边链表中所有结点
        p = NodeTable[vertexIndex].edgeHead;
        k = p->dest;        //取邻接顶点k
        s = NodeTable[k].edgeHead;
        t = nullptr;    //找对称存放的边结点
        while (s != nullptr && s->dest != vertexIndex) {
            t = s;
            s = s->nextEdge;
        }
        if (s != nullptr) {      //删除对称存放的边结点
            if (t == nullptr) {
                NodeTable[k].edgeHead = s->nextEdge;
            } else
                t->nextEdge = s->nextEdge;
            delete s;
        }
        NodeTable[vertexIndex].edgeHead = p->nextEdge;             //清除顶点v的边链表结点
        delete p;
        this->numEdges--;      //与顶点v相关联的边数减1
    }
    this->numVertices--;    //图的顶点个数减1
    NodeTable[vertexIndex].value = NodeTable[this->numVertices].value; //填补
    p = NodeTable[vertexIndex].edgeHead = NodeTable[this->numVertices].edgeHead;
    while (p != nullptr) {
        s = NodeTable[p->dest].edgeHead;
        while (s != nullptr) {
            if (s->dest == this->numVertices) {
                s->dest = vertexIndex;
                break;
            } else
                s = s->nextEdge;
        }
    }
    return true;
}

template<class T, class E>
bool GraphByAdjacencyList<T, E>::insertEdge(int vertex01, int vertex02, E weight) {
    //在带权图中插入一条边（vertex01,vertex02），若此边存在或参数不合理，函数返回false，否则返回true。
    //对于非带权图，最后一个参数cost不要。算法中相应语句也不要。
    if (vertex01 >= 0 && vertex01 < this->numVertices && vertex02 >= 0 && vertex02 < this->numVertices) {
        Edge<T, E> *q, *p = NodeTable[vertex01].edgeHead;   //v1对应的边链表头指针
        while (p != nullptr && p->dest != vertex02)//寻找邻接顶点vertex2
            p = p->nextEdge;
        if (p != nullptr)  //找到此边，不插入
            return false;
        p = new Edge<T, E>;//否则，创建新结点
        q = new Edge<T, E>;
        p->dest = vertex02;
        p->weight = weight;
        p->nextEdge = NodeTable[vertex01].edgeHead;//链如v1边链表
        NodeTable[vertex01].edgeHead = p;
        q->dest = vertex01;
        q->weight = weight;
        q->nextEdge = NodeTable[vertex02].edgeHead;//链入v2边链表
        NodeTable[vertex02].edgeHead = q;
        this->numEdges++;
        return true;
    }
    return 0;
}

template<class T, class E>
bool GraphByAdjacencyList<T, E>::removeEdge(int vertex01, int vertex02) {
    //在图中删除一条边（vertex01,vertex02）
    if (vertex01 != -1 && vertex02 != -1) {
        Edge<T, E> *p = NodeTable[vertex01].edgeHead, *q = nullptr, *s = p;
        while (p != nullptr && p->dest != vertex02) {//v1对应边链表中找被删边
            q = p;
            p = p->nextEdge;
        }
        if (p != nullptr) {//找到被删边结点
            if (p == s)//该结点是边链表首结点
                NodeTable[vertex01].edgeHead = p->nextEdge;
            else
                q->nextEdge = p->nextEdge;//不是，重新链接
            delete p;
        } else
            return false;  //没有找到被删边结点
        p = NodeTable[vertex02].edgeHead; //v2对应边链表中删除
        q = nullptr;
        s = p;
        while (p->dest != vertex01) {//寻找被删边结点
            q = p;
            p = p->nextEdge;
        }
        if (p == s)//该结点时边链表首结点
            NodeTable[vertex02].edgeHead = p->nextEdge;
        else
            q->nextEdge = p->nextEdge;//不是，重新链接
        delete p;
        return true;
    }
    return false;//没有找到结点
}

template<class T, class E>
int GraphByAdjacencyList<T, E>::getNumEdges() const {
    return numEdges;
}

template<class T, class E>
int GraphByAdjacencyList<T, E>::getNumVertices() const {
    return numVertices;
}

template<class T, class E>
int GraphByAdjacencyList<T, E>::getVertexDegree(int vertexValue) const {
    Edge<T, E> *p = nullptr;
    for (int i = 0; i < numVertices; ++i) {
        if (NodeTable[i].value == vertexValue) {
            p = NodeTable[i].edgeHead;
            break;
        }
    }
    int count = 0;
    while (p != nullptr) {
        count++;
        p = p->nextEdge;
    }
    return count;
}

template<class T, class E>
void GraphByAdjacencyList<T, E>::DFS(GraphByAdjacencyList<T, E> &Graph, const T &vertexValue) {
    //从顶点vertexValue出发，对图Graph进行深度优先遍历的主过程
    int i, vertexIndex, numberOfVertex = Graph.getNumVertices();//取图中顶点个数
    bool *visited = new bool[numberOfVertex];//创建辅助数组
    for (i = 0; i < numberOfVertex; ++i) {//辅助数组visited初始化
        visited[i] = false;
    }
    vertexIndex = Graph.getVertexIndex(vertexValue);
    DFS(Graph, vertexIndex, visited);//从顶点0开始深度优先搜索
    delete[] visited;//释放visited
}

template<class T, class E>
void GraphByAdjacencyList<T, E>::DFS(GraphByAdjacencyList<T, E> &Graph, int index, bool *visited) {               //子过程
    //从顶点位置index出发，以深度优先的次序访问所有可读入的尚未访问过的顶点。算法中用到一个
    //辅助数组visited，对已访问过的顶点作访问标记
    std::cout << Graph.getNodeValue(index) << " ";//访问顶点index
    visited[index] = true;//顶点index作访问标记
    int neighborVertex = Graph.getFirstNeighbor(index);//找顶点index的第一个邻接顶点neighborVertex
    while (neighborVertex != -1) {//若邻接顶点neighborVertex存在
        if (!visited[neighborVertex]) {//若w未访问过，递归访问顶点neighborVertex
            DFS(Graph, neighborVertex, visited);
        }
        neighborVertex = Graph.getNextNeighbor(index, neighborVertex);//取index排在neighborVertex后的下一个邻接顶点
    }
}

template<class T, class E>
void GraphByAdjacencyList<T, E>::BFS(GraphByAdjacencyList<T, E> &Graph, const T &vertexValue) {
//从顶点vertexValue出发，以广度优先的次序横向搜索图，算法中使用了一个队列。
    int i, neighborVertex, numberOfVertex = Graph.getNumVertices();//取图中顶点个数
    bool *visited = new bool[numberOfVertex];   //visited记录顶点是否访问过
    for (i = 0; i < numberOfVertex; i++) {   //初始化
        visited[i] = false;
    }
    int vertexIndex = Graph.getVertexIndex(vertexValue);   //取顶点下标
    std::cout << Graph.getNodeValue(vertexIndex) << " ";      //访问顶点vertexIndex，做已访问标记
    visited[vertexIndex] = true;
    std::queue<int> vertexQueue;
    vertexQueue.push(vertexIndex);             //顶点进队列，实现分层访问
    while (!vertexQueue.empty()) {             //循环，访问所有结点
        vertexIndex = vertexQueue.front();
        vertexQueue.pop();              //从队列中退出顶点vertexIndex
        neighborVertex = Graph.getFirstNeighbor(vertexIndex);      //找顶点vertexIndex的第一个邻接顶点neighborVertex
        while (neighborVertex != -1) {             //若邻接顶点neighborVertex存在
            if (!visited[neighborVertex]) {         //若未访问过
                std::cout << Graph.getNodeValue(neighborVertex) << " ";   //访问顶点neighborVertex
                visited[neighborVertex] = true;
                vertexQueue.push(neighborVertex);           //顶点neighborVertex进队列
            }
            neighborVertex = Graph.getNextNeighbor(vertexIndex, neighborVertex);  //找顶点vertexIndex的下一个邻接顶点
        }              //重复检测vertexIndex的所有邻接顶点
    }         //外层循环，判队列空否
    delete[] visited;
}


#endif //GRAPHBYADJACENCYLIST_GRAPHBYADJACENCYLIST_H
