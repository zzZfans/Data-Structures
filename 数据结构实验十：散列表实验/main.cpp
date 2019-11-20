#include <iostream>
#include <fstream>
#include "ClosedHashTable.h"
#include "Contact.h"
#include "OpenHashTable.h"
#include <cmath>

using namespace std;

unsigned long long userNameHash(const string &str) {
    unsigned long long key = 0;
    int i = str.size() - 1;
    for (auto ele:str) {
        key += ele * pow(10, i--);
    }
    return key;
}

int main() {
    cout << "《测试数据共1000组，从test.txt文件中读取》" << endl;

    cout << "---------------------------------------------------------------------闭散列表-线性探测法-以电话号码为关键字" << endl;
    cout << "使用闭散列表的构造方法，采用线性探测法解决冲突：" << endl;
    cout << "以电话号码为关键字建立散列表：" << endl << endl;

    ifstream in01(R"(C:\Users\10944\Desktop\HashTable\test.txt)"); //创建输入流对象 文件路径因个人电脑而异

    ClosedHashTable<Contact> closedHT01(79);  //设置质数79为散列函数除数

    //插入1000条数据项
    Contact temp01;
    while (in01 >> temp01) {
        closedHT01.Insert(temp01.getTellNumber(), temp01);
    }

    cout << "测试搜索函数，13320572294为测试数据中的第100条数据：" << endl;
    if (closedHT01.Search(13320572294, temp01)) {//搜索成功返回true 并将搜索到的信息赋值给temp 未搜索成功返回false
        cout << "搜索13320572294成功，搜索结果：" << temp01 << endl;
    } else
        cout << "搜索13320572294失败！" << endl;

    cout << "测试删除函数，删除13320572294，13320572294为测试数据中的第100条数据：" << endl;
    if (closedHT01.Remove(13320572294)) {
        cout << "删除13320572294成功！" << endl << endl;
    } else
        cout << "删除13320572294失败！" << endl << endl;

    cout << "测试搜索函数，13320572294为测试数据中的第100条数据：" << endl;
    if (closedHT01.Search(13320572294, temp01)) {//搜索成功返回true 并将搜索到的信息赋值给temp 未搜索成功返回false
        cout << "搜索13320572294成功，搜索结果：" << temp01 << endl;
    } else
        cout << "搜索13320572294失败！" << endl;

    cout << "---------------------------------------------------------------------闭散列表-线性探测法-以用户名为关键字" << endl;
    cout << "使用闭散列表的构造方法，采用线性探测法解决冲突：" << endl;
    cout << "以用户名为关键字建立散列表：" << endl << endl;

    ifstream in02(R"(C:\Users\10944\Desktop\HashTable\test.txt)"); //创建输入流对象 文件路径因个人电脑而异

    ClosedHashTable<Contact> closedHT02(79);  //设置质数79为散列函数除数

    //插入1000条数据项
    Contact temp02;
    while (in02 >> temp02) {
        closedHT02.Insert(userNameHash(temp02.getUserName()), temp02);
    }

    cout << "测试搜索函数，PQDATQHNVFOEVNO为测试数据中的第600条数据：" << endl;
    if (closedHT02.Search(userNameHash("PQDATQHNVFOEVNO"), temp02)) {//搜索成功返回true 并将搜索到的信息赋值给temp 未搜索成功返回false
        cout << "搜索PQDATQHNVFOEVNO成功，搜索结果：" << temp02 << endl;
    } else
        cout << "搜索PQDATQHNVFOEVNO失败！" << endl;

    cout << "测试删除函数，删除PQDATQHNVFOEVNO，PQDATQHNVFOEVNO为测试数据中的第600条数据：" << endl;
    if (closedHT02.Remove(userNameHash("PQDATQHNVFOEVNO"))) {
        cout << "删除PQDATQHNVFOEVNO成功！" << endl << endl;
    } else
        cout << "删除PQDATQHNVFOEVNO失败！" << endl << endl;

    cout << "测试搜索函数，PQDATQHNVFOEVNO为测试数据中的第600条数据：" << endl;
    if (closedHT02.Search(userNameHash("PQDATQHNVFOEVNO"), temp02)) {//搜索成功返回true 并将搜索到的信息赋值给temp 未搜索成功返回false
        cout << "搜索PQDATQHNVFOEVNO成功，搜索结果：" << temp02 << endl;
    } else
        cout << "搜索PQDATQHNVFOEVNO失败！" << endl;

    cout << "---------------------------------------------------------------------开散列表-拉链法-以电话号码为关键字" << endl;
    cout << "使用开散列表的构造方法，采用拉链法解决冲突：" << endl;
    cout << "以电话号码为关键字建立散列表：" << endl << endl;

    ifstream in03(R"(C:\Users\10944\Desktop\HashTable\test.txt)"); //创建输入流对象 文件路径因个人电脑而异

    OpenHashTable<Contact> openHT01(79);  //设置质数79为散列函数除数

    //插入1000条数据项
    Contact temp03;
    while (in03 >> temp03) {
        openHT01.Insert(temp03.getTellNumber(), temp03);
    }

    cout << "测试搜索函数，13345982139为测试数据中的第300条数据：" << endl;
    if (openHT01.Search(13345982139, temp03)) {//搜索成功返回true 并将搜索到的信息赋值给temp 未搜索成功返回false
        cout << "搜索13345982139成功，搜索结果：" << temp03 << endl;
    } else
        cout << "搜索13345982139失败！" << endl;

    cout << "测试删除函数，删除13345982139，13345982139为测试数据中的第300条数据：" << endl;
    if (openHT01.Remove(13345982139)) {
        cout << "删除13345982139成功！" << endl << endl;
    } else
        cout << "删除13345982139失败！" << endl << endl;

    cout << "测试搜索函数，13345982139为测试数据中的第300条数据：" << endl;
    if (openHT01.Search(13345982139, temp03)) {//搜索成功返回true 并将搜索到的信息赋值给temp 未搜索成功返回false
        cout << "搜索13345982139成功，搜索结果：" << temp03 << endl;
    } else
        cout << "搜索13345982139失败！" << endl;

    cout << "---------------------------------------------------------------------开散列表-拉链法-以用户名为关键字" << endl;
    cout << "使用开散列表的构造方法，采用拉链法解决冲突：" << endl;
    cout << "以用户名为关键字建立散列表：" << endl << endl;

    ifstream in04(R"(C:\Users\10944\Desktop\HashTable\test.txt)"); //创建输入流对象 文件路径因个人电脑而异

    OpenHashTable<Contact> openHT02(79);  //设置质数79为散列函数除数

    //插入1000条数据项
    Contact temp04;
    while (in04 >> temp04) {
        openHT02.Insert(userNameHash(temp04.getUserName()), temp04);
    }

    cout << "测试搜索函数，IVTJEUNZLGAT为测试数据中的第800条数据：" << endl;
    if (openHT02.Search(userNameHash("IVTJEUNZLGAT"), temp04)) {//搜索成功返回true 并将搜索到的信息赋值给temp 未搜索成功返回false
        cout << "搜索IVTJEUNZLGAT成功，搜索结果：" << temp04 << endl;
    } else
        cout << "搜索IVTJEUNZLGAT失败！" << endl;

    cout << "测试删除函数，删除IVTJEUNZLGAT，IVTJEUNZLGAT为测试数据中的第800条数据：" << endl;
    if (openHT02.Remove(userNameHash("IVTJEUNZLGAT"))) {
        cout << "删除IVTJEUNZLGAT成功！" << endl << endl;
    } else
        cout << "删除IVTJEUNZLGAT失败！" << endl << endl;

    cout << "测试搜索函数，IVTJEUNZLGAT为测试数据中的第800条数据：" << endl;
    if (openHT02.Search(userNameHash("IVTJEUNZLGAT"), temp04)) {//搜索成功返回true 并将搜索到的信息赋值给temp 未搜索成功返回false
        cout << "搜索IVTJEUNZLGAT成功，搜索结果：" << temp04 << endl;
    } else
        cout << "搜索IVTJEUNZLGAT失败！" << endl;

    cout << "---------------------------------------------------------------------对比分析这两种不同解决冲突方法的平均搜索长度值的变化" << endl;

    int flag = 1;
    cout << "线性探测法的平均搜索长度值的变化（100次~200次~300次···本测试环境每次探测散列表中元素都+1）：" << endl;
    for (auto ele:closedHT01.getAsl()) {
        flag++;
        if (flag % 100 == 0)
            cout << ele << " ";
    }

    flag = 1;
    cout << endl << "拉链法的平均搜索长度值的变化（100次~200次~300次···本测试环境每次探测散列表中元素都+1）：" << endl;
    for (auto ele:openHT01.getAsl()) {
        flag++;
        if (flag % 100 == 0)
            cout << ele << " ";
    }

    return 0;
}