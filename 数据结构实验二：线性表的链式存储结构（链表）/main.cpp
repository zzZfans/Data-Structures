#include <iostream>
#include "DoubleLinkedList.h"
#include "Student.h"

int main() {
    //创建双向链表对象 数据表项为Student
    DoubleLinkedList<Student> stuList;
    //向数据表中添加数据
    for (int i = 37; i <= 47; ++i) {
        Student s(to_string(i - 36), i - 10, i - 20);
        stuList.push_back(s);
    }

    cout << "打印链表：" << endl;
    stuList.DisplayData(); //打印链表
    cout << endl << "打印链表长度：";
    cout << endl << stuList.Length() << "个学生" << endl << endl;           //打印链表长度


    cout << "测试拷贝构造函数：" << endl;
    DoubleLinkedList<Student> stuList2(stuList);         //测试拷贝构造函数

    stuList2.DisplayData();
    cout << endl << stuList2.Length() << "个学生" << endl << endl;

    cout << "测试=重载：" << endl;
    DoubleLinkedList<Student> stuList3 = stuList2;         //测试=重载

    stuList3.DisplayData();
    cout << endl << stuList3.Length() << "个学生" << endl << endl;

    cout << "测试在指定元素前插入：" << endl;
    Student t1;
    Student t2("InsertBeforeTheSpecifiedElement", 32, 23);
    stuList3.getDataByIndex(3, t1);
    stuList3.InsertBeforeTheSpecifiedElement(t1, t2);    //测试在指定元素前插入
    stuList3.DisplayData();
    cout << endl << stuList3.Length() << "个学生" << endl << endl;

    cout << "测试指定元素之后插入：" << endl;
    Student t3;
    Student t4("InsertAfterTheSpecifiedElement", 45, 11);
    stuList3.getDataByIndex(3, t3);
    stuList3.InsertAfterTheSpecifiedElement(t3, t4);    //测试指定元素之后插入
    stuList3.DisplayData();
    cout << endl << stuList3.Length() << "个学生" << endl << endl;

    cout << "测试在指定位置完成插入：" << endl;
    Student t5("InsertAtTheSpecifiedLocation", 35, 41);
    stuList3.InsertAtTheSpecifiedLocation(2, t5);    //测试在指定位置完成插入
    stuList3.DisplayData();
    cout << endl << stuList3.Length() << "个学生" << endl << endl;

    cout << "测试逻辑删除：" << endl;
    stuList3.LogicalDeleteTheSpecifiedElement(t5);    //测试逻辑删除
    stuList3.LogicalDeleteElementAtSpecifiedLocation(3);
    stuList3.DisplayData();
    cout << endl << "逻辑删除的对象：" << endl;
    stuList3.DisplayLogicallyDeletedData();
    cout << endl << stuList3.Length() << "个学生" << endl << endl;

    cout << "测测试逻辑恢复：" << endl;
    stuList3.LogicalRecoveryOfSpecifiedElement(t5);//测试逻辑恢复
    stuList3.DisplayData();
    cout << endl << "逻辑删除的对象：" << endl;
    stuList3.DisplayLogicallyDeletedData();
    cout << endl << stuList3.Length() << "个学生" << endl << endl;

    cout << "测试物理删除：" << endl;
    stuList3.PhysicalDeleteTheSpecifiedElement(t5);//测试物理删除
    stuList3.DisplayData();
    cout << endl << "逻辑删除的对象：" << endl;
    stuList3.DisplayLogicallyDeletedData();
    cout << endl << stuList3.Length() << "个学生" << endl << endl;

    cout << "尝试恢复物理删除对象t5：" << endl;
    if (!stuList3.LogicalRecoveryOfSpecifiedElement(t5))
        cout << "恢复物理删除对象失败" << endl;    //失败提示
    stuList3.DisplayData();
    cout << endl << "逻辑删除的对象：" << endl;
    stuList3.DisplayLogicallyDeletedData();
    cout << endl << stuList3.Length() << "个学生" << endl << endl;

    cout << "测试修改：" << endl;
    Student t6("曾凡深", 100, 100);
    stuList3.ModifyDataForSpecifiedElement(t4, t6);
    stuList3.DisplayData();
    cout << endl << "逻辑删除的对象：" << endl;
    stuList3.DisplayLogicallyDeletedData();
    cout << endl << stuList3.Length() << "个学生" << endl << endl;

    cout << "测试文件读写：" << endl;
    string file = "student.txt";
    stuList3.WriteDataToFile(file);

    DoubleLinkedList<Student> stuList4;
    stuList4.ReadDataFromAFile(file);
    stuList4.DisplayData();
    cout << endl << "逻辑删除的对象：" << endl;
    stuList4.DisplayLogicallyDeletedData();
    cout << endl << stuList4.Length() << "个学生" << endl << endl;

    cout << "测试查询：" << endl;
    if (stuList4.QuerySpecifiedElement(t6))
        cout << t6 << " 存在" << endl << endl;

    cout << "测试优化冒泡排序：" << endl;
    stuList4.Sort();
    stuList4.DisplayData();
    cout << endl << "逻辑删除的对象：" << endl;
    stuList4.DisplayLogicallyDeletedData();
    cout << endl << stuList4.Length() << "个学生" << endl << endl;


    cout << "测试逻辑清空：" << endl;
    stuList4.toLogicalEmpty();
    stuList4.DisplayData();
    cout << endl << "逻辑删除的对象：" << endl;
    stuList4.DisplayLogicallyDeletedData();
    cout << endl << stuList4.Length() << "个学生" << endl << endl;

    cout << "测试物理清空：" << endl;
    stuList4.toPhysicalEmpty();
    stuList4.DisplayData();
    cout << endl << "逻辑删除的对象：" << endl;
    stuList4.DisplayLogicallyDeletedData();
    cout << endl << stuList4.Length() << "个学生" << endl << endl;

    return 0;
}