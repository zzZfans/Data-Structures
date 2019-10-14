//
// Created by Zfans on 2019/09/21.
//

#ifndef ARRAYSTACK_ARRAYSTACK_H
#define ARRAYSTACK_ARRAYSTACK_H

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

const int defaultSize = 64;

template<class T>
class ArrayStack {
private:
    T *Arr;
    int top;
    int maxSize;             //当前容量



    int priority(char c); //判断优先级

    bool isOperator(char c); //判断是否为操作符

    double StringToDouble(string str); //字符串转double
public:
    ArrayStack();

    ~ArrayStack();

    bool push(T t);//向栈中添加一个t元素
    T peek();//向栈中取出一个元素
    T pop();//在栈中删除一个元素
    int size();//大小
    bool isEmpty();//判断是否为空
    bool ExpansionCapacity();     //扩展容量
    string ReverseString(string str);//使用该栈完成一个字符串的逆序输出
    bool CheckBracketMatching(string str);  //使用该栈完成表达式的括号是否匹配
    bool toEmpty(); //清空
    double ArithmeticExpressionEvaluation(string str);//算数表达式求值
    vector<string> ArithmeticToPostfix(string str);//算数表达式转后缀表达式
};

template<class T>
ArrayStack<T>::ArrayStack() {
    top = 0;
    Arr = new T[defaultSize];
    maxSize = defaultSize;
    if (!Arr) {
        cerr << "Arr malloc error!" << endl;
    }
}

template<class T>
ArrayStack<T>::~ArrayStack() {
    if (Arr) {
        delete[]Arr;
        Arr = NULL;
    }
}

template<class T>
bool ArrayStack<T>::push(T t) {
    if (top < maxSize) {
        Arr[top++] = t;
        return true;
    } else {
        ExpansionCapacity();
        Arr[top++] = t;
        return true;
    }
    return false;
}

template<class T>
T ArrayStack<T>::peek() {
    if (top > 0)
        return Arr[top - 1];
    return NULL;
}

template<class T>
T ArrayStack<T>::pop() {
    if (top > 0) {
        T ret = Arr[top - 1];
        top--;
        return ret;
    }
    return NULL;
}

template<class T>
int ArrayStack<T>::size() {
    return top;
}

template<class T>
bool ArrayStack<T>::isEmpty() {
    return !top;
}

template<class T>
string ArrayStack<T>::ReverseString(string str) {
    for (auto c:str) {
        push(c);
    }
    int ASsize = top;
    string ret;
    for (int i = 0; i < ASsize; ++i) {
        ret += pop();
    }
    return ret;
}

template<class T>
bool ArrayStack<T>::CheckBracketMatching(string str) {
    for (auto c:str) {
        if (c == '[' || c == '{' || c == '(') {
            push(c);
        }
        if (c == ']') {
            if (peek() == '[')
                pop();
            else
                return false;
        }
        if (c == '}') {
            if (peek() == '{')
                pop();
            else
                return false;
        }
        if (c == ')') {
            if (peek() == '(')
                pop();
            else
                return false;
        }
    }
    return isEmpty();
}

template<class T>
bool ArrayStack<T>::toEmpty() {
    if (Arr) {
        delete[]Arr;
        Arr = NULL;
    }
    top = 0;
    Arr = new T[maxSize];
    if (!Arr) {
        cerr << "Arr malloc error!" << endl;
    }
    return true;
}

template<class T>
bool ArrayStack<T>::ExpansionCapacity() {
    T *newStack = new T[maxSize + defaultSize];
    if (!newStack) {
        cerr << "Arr malloc error!" << endl;
    }
    maxSize += defaultSize;
    T *srcptr = Arr;
    T *destprt = newStack;
    int n = top;
    while (n--)*destprt++ = *srcptr++;
    delete[] Arr;
    Arr = newStack;
    return true;
}

template<class T>
double ArrayStack<T>::ArithmeticExpressionEvaluation(string str) {
    ArrayStack<double> result;
    for (string son_str:ArithmeticToPostfix(str)) {
        if (!isOperator(son_str.front())) {
            result.push(StringToDouble(son_str));
        } else if (isOperator(son_str.front())) {
            double R = result.pop();
            double L = result.pop();
            double sum = 0;
            switch (son_str.front()) {
                case '+': {
                    sum = L + R;
                }
                    break;
                case '-': {
                    sum = L - R;
                }
                    break;
                case '*': {
                    sum = L * R;
                }
                    break;
                case '/': {
                    sum = L / R;
                }
                    break;
                case '^': {
                    sum = pow(L, R);
                }
                default:
                    break;
            }
            result.push(sum);
        }
    }
    return result.pop();
}

template<class T>
int ArrayStack<T>::priority(char c) {
    if (c == '^')
        return 3;
    if (c == '*' || c == '/' || c == '%')
        return 2;
    if (c == '+' || c == '-')
        return 1;
    else
        return 0;
}

template<class T>
bool ArrayStack<T>::isOperator(char c) {
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
        return true;
    else
        return false;
}

template<class T>
vector<string> ArrayStack<T>::ArithmeticToPostfix(string str) {
    vector<string> postfix;
    string menber;
    for (auto c:str) {
        if ((c < 48 || c > 57) && c != '.') {
            if (!menber.empty())
                postfix.push_back(menber);
            menber.clear();
        }
        if (c == '(')
            push(c);
        else if (c == ')') {
            string temp;
            temp += pop();
            while (temp != "(") {
                if (!temp.empty())
                    postfix.push_back(temp);
                temp.clear();
                temp += pop();
            }
        } else if (isOperator(c)) {
            if (!isEmpty()) {
                string temp;
                temp += pop();
                while (priority(temp.front()) >= priority(c)) {
                    if (!temp.empty())
                        postfix.push_back(temp);
                    temp.clear();
                    temp += pop();
                }
                if (priority(temp.front()) < priority(c)) {
                    push(temp.front());
                    push(c);
                }
            } else
                push(c);
        } else {
            menber += c;
        }
    }
    if (!isEmpty()) {
        while (!isEmpty()) {
            string t;
            t += pop();
            if (!t.empty())
                postfix.push_back(t);
        }
        postfix.pop_back();
    }
    return postfix;
}

template<class T>
double ArrayStack<T>::StringToDouble(string str) {
    double db = 0;
    int count = 0;
    for (auto n:str) {
        if (n == '.')
            break;
        count++;
    }
    for (auto n:str) {
        if (n == '.')
            count = 0;
        if (n != '.')
            db += (n - 48) * pow(10, --count);
    }
    return db;
}

#endif //ARRAYSTACK_ARRAYSTACK_H
