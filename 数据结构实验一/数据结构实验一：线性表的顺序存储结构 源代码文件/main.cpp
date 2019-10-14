#include <iostream>
#include "SeqList.h"
#include "Student.h"

int main() {

    //创建顺序表对象 数据表项为Student

    SeqList<Student> stu01;

    //向数据表中添加数据

    for (int i = 37; i <= 100; ++i) {
        Student s(to_string(i - 36), i - 10, i - 20);
        stu01.push_back(s);
    }

    stu01.DisplayData();                 //打印顺序表
    cout << endl << stu01.Length() << endl;           //打印顺序表长度

    SeqList<Student> stu02(stu01);         //测试拷贝构造函数
    stu02.DisplayData();
    cout << endl << stu02.Length() << endl;

    SeqList<Student> stu03 = stu02;         //测试=重载
    stu03.DisplayData();
    cout << endl << stu03.Length() << endl;

    //测试在指定元素前插入

    Student t1("InsertBeforeTheSpecifiedElement", 32, 23);
    Student t2;
    int index01 = 64;
    stu03.getDataByIndex(index01, t2);
    stu03.InsertBeforeTheSpecifiedElement(t2, t1);
    stu03.DisplayData();
    cout << endl << stu03.Length() << endl;

    //测试指定元素之后插入

    Student t3("InsertAfterTheSpecifiedElement", 56, 76);
    Student t4;
    int index02 = 65;
    stu03.getDataByIndex(index02, t4);
    cout << stu03.LocateTheOrdinalNumberOfTheSpecifiedElement(t4) << endl;
    stu03.InsertAfterTheSpecifiedElement(t4, t3);
    stu03.DisplayData();
    cout << endl << stu03.Length() << endl;

    //测试在指定位置完成插入

    Student t5("InsertAtTheSpecifiedLocation", 12, 21);
    int index03 = 1;
    stu03.InsertAtTheSpecifiedLocation(index03, t5);
    stu03.DisplayData();
    cout << endl << stu03.Length() << endl;

//测试逻辑删除

    stu03.LogicalDeleteTheSpecifiedElement(t5);
    stu03.DisplayData();
    cout << endl << "逻辑删除的对象：" << endl;
    stu03.DisplayLogicallyDeletedData();
    cout << endl << stu03.Length() << endl;

    stu03.LogicalDeleteElementAtSpecifiedLocation(index03);
    stu03.DisplayData();
    cout << endl << "逻辑删除的对象：" << endl;
    stu03.DisplayLogicallyDeletedData();
    cout << endl << stu03.Length() << endl;

    //测试逻辑恢复
    stu03.LogicalRecoveryOfSpecifiedElement(t5);
    stu03.DisplayData();
    cout << endl << "逻辑删除的对象：" << endl;
    stu03.DisplayLogicallyDeletedData();
    cout << endl << stu03.Length() << endl;

    //测试物理删除

    stu03.PhysicalDeleteTheSpecifiedElement(t5);
    stu03.PhysicalDeleteElementAtSpecifiedLocation(index03);
    stu03.DisplayData();
    cout << endl << stu03.Length() << endl;

    // 尝试恢复物理删除对象

    if (!stu03.LogicalRecoveryOfSpecifiedElement(t5))
        cout << "尝试恢复物理删除对象失败" << endl; //失败提示
    stu03.DisplayData();
    cout << endl << stu03.Length() << endl;

    //排序测试

    stu03.Sort();
    stu03.DisplayData();
    cout << endl << stu03.Length() << endl;

    //测试修改
    Student t6("曾凡深", 100, 100);
    Student t7;
    stu03.getDataByIndex(index01, t7);
    stu03.ModifyDataForSpecifiedElement(t7, t6);
    stu03.DisplayData();
    cout << endl << stu03.Length() << endl;

    //测试文件读写
    string sf = "student.txt";
    stu03.WriteDataToFile(sf);   //写

    SeqList<Student> stu04;
    stu04.ReadDataFromAFile(sf);    //读
    cout << "stu04:" << endl;
    stu04.DisplayData();
    cout << endl << stu04.Length() << endl;

    //测试逻辑清空
    stu04.toLogicalEmpty();
    cout << stu04.Length() << endl;
    cout << "逻辑删除的对象：" << endl;
    stu04.DisplayLogicallyDeletedData();

    //逻辑恢复一个对象

    Student t8("曾凡深", 100, 100);
    stu04.LogicalRecoveryOfSpecifiedElement(t8);
    cout << endl << "逻辑恢复的对象：" << endl;
    stu04.DisplayData();

    //测试查询

    cout << endl << "---" << stu04.QuerySpecifiedElement(t8) << "---" << endl;

    //测试物理清空

    stu04.toPhysicalEmpty();
    cout << endl << "物理清空后长度为：" << stu04.Length() << endl;
    stu04.DisplayData();
    stu04.DisplayLogicallyDeletedData();

    return 0;
}