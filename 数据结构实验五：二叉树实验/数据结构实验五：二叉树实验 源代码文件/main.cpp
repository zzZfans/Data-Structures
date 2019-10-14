#include <iostream>
#include "BinaryTree.h"

using namespace std;

int main() {
    BinaryTree<char> bt01('#');
    const char *str01 = "ABC##DE##F##G#H##";
    cout << "使用前序遍历创建二叉树（递归）str01 = \"ABC##DE##F##G#H##\"：";
    bt01.PreorderCreateBinaryTree(str01);
    cout << "\n前序遍历（递归）：";
    bt01.PreOrder();
    cout << "\n前序遍历（非递归）：";
    bt01.NonRecursivePreOrder();
    cout << "\n中序遍历（递归）：";
    bt01.InOrder();
    cout << "\n中序遍历（非递归）：";
    bt01.NonRecursiveInOrder();
    cout << "\n后序遍历（递归）：";
    bt01.PostOrder();
    cout << "\n后序遍历（非递归）：";
    bt01.NonRecursivePostOrder();
    cout << "\n层次序遍历（非递归）：";
    bt01.LevelOrder();
    const char *str02 = "A(B(D,E(G,)),C(,F))#";
    cout << "\n使用广义表建立二叉树（非递归）str02 = \"A(B(D,E(G,)),C(,F))#\"：";
    bt01.GeneralizedTableCreateBinaryTree(str02);
    cout << "\n           A              ";
    cout << "\n       B       C           ";
    cout << "\n    D     E      F        ";
    cout << "\n        G                   ";
    cout << "\n前序遍历（递归）：";
    bt01.PreOrder();
    cout << "\n前序遍历（非递归）：";
    bt01.NonRecursivePreOrder();
    cout << "\n中序遍历（递归）：";
    bt01.InOrder();
    cout << "\n中序遍历（非递归）：";
    bt01.NonRecursiveInOrder();
    cout << "\n后序遍历（递归）：";
    bt01.PostOrder();
    cout << "\n后序遍历（非递归）：";
    bt01.NonRecursivePostOrder();
    cout << "\n层次序遍历（非递归）：";
    bt01.LevelOrder();
    cout << "\n计算结点E所在层次：";
    cout << bt01.NodeLevel('E');
    cout << "\n节点数量：";
    cout << bt01.Size();
    cout << "\n叶结点数量：";
    cout << bt01.LeafSize();
    cout << "\n二叉树的高度：";
    cout << bt01.Height();
    cout << "\n计算结点B的度：";
    cout << bt01.DegreeOfNode('B');
    cout << "\n计算结点C的度：";
    cout << bt01.DegreeOfNode('C');
    cout << "\n结点D的双亲：";
    cout << bt01.Parent('D');
    cout << "\n结点E的子女：";
    if (bt01.LeftChild('E'))
        cout << bt01.LeftChild('E');
    if (bt01.RightChild('E'))
        cout << bt01.RightChild('E');
    cout << "\n拷贝构造（bt02拷贝bt01）：";
    BinaryTree<char> bt02(bt01);
    cout << "\n层次序遍历bt02（非递归）：";
    bt02.LevelOrder();
    BinaryTree<char> bt03;
    cout << "\nbt03复制bt02：";
    bt03.CopyBinaryTree(bt02);
    cout << "\n层次序遍历bt03（非递归）：";
    bt03.LevelOrder();
    cout << "\n二叉树输出（bt01）：";
    cout << bt01;
    return 0;
}