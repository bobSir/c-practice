//
// Created by bob on 2019/10/27.
//

#include <iostream>

using namespace std;


/**
 * 多继承
 * 多态 virtual 虚函数 实现多态
 * c++类型转换
 * c++异常
 * c++ 泛型 template<typename T>
 */
class Base1 {
public:
    Base1(int b1) : b1(b1) {

    }

    void printB1() {
        cout << "b1:" << b1 << endl;
    }

private:
    int b1;
};

class Base2 {
public:
    Base2(int b2) : b2(b2) {

    }

    void printB2() {
        cout << "b2:" << b2 << endl;
    }

private:
    int b2;
};

class child : public Base1, public Base2 {//C++多继承
public:
    child(int b1, int b2, int c) : Base1(b1), Base2(b2), c(c) {//建议初始化列表初始化

    }

    void printC() {
        cout << "c:" << c << endl;
    }

private:
    int c;
};

int main01() {
    child c1(1, 2, 3);
    c1.printB1();
    c1.printB2();
    c1.printC();
    return 0;
}

class B {
public:
    int b;

};

class Base1_ : virtual public B {

};

class Base2_ : virtual public B {

};

class C : public Base1_, public Base2_ {
};

int main02() {
    C c;
    c.b = 100;//继承的二义性 解决方案 虚继承
    return 0;
}

//析构函数
class Test {
public:
    Test() {
        cout << "test 构造函数 " << endl;
    }

    virtual ~Test() {//虚析构
        cout << "test 析构函数 " << endl;
    }
};

class Test1 : public Test {
public:
    Test1() {
        cout << "test1 构造函数 " << endl;
    }

    virtual ~Test1() {
        cout << "test1 析构函数 " << endl;
    }
};

class Test2 : public Test1 {
public:
    Test2() {
        cout << "test2 构造函数 " << endl;
    }

    ~Test2() {
        cout << "test2 析构函数 " << endl;
    }
};

void objTest(Test *test) {
    delete test;
}

int main03() {

    Test2 *test2 = new Test2;
    objTest(test2);

    return 0;
}

//多态

class Parent {
public:
    Parent(int a = 0) : a(a) {

    }

    virtual void print() {//只有虚函数才能产生多态
        cout << "parent 1" << endl;
    }

    virtual void print2() {
        cout << "parent 2" << endl;
    }

private:
    int a = 0;
};

class D : public Parent {
public:
    D(int a = 0, int b = 0) : Parent(a), b(b) {

    }

    void print() {
        cout << "child D" << endl;
    }

    void print2() {
        cout << "child D 2" << endl;
    }

private:
    int b = 0;
};

void objTest1(Parent *parent) {
    parent->print();
    parent->print2();
}

int main04() {
    Parent p1;
    D child1;

    objTest1(&p1);
    objTest1(&child1);
    return 0;
}

//C++ 的抽象类 
class Shape {//抽象类 抽象类无法实例化
public:
    virtual void area() = 0;// =0 关键字 纯虚构函数

};

class Circle : public Shape {
public:
    Circle(int r) : r(r) {

    }

    virtual void area() {
        cout << " Circle area = " << 3.14 * r * r << endl;
    }

private:
    int r;
};

class Tri : public Shape {
public:
    Tri(int a, int h) : a(a), h(h) {

    }

    virtual void area() {
        cout << "Tri area = " << a * h / 2 << endl;
    }

private:
    int a;
    int h;
};

void getArea(Shape *shape) {
    shape->area();
}

int main05() {

    Shape *base = nullptr;
    Circle c1(10);
    Tri tri(3, 6);
    base = &c1;
//    base->area();//发生多态

    getArea(&tri);

    return 0;
}

//c++ 类型转换
/**
 * static_cast<T>(expre)
 * dynamic_cast<T>(expre)
 * const_cast<T>(expre)
 * reinterpret_cast<T>(expre)
 */

//static_cast<T>(expre)
int main06() {

    double d = 3.14;
    int a = (int) d;
    int b = int(d);

    int b1 = static_cast<int>(d);

    int a1 = 3;
    const int b2 = (const int) a1;
    const int c1 = static_cast<const int>(a1);


    return 0;
}

class B1 {
public:
    void func() {}

    virtual void print();

};

class D1 : public B1 {

};


void func(int *i) {}

//const_cast<T>(expre)
int main08() {
    const int a = 10;
    func(const_cast<int *>(&a));

    return 0;
}

//reinterpret_cast<T>(expre)
int main09() {
    //把指针转换成任何类型的指针
    int a = 0x76;//ASCII v
    printf("a = %d,addr=%p\n", a, &a);
    int *ap = &a;

    char *c = reinterpret_cast<char *>(ap);
    printf("c=%c,addr=%p\n", *c, c);

    return 0;
}


//dynamic_cast<T>(expre)
int main07() {
    D1 *d = new D1;
    B1 *b1 = new B1;
    //向上
    B1 *b12 = dynamic_cast<B1 *>(d);
    cout << "b12: " << b12 << endl;
    //向下 基类必须要有虚函数才能转
    D1 *d1 = dynamic_cast<D1 *>(b1);
    cout << "d1: " << d1 << endl;//NULL 转换失败


    return 0;
}

//C++ 异常

class F {
public:
    ~F() {
        cout << "~F" << endl;
        throw 1;//析构函数不要抛出异常
    }
};

void f1() throw(int) {
    int a;
    throw 2;
}

void f2() throw(int) {
    F f;
    f1();
}

void f3() {
    try {
        f2();
    } catch (int i) {

    }

}

//C++ 模板

template<typename T>
//模板函数
void swap1(T &a, T &b) {
    T temp(a);
    a = b;
    b = temp;
}

class Printer {
public:
    template<typename T>
    void print(const T &t) {
        cout << t << endl;
    }
};

int main() {

    int i = 1;
    int j = 2;
    swap1(i, j);
    cout << "i = " << i << "j = " << j << endl;
    double n = 1.0;
    double m = 2.0;
    swap1(n, m);
    Printer p;
    p.print(i);
    p.print(n);
    return 0;
}


