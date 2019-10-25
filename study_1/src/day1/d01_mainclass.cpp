//
// Created by bob on 2019/10/15.
//
#include <iostream>

using namespace std;

/**
 * 构造函数
 * 1、没有返回值
 * 2、函数名称和类名相同
 * 析构函数
 *
 */
class Test {
public:

    Test() {//构造函数
        a = 10;
        p = (char *) malloc(100); //给p变量在堆区分配一块内存 -- colloc
        strcpy(p, "abcd");

        cout << "构造函数" << endl;
    }

    ~Test() {//析构函数 释放资源工作
        if (p != nullptr) {
            free(p);
            p = nullptr;
        }
        cout << "析构函数" << endl;
    }

    void print() {//成员函数
        cout << "a: " << a << "p:" << p << endl;
    }

protected:
    int j;
private:
    int a;
    char *p;
};

/**
 * 构造函数分类
 */
class Test2 {
public:

    void init(int a, int b) {
        m_a = a;
        m_b = b;
    }

    Test2() {
        m_a = 0;
        m_b = 0;
        cout << "无参构造函数:" << m_a << " -- " << m_b << endl;
    }

    Test2(int a) {
        m_a = 0;
        m_b = 0;
        cout << "无参构造函数:" << m_a << "" << m_b << endl;
    }

    Test2(int a, int b) {
        m_a = a;
        m_b = b;
    }

    Test2(const Test2 &obj) {//拷贝构造函数
        m_a = obj.m_a;
        m_b = obj.m_b;
        cout << "拷贝构造函数:" << m_a << "" << m_b << endl;
    }

    ~Test2() {
        cout << "析构函数" << m_a << "" << m_b << endl;
    }

    void print() {
        cout << "print:" << m_a << "" << m_b << endl;
    }

    int getA() {
        return m_a;
    }

private:
    int m_a;
    int m_b;
};

/**
 * 默认的拷贝函数只可以完成对象的数据成员的简单复制-传值
 * 当对象的数据资源是由指针指向堆时，我们需要考虑深拷贝
 */
class Test3 {
public:
    Test3(const Test3 &t) {
        a = t.a;
        p = (char *) malloc(100);
        strcpy(p, t.p);
    }

    ~Test3() {

    }

private:
    int a;
    char *p;
};

void objTest() {
    Test t1;
    t1.print();
}

void objTest1() {
    Test2 t1;

    //1、括号法
    Test2 t2(1);

    Test2 t3(1, 2);

    //=号法 c++对" = " 功能增强，调用了构造函数
    Test2 t4 = (4, 5);//单参构造器
    Test2 t5 = 9;//

    //3、直接调用构造函数，手动调用的构造函数
    Test2 t6 = Test2(1, 2);

    t1 = t5;//把t5 copy 给t1 //赋值操作

    Test2 t7 = t5;//拷贝构造函数

    Test2 t8(t5);
}

void objTest2() {
    Test2 t1;
    t1.init(1, 2);

    Test2 tArr[2];
    tArr[0].init(1, 2);
}

/**
 * 拷贝构造函数的调用时机
 * @param t
 * 1、实参初始化形参的时候 会调用拷贝构造函数
 */
void copyTest(Test2 t) {
    cout << t.getA() << endl;
}

void objTest4() {

    Test2 t1(1, 2);
    Test2 t2 = t1;
    t2.print();

    copyTest(t2);//实参初始化形参的时候 会调用拷贝构造函数
}

Test2 getTest2() {
    Test2 t(4, 5);
    return t;
}

void objTest5() {
    Test2 t1 = getTest2();//t1初始化, 创建一个匿名对象 扶正 析构一次
    t1.print();
}

void objTest6() {
    Test2 t1(1, 2);//t1初始化 析构一次
    t1 = getTest2();//赋值 析构一次
    t1.print();
}

void objTest7() {

}

int main() {
    objTest();
    objTest1();
    objTest2();
    return 0;
}