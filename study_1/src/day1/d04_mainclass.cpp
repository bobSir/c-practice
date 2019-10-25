//
// Created by bob on 2019/10/22.
//

#include <iostream>

using namespace std;

/**
 * 继承
 *
 * class Child : Parent{} //默认private
 * class Child : [权限访问]private|protect|public Parent{}
 * 访问控制权限 子类(派生类) 可以访问父类(基类)中的所有的非私有成员
 * 外部可见性 内部可见性
 */

class Parent {
public:
    int a;

    void print() {
        cout << "a = " << a << " b = " << b << " c = " << c << endl;
    }

protected:
    int b;
private:
    int c;

};

class Child : Parent {

};

class Child1 : private Parent {

};

class Child2 : protected Parent {
public:
    void test() {
        this->a = 1;
        this->b = 2;
//        this->c = 3;

        print();
    }
};

class Child3 : public Parent {

};

struct Base {
    int a;
    int b;
    int c;
};

int main01() {
    cout << "继承" << endl;

    Child child;
//    child.a = 10;
//    child.b = 10;
//    child.b = 10;

    Child2 child2;
//    child2.a = 10;
//    child2.b = 10;
//    child2.c = 10;

//    Child3 child3;
//    child3.a = 10;
//    child3.b = 10;
//    child3.c = 10;

    return 0;
}


class parent {

public:

    parent() {
//        cout << "构造 我是爸爸." << endl;
    }

    parent(const parent &p) {
//        cout << "拷贝构造 我是爸爸." << endl;
    }

    ~parent() {
        cout << "析构 我是爸爸." << endl;
    }

    virtual void print() {//多态  虚函数
        cout << "我是爸爸: " << a << endl;
    }

private:
    int a;
};

class child : public parent {
public:
    void print1() {
        cout << "我是儿子 " << c << endl;
    }

private:
    int c;
};

void testPrint(parent *base) {
    base->print();
}

void testPrint(parent &base) {
    base.print();
}

/**
 * c++ 类型的兼容性问题
 */
int main02() {
    cout << "兼容性问题演示" << endl;

    parent p1;
//    p1.print();

    child c1;
//    c1.print();
//    c1.print1();

    //兼容性问题，使用基类的指针(引用) 指向子类对象
    parent *p = nullptr;
    p = &c1;
    p->print();//是调用 c++编译器调用的时候 是根据指针的类型来判断

    //指针作为参数
    testPrint(&p1);
    testPrint(&c1);


    //引用作为函数参数
    testPrint(p1);
    testPrint(c1);

    //用子类对象 初始化父类对象
    parent p2 = c1;//向上转型
    // child c2 = p1;//error 向下转型 在特定的语义下可以强转

    testPrint(p2);

    return 0;
}

class Base1 {
public:
    Base1(int a = 0, int b = 0) {
        this->a = a;
        this->b = b;
        cout << "父类构造" << endl;
    }

    void print() {
        cout << "父类: " << a << " " << b << endl;
    }

    ~Base1() {
        cout << "父类析构" << endl;
    }

private:
    int a;
    int b;
};

class B2 : public Base1 {
public:

    /**
     * 初始化列表的使用情况
     * 1、成员变量是一个类类型，类还是有参的构造函数
     * 2、const 变量
     * 3、初始化父类的成员变量
     */
    B2(int a = 0, int b = 0, int c = 0) : Base1(a, b) {//初始化列表
        this->c = c;
        cout << "子类构造" << c << endl;
    }

    ~B2() {
        cout << "子类析构" << c << endl;
    }

private:
    int c;
};

void testObj() {
    B2 b2(1, 2, 3);
}

int main() {
    cout << "继承中的构造函数" << endl;
    testObj();
    return 0;
}

