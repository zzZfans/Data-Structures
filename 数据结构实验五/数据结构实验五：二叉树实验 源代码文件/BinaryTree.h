//
// Created by Zfans on 2019/10/02.
//

#ifndef BINARYTREE_BINARYTREE_H
#define BINARYTREE_BINARYTREE_H

#include <stack>
#include <queue>
#include <iostream>

using namespace std;

template<class T>
struct BTNode {
    T data;  //数据
    BTNode<T> *parent, *leftChild, *rightChild; //父结点，左子树，右子树

    BTNode() : parent(nullptr), leftChild(nullptr), rightChild(nullptr) {}//无参构造函数

    explicit BTNode(T data, BTNode<T> *P = nullptr, BTNode<T> *L = nullptr, BTNode<T> *R = nullptr)
            : data(data),
              parent(P),
              leftChild(L),
              rightChild(R) {}//带默认值的有参构造函数
};

template<class T>
class BinaryTree {
private:
    BTNode<T> *root; //根结点
    T flag;//数据输入停止标志
protected:
    void PreorderCreateBinaryTree(BTNode<T> *&btNode, const T *&str);//前序遍历创建二叉树（递归）

    void GeneralizedTableCreateBinaryTree(BTNode<T> *&btNode, const T *str);//广义表建立二叉树（非递归）

    void PreOrder(BTNode<T> *&btNode);//前序遍历（递归）

    void InOrder(BTNode<T> *&btNode);//中序遍历（递归）

    void PostOrder(BTNode<T> *&btNode);//后序遍历（递归）

    void NonRecursivePreOrder(BTNode<T> *&btNode);//前序遍历（非递归）

    void NonRecursiveInOrder(BTNode<T> *&btNode);//中序遍历（非递归）

    void NonRecursivePostOrder(BTNode<T> *&btNode);//后序遍历（非递归）

    void LevelOrder(BTNode<T> *&btNode);//层次序遍历（非递归）

    void Destroy(BTNode<T> *&btNode);//销毁二叉树（递归）

    unsigned int NodeLevel(BTNode<T> *&btNode, const T &x, unsigned int count);//计算结点所在的层次（递归）

    unsigned int Size(BTNode<T> *&btNode);//结点数（递归）

    unsigned int LeafSize(BTNode<T> *&btNode);//叶结点数（递归）

    unsigned int Height(BTNode<T> *&btNode);//树的高度（递归)

    BTNode<T> *FindNode(BTNode<T> *&btNode, const T &x);//寻找结点（前序遍历（非递归）改）

    void CopyBinaryTree(BTNode<T> *&selfNode, BTNode<T> *&btNode);//复制二叉树（递归）

public:
    BinaryTree(BinaryTree<T> &BT);//拷贝构造函数
    BinaryTree() : root(nullptr) {}//构造函数
    BinaryTree(T flag) : flag(flag), root(nullptr) {}//指定结束标志的构造函数
    ~BinaryTree() { Destroy(root); }  //析构函数

    void PreorderCreateBinaryTree(const T *&str) { PreorderCreateBinaryTree(root, str); }

    void GeneralizedTableCreateBinaryTree(const T *&str) { GeneralizedTableCreateBinaryTree(root, str); }

    void PreOrder() { PreOrder(root); }

    void InOrder() { InOrder(root); }

    void PostOrder() { PostOrder(root); }

    void NonRecursivePreOrder() { NonRecursivePreOrder(root); }

    void NonRecursiveInOrder() { NonRecursiveInOrder(root); }

    void NonRecursivePostOrder() { NonRecursivePostOrder(root); }

    void LevelOrder() { LevelOrder(root); }

    void Destroy() { Destroy(root); }

    unsigned int NodeLevel(const T &x) { return NodeLevel(root, x, 0); }

    unsigned int Size() { return Size(root); }

    unsigned int LeafSize() { return LeafSize(root); }

    unsigned int Height() { return Height(root); }

    unsigned int DegreeOfNode(const T &x); //结点的度

    T Parent(const T &x);

    T LeftChild(const T &x);

    T RightChild(const T &x);

    void CopyBinaryTree(BinaryTree<T> &BT);//复制二叉树

    T getFlag() const;

    void setFlag(T flag);

    friend ostream &operator<<(ostream &os, const BinaryTree &tree) {
        os << tree.flag << " ";
        string str;
        if (tree.root != nullptr) {
            stack<BTNode<T> *> s;
            s.push(tree.root);
            BTNode<T> *p;
            while (!s.empty()) {
                p = s.top();
                s.pop();
                str += p->data;
                if (p->rightChild != nullptr)
                    s.push(p->rightChild);
                else
                    str += tree.flag;
                if (p->leftChild != nullptr)
                    s.push(p->leftChild);
                else
                    str += tree.flag;
            }
        }
        os << str << endl;
        return os;
    }
};

template<class T>
void BinaryTree<T>::PreorderCreateBinaryTree(BTNode<T> *&btNode, const T *&str) {
    if (*str == flag || *str == '\0') {
        btNode = nullptr;
    } else {
        btNode = new BTNode<T>(*str);
        PreorderCreateBinaryTree(btNode->leftChild, ++str);
        if (btNode->leftChild) {
            btNode->leftChild->parent = btNode;
        }
        PreorderCreateBinaryTree(btNode->rightChild, ++str);
        if (btNode->rightChild) {
            btNode->rightChild->parent = btNode;
        }
    }
}

template<class T>
void BinaryTree<T>::GeneralizedTableCreateBinaryTree(BTNode<T> *&btNode, const T *str) {
    stack<BTNode<T> *> s;
    btNode = nullptr;
    BTNode<T> *p, *t;    //p用来记住当前创建的节点，t用来记住栈顶的元素
    int k;    //k是处理左、右子树的标记
    while (*str != flag) {
        switch (*str) {
            case '(':    //对(做处理
                s.push(p);
                k = 1;
                break;

            case ')':    //对)做处理
                s.pop();
                break;

            case ',':    //对,做处理
                k = 2;
                break;

            default:
                p = new BTNode<T>(*str);    //构造一个结点
                if (btNode == nullptr) {  //如果头节点是空
                    btNode = p;
                } else if (k == 1) { //链入*t的左孩子
                    t = s.top();
                    t->leftChild = p;
                    p->parent = t;
                } else { //链入*t的右孩子
                    t = s.top();
                    t->rightChild = p;
                    p->parent = t;
                }
        }
        str++;
    }
}

template<class T>
void BinaryTree<T>::PreOrder(BTNode<T> *&btNode) {
    if (btNode != nullptr) {
        cout << btNode->data << " ";
        PreOrder(btNode->leftChild);
        PreOrder(btNode->rightChild);
    }
}

template<class T>
void BinaryTree<T>::InOrder(BTNode<T> *&btNode) {
    if (btNode != nullptr) {
        InOrder(btNode->leftChild);
        cout << btNode->data << " ";
        InOrder(btNode->rightChild);
    }
}

template<class T>
void BinaryTree<T>::PostOrder(BTNode<T> *&btNode) {
    if (btNode != nullptr) {
        PostOrder(btNode->leftChild);
        PostOrder(btNode->rightChild);
        cout << btNode->data << " ";
    }
}

template<class T>
void BinaryTree<T>::LevelOrder(BTNode<T> *&btNode) {
    if (btNode != nullptr) {
        queue<BTNode<T> *> Q;
        BTNode<T> *p;
        Q.push(btNode);
        while (!Q.empty()) {
            p = Q.front();
            Q.pop();
            cout << p->data << " ";
            if (p->leftChild != nullptr)
                Q.push(p->leftChild);
            if (p->rightChild != nullptr)
                Q.push(p->rightChild);
        }
    }
}

template<class T>
void BinaryTree<T>::Destroy(BTNode<T> *&btNode) {
    if (btNode != nullptr) {
        Destroy(btNode->leftChild);
        Destroy(btNode->rightChild);
        delete btNode;
        btNode = nullptr;
    }
}

template<class T>
void BinaryTree<T>::NonRecursivePreOrder(BTNode<T> *&btNode) {
    if (btNode != nullptr) {
        stack<BTNode<T> *> s;
        s.push(btNode);
        BTNode<T> *p;
        while (!s.empty()) {
            p = s.top();
            s.pop();
            cout << p->data << " ";
            if (p->rightChild != nullptr)
                s.push(p->rightChild);
            if (p->leftChild != nullptr)
                s.push(p->leftChild);
        }
    }
}

template<class T>
void BinaryTree<T>::NonRecursiveInOrder(BTNode<T> *&btNode) {
    stack<BTNode<T> *> s;
    BTNode<T> *temp = btNode;
    while (temp || !s.empty()) {
        while (temp) {  //有右边就要右边左子树入栈
            s.push(temp);
            temp = temp->leftChild;
        }
        temp = s.top();
        cout << temp->data << " ";
        s.pop();
        temp = temp->rightChild;
    }
}

template<class T>
void BinaryTree<T>::NonRecursivePostOrder(BTNode<T> *&btNode) {
    stack<BTNode<T> *> s;
    BTNode<T> *temp = root, *pre = nullptr;
    while (temp || !s.empty()) {
        while (temp) {
            s.push(temp);
            temp = temp->leftChild;
        }
        temp = s.top();
        if (!temp->rightChild || temp->rightChild == pre) {  //判断无右边
            cout << temp->data << " ";
            s.pop();
            pre = temp;
            temp = nullptr;
        } else
            temp = temp->rightChild;
    }
}

template<class T>
unsigned int BinaryTree<T>::NodeLevel(BTNode<T> *&btNode, const T &x, unsigned int count) {
    if (btNode) {
        count++;
        if (btNode->data == x)
            return count;
        int L = NodeLevel(btNode->leftChild, x, count);
        if (L != 0)
            return L;
        return NodeLevel(btNode->rightChild, x, count);
    }
    return 0;
}

template<class T>
unsigned int BinaryTree<T>::Size(BTNode<T> *&btNode) {
    if (btNode == nullptr)
        return 0;
    return Size(btNode->leftChild) + Size(btNode->rightChild) + 1;
}

template<class T>
unsigned int BinaryTree<T>::LeafSize(BTNode<T> *&btNode) {
    if (btNode == nullptr)
        return 0;
    if (btNode->leftChild == nullptr && btNode->rightChild == nullptr)
        return 1;
    return LeafSize(btNode->leftChild) + LeafSize(btNode->rightChild);
}

template<class T>
unsigned int BinaryTree<T>::Height(BTNode<T> *&btNode) {
    if (btNode == nullptr)
        return 0;
    int L = Height(btNode->leftChild);
    int R = Height(btNode->rightChild);
    return (L > R ? L : R) + 1;
}

template<class T>
BTNode<T> *BinaryTree<T>::FindNode(BTNode<T> *&btNode, const T &x) {
    if (btNode != nullptr) {
        stack<BTNode<T> *> s;
        s.push(btNode);
        BTNode<T> *p;
        while (!s.empty()) {
            p = s.top();
            s.pop();
            if (p->data == x)
                return p;
            if (p->rightChild != nullptr)
                s.push(p->rightChild);
            if (p->leftChild != nullptr)
                s.push(p->leftChild);
        }
    }
    return nullptr;
}

template<class T>
unsigned int BinaryTree<T>::DegreeOfNode(const T &x) {
    unsigned int count = 0;
    BTNode<T> *p = FindNode(root, x);
    if (p->leftChild)
        count++;
    if (p->rightChild)
        count++;
    return count;
}

template<class T>
T BinaryTree<T>::Parent(const T &x) {
    BTNode<T> *p = FindNode(root, x)->parent;
    if (p == nullptr)
        return 0;
    return p->data;
}

template<class T>
T BinaryTree<T>::LeftChild(const T &x) {
    BTNode<T> *p = FindNode(root, x)->leftChild;
    if (p == nullptr)
        return 0;
    return p->data;
}

template<class T>
T BinaryTree<T>::RightChild(const T &x) {
    BTNode<T> *p = FindNode(root, x)->rightChild;
    if (p == nullptr)
        return 0;
    return p->data;
}

template<class T>
BinaryTree<T>::BinaryTree(BinaryTree<T> &BT) {
    flag = BT.flag;
    CopyBinaryTree(root, BT.root);
}

template<class T>
void BinaryTree<T>::CopyBinaryTree(BTNode<T> *&selfNode, BTNode<T> *&btNode) {
    if (btNode != nullptr) {
        selfNode = new BTNode(btNode->data);
        CopyBinaryTree(selfNode->leftChild, btNode->leftChild);
        if (selfNode->leftChild) {
            selfNode->leftChild->parent = selfNode;
        }
        CopyBinaryTree(selfNode->rightChild, btNode->rightChild);
        if (selfNode->rightChild) {
            selfNode->rightChild->parent = selfNode;
        }
    }
}

template<class T>
void BinaryTree<T>::CopyBinaryTree(BinaryTree<T> &BT) {
    CopyBinaryTree(root, BT.root);
}

template<class T>
T BinaryTree<T>::getFlag() const {
    return flag;
}

template<class T>
void BinaryTree<T>::setFlag(T flag) {
    BinaryTree::flag = flag;
}

#endif //BINARYTREE_BINARYTREE_H