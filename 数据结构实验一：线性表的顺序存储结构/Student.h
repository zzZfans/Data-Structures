//
// Created by Zfans on 2019/09/10.
//

#ifndef SEQLISTBYCPP_STUDENT_H
#define SEQLISTBYCPP_STUDENT_H

#include<stdio.h>
#include<iostream>
#include<string>
#include<cassert>

using namespace std;

class Student {
public:
    //几种构造函数
    Student() = default;

    Student(const string &s);

    Student(const string &s, int chi, int ma);

    Student(const Student &);       //拷贝构造函数

    string name() const;

    int grade() const;    //返回总分
    double avg_grade() const;     //求平均值

    //几种重载运算符
    Student &operator+=(const Student &);

    friend istream &operator>>(istream &is, Student &item);

    friend ostream &operator<<(ostream &os, Student &item);

    friend bool operator==(const Student &lhs, const Student &rhs);

    friend bool operator!=(const Student &lhs, const Student &rhs);

    friend Student operator+(const Student &lhs, const Student &rhs);

    friend bool operator<(const Student &lhs, const Student &rhs);

    friend bool operator>(const Student &lhs, const Student &rhs);

    ~Student() = default;     //析构函数

private:
    string nameNo;      //姓名
    int chinese = 0;    //语文分数
    int math = 0;       //数学分数
    int sumgrade = 0;   //总分
};

Student::Student(const Student &item) :
        nameNo(item.nameNo),
        chinese(item.chinese),
        math(item.math),
        sumgrade(item.sumgrade) {}

double Student::avg_grade() const {
    if (sumgrade)
        return sumgrade / 2.0;
    else
        return 0;
}

Student &Student::operator+=(const Student &item) {
    chinese += item.chinese;
    math += item.math;
    sumgrade += item.sumgrade;
    return *this;
}

istream &operator>>(istream &is, Student &item) {
    is >> item.nameNo >> item.chinese >> item.math >> item.sumgrade;
    return is;
}

ostream &operator<<(ostream &os, Student &item) {
    os << item.name() << " " << item.chinese << " "
       << item.math << " " << item.sumgrade;
    return os;
}

bool operator==(const Student &lhs, const Student &rhs) {
    return lhs.name() == rhs.name();
}

bool operator!=(const Student &lhs, const Student &rhs) {
    return !(lhs == rhs);
}

Student operator+(const Student &lhs, const Student &rhs) {
    Student sum = lhs;
    sum += rhs;
    return sum;
}

bool operator<(const Student &lhs, const Student &rhs) {
    return lhs.sumgrade < rhs.sumgrade;
}

bool operator>(const Student &lhs, const Student &rhs) {
    return lhs.sumgrade > rhs.sumgrade;
}

int Student::grade() const { return sumgrade; }

Student::Student(const string &s) : nameNo(s) {}

Student::Student(const string &s, int chi, int ma) :
        nameNo(s), chinese(chi), math(ma), sumgrade(chi + ma) {}

string Student::name() const { return nameNo; }

#endif //SEQLISTBYCPP_STUDENT_H
