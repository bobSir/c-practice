//
// Created by bob on 2019/10/17.
//

#include <iostream>

using namespace std;

class A {
public:

    A() {

    }

    A(int a) {
        cout << "A 构造函数" << endl;
    }

    ~A() {
        cout << "A 析构函数" << endl;
    }

private:
    int m_a;
};

/**
 * 构造函数初始化列表
 * 语法: className():mi(XXX),m2(XXX) -- 为了解决在B类中组合了一个A类对象(A重写了有参构造器)
 */
class B {
public:
    B(A a) : m_a(2) {//构造函数的初始化列表
        m_b = 3;
        m_a = a;
    }

    B() : m_a2(1), m_a1(2), m_a(3) {

    }

private://初始化列表里面初始化的顺序是按照成员变量声明的顺序。
    int m_b;
    A m_a;
    A m_a1;
    A m_a2;

    const int c = 10;//常量
};

/**
 * 要初始化B的时候 必须要先初始化B中的A
 *
 * 1、默认的无参构造函数，没有定义构造函数时，会默认有个无参的构造器
 */
int main() {
    B b1;


    return 0;
}

/**
 * 构造函数里面再去调用构造函数
 */
class Test {
public:
    Test(int a, int b, int c) {
        this->a = a;
        this->b = b;
        this->c = c;
    }

    Test(int a, int b) {
        this->a = a;
        this->b = b;
        Test(a, b, 3);//不要在构造函数里再去调用构造器 匿名对象会被析构
    }

    void print() {
        cout << a << " -- " << b << " -- " << c << endl;
    }

    ~Test() {

    }

private:
    int a;
    int b;
    int c;
};

/**
 * new delete /new[] delete[]
 * 对象的动态创建和释放
 * 在栈上创建对象和释放对象 与 在堆上创建对象和释放对象的区别
 * 栈
 * 1、在栈上创建的对象，一经创建，对象的大小是无法改变的
 * 2、在栈上的对象 系统自动创建和销毁
 *
 * 堆
 * 1、堆上申请的内存空间 可以动态调整
 * 2、堆上申请的空间，必须自己申请与释放
 *
 * malloc / calloc free C语言 是函数
 *
 * new delete  C++的语法 是操作符 不是函数
 *
**/

int main01() {

    int *p = (int *) malloc(sizeof(int));//在堆上申请一块内存 C
    *p = 10;
    free(p);
    p = nullptr;

    int *p1 = new int;//在堆上申请内存 C++
    *p1 = 20;
    delete p1;
    p1 = nullptr;

    int *p2 = new int(30);
    delete (p2);


    int *array1 = new int[10];
    array1[2] = 3;
    delete[] array1;

    return 0;
}