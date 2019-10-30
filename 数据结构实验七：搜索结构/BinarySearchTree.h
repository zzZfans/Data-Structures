//
// Created by Zfans on 2019/10/28.
//

#ifndef SEARCHSTRUCTURE_BINARYSEARCHTREE_H
#define SEARCHSTRUCTURE_BINARYSEARCHTREE_H

#include <iostream>
#include <cassert>
#include <queue>

using namespace std;

template<class K, class V>
class BinarySearchTree {

private:
    struct Node {
        K key;
        V value;
        Node *left;
        Node *right;

        Node(K key, V value) {
            this->key = key;
            this->value = value;
            this->left = this->right = nullptr;
        }

        Node(Node *node) {
            this->key = node->key;
            this->value = node->value;
            this->left = node->left;
            this->right = node->right;
        }
    };

    Node *root;
    int Size;

public:
    BinarySearchTree() {//构造函数
        root = nullptr;
        Size = 0;
    }

    ~BinarySearchTree() {//析构函数
        destory(root);
    }

    int size() {//获取元素个数
        return Size;
    }

    bool isEmpty() { //判空
        return Size == 0;
    }

    void insert(K key, V value) {//插入元素
        root = insert(root, key, value);
    }

    bool existence(K key, int &ComparisonTimes) {//判断是否存在key
        return existence(root, key, ComparisonTimes);
    }

    V *search(K key) { //搜索并返回value
        return search(root, key);
    }

    void preOrder() {//前序遍历
        preOrder(root);
    }

    void destory() {//销毁二叉搜索树
        destory(root);
    }

    void levelOrder() {//层次遍历

        queue<Node *> q;
        q.push(root);
        while (!q.empty()) {

            Node *node = q.front();
            q.pop();
            cout << node->key << endl;
            if (node->left)
                q.push(node->left);
            if (node->right)
                q.push(node->right);
        }
    }

    // 寻找最小的键值
    K minimum() {
        assert(Size != 0);
        Node *minNode = minimum(root);
        return minNode->key;

    }

    // 寻找最大的键值
    K maximun() {
        assert(Size != 0);
        Node *maxNode = maximun(root);
        return maxNode->key;
    }

    // 从二叉树删除最小值
    void removeMin() {
        if (root)
            root = removeMin(root);
    }
// 从二叉树删除最大值
    void removeMax() {
        if (root)
            root = removeMax(root);
    }


private:
    // 向node为根的二叉搜索树中，插入节点(key, value)
    // 返回插入新节点的二叉搜索树的根
    Node *insert(Node *node, K key, V value) {
        if (node == nullptr) {
            Size++;
            return new Node(key, value);
        }
        if (key == node->key)
            node->value = value;
        else if (key < node->key)
            node->left = insert(node->left, key, value);
        else
            node->right = insert(node->right, key, value);
        return node;
    }

    bool existence(Node *node, K key, int &ComparisonTimes) {
        ComparisonTimes++;
        if (node == nullptr)
            return false;
        if (key == node->key)
            return true;
        else if (key < node->key) {
            return existence(node->left, key, ComparisonTimes);
        } else {
            return existence(node->right, key, ComparisonTimes);
        }
    }

    V *search(Node *node, K key) {

        if (node == nullptr)
            return nullptr;

        if (key == node->key) {
            return &(node->value);
        } else if (key < node->key) {
            return search(node->left, key);
        } else
            return search(node->right, key);
    }

    void preOrder(Node *node) {
        if (node != nullptr) {
            cout << node->key << endl;
            preOrder(node->left);
            preOrder(node->right);
        }
    }

    void destory(Node *node) {

        if (node != nullptr) {
            destory(node->left);
            destory(node->right);

            delete node;
            Size--;
        }
    }

    Node *minimum(Node *node) {
        if (node->left == nullptr)
            return node;

        return minimum(node->left);
    }

    Node *maximum(Node *node) {
        if (node->right == nullptr)
            return node;

        return maximum(node->right);
    }

    void remove(K key) {
        remove(root, key);

    }

    // 删除掉以node为根的二分搜索树中的最小节点
    // 返回删除节点后新的二分搜索树的根
    Node *removeMin(Node *node) {
        if (node->left == nullptr) {
            Node *rightNode = node->right;
            delete node;
            Size--;
            return rightNode;
        }

        node->left = removeMin(node->left);
    }

    // 删除掉以node为根的二分搜索树中的最大节点
    // 返回删除节点后新的二分搜索树的根
    Node *removeMax(Node *node) {
        if (node->right == nullptr) {
            Node *leftNode = node->left;
            delete node;
            Size--;
            return leftNode;
        }
        node->right = removeMax(node->right);
    }

    // 删除掉以node为根的二分搜索树中键值为key的节点
    // 返回删除节点后新的二分搜索树的根
    Node *remove(Node *node, K key) {
        if (node == nullptr)
            return nullptr;
        if (key < node->key) {
            node->left = remove(node->left, key);
            return node;
        } else if (key > node->key) {
            node->right = remove(node->right, key);
            return node;
        } else {
            // key == node->key
            if (node->left == nullptr) {
                Node *rightNode = node->right;
                delete node;
                Size--;
                return rightNode;
            }

            if (node->right == nullptr) {
                Node *leftNode = node->left;
                delete node;
                Size--;
                return leftNode;
            }

            Node *successor = new Node(minimum(node->right)); //右子树的最小值
            Size++;
            successor->right = removeMin(node->right);
            successor->left = node->left;

            delete node;
            Size--;

            return successor;
        }
    }
};


#endif //SEARCHSTRUCTURE_BINARYSEARCHTREE_H
