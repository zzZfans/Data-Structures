#include <iostream>
#include "ArrayQueue.h"

int main() {
    ArrayQueue<int> queue;    //创建一个队列

    for (int i = 0; i < 100; ++i) {     //压入100个数据
        queue.push(i);
    }
    cout << "取队列首元素：" << queue.front() << endl;
    cout << "取队列尾元素：" << queue.back() << endl;
    cout << "队列大小：" << queue.size() << endl;
    cout << "队列是否为空（1/0）：" << queue.empty() << endl;
    cout << "队列首元素出队（1表示成功，0表示失败）：" << queue.pop() << endl;
    cout << "取队列首元素：" << queue.front() << endl;
    cout << "取队列尾元素：" << queue.back() << endl;
    cout << "队列大小：" << queue.size() << endl;
    cout << "队列是否为空（1/0）：" << queue.empty() << endl;

    ArrayQueue<int> PrintBinomialCoefficients;
    cout << "打印二项式系数（8层）：" << endl;
    PrintBinomialCoefficients.PrintBinomialCoefficients(8);
    return 0;
}