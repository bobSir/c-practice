//
// Created by bob on 2019/10/20.
//
#include <iostream>

using namespace std;

/**
 * 静态 非静态
 * 友元函数 友元类
 * 运算符符重载
 */



class Test {
public:
    void printC() {
        cout << "C = " << c << endl;
    }

    void addC() {
        c = c + 1;
    }

    int getC() {
        return c;
    }

private:
    int a;
    int b;
    static int c;
};

int main0() {
    //静态成员变量如何初始化
    Test t1;
    //Test::c = 10； public静态方法可以用作用域限定符赋值

    return 0;
}

class Test1 {
public:

    friend class Test2;//友元类 在test2中可以访问test1类中私有的成员变量 函数

    Test1() {

    }

    Test1(int a, int b) {
        this->a = a;
        this->b = b;
    }

    friend void add1(Test1 t);//友元函数的声明方式 friend关键字

    void add() {
        a = a + b;
        cout << "a = " << a << endl;
    }

private:
    int a;
    int b;

};

class Test2 {
public:
    //友元函数是没有this指针的
    void setA(int a) { //Test1中声明Test2中友元函数 在test2中可以访问test1类中私有的成员变量 函数
        t1.a = a;
        t1.b = a;
    }

    void print() {

    }

private:
    Test1 t1;
};


/**
 * 在类的外部 使用类里面的私有成员变量
 */
void add1(Test1 t) {
    t.a = t.a + t.b;
    cout << "a = " << t.a << endl;
}

/**
 * 类的友元函数
 * 1、定义在类的外部
 * 2、有权访问类的所有private/protected的成员
 *
 * 为什么要设计友元函数 友元类
 * 1、java的反射 可以直接修改类的私有属性
 * 2、开了个后门
 */

int main01() {
    //友元函数&友元类

    Test2 t2;
    t2.setA(2);
    t2.print();

    return 0;
}

/**
 * java String "abc"+"def"
 * c/c++ strcat
 *
 * 运算符符重载
 * 可以使得用户自定义的数据使用起来更简单
 *
 *  分类
 *  //按照实现方式
 * 1、运算符重载为成员函数
 * 2、运损符重载为全局函数(友元)
 *
 *  //按照 运算符需要的操作数
 * 1、一元操作符 ++ --
 * 2、二元运算符 数学运算符(+ - * /)
 *
 *
 */

class Complex {
public:

    Complex(int a = 0, int i = 0) {
        this->a = a;
        this->i = i;
    }

    void print() {
        cout << "Complex: (" << a << "+" << i << ")" << endl;
    }

    Complex &operator--() {
        this->a--;
        this->i--;
        return *this;
    }

    Complex operator--(int) {
        Complex temp = *this;
        this->a--;
        this->i--;
        return temp;
    }

private:
    friend Complex myAdd(Complex c1, Complex c2);

    friend Complex operator+(Complex c1, Complex c2);

    friend Complex &operator++(Complex &c);

    friend Complex operator++(Complex &c, int);

    friend ostream &operator<<(ostream &out, Complex &c);

    int a;
    int i;
};

Complex myAdd(Complex c1, Complex c2) {
    Complex tem(c1.a + c2.a, c1.i + c2.i);
    return tem;
}

Complex operator+(Complex c1, Complex c2) {
    Complex tem(c1.a + c2.a, c1.i + c2.i);
    return tem;
}

Complex &operator++(Complex &c) {
    c.a++;
    c.i++;
    return c;
}

//后置++
Complex operator++(Complex &c, int) {//占位参数 1、兼容C不规范的写法
    Complex temp = c;
    c.a++;
    c.i++;
    return temp;
}

//重载为友元函数 无法重载为成员函数
//void operator<<(ostream &out, Complex &c) {
//    out << "Complex: (" << c.a << "+" << c.i << ")" << endl;
//}
ostream &operator<<(ostream &out, Complex &c) {
    out << "Complex: (" << c.a << "+" << c.i << ")" << endl;
    return out;
}

class Name {
public:
    Name(char *pName) {
        size = strlen(pName);
        this->pName = (char *) malloc(100);
        strcpy(this->pName, pName);
    }

    Name(const Name &name) {
        size = name.size;
        this->pName = (char *) malloc(100);
        strcpy(this->pName, name.pName);
    }

    ~Name() {
        if (pName != nullptr) {
            free(pName);
            pName = nullptr;
            size = 0;
        }
    }

    Name &operator=(Name &obj) {
        //深拷贝
        if (this->pName != nullptr) {
            delete[] pName;
            size = 0;
        }
        size = obj.size;
        pName = new char[size + 1];
        strcpy(pName, obj.pName);
        return *this;
    }

public:
    char *pName;
    int size;
};

void objTest() {
    Name obj1("");
    Name obj2 = obj1;//默认拷贝构造函数 浅拷贝

    cout << " obj2 = " << obj2.pName << endl;
    // 分析 Name& operator = (Name& obj)
}

int main05() {
    //运算符加深
    objTest();

    cout << "main finish -- " << endl;
    return 0;
}

int main03() {
    //后置++
    Complex c1(6, 6);
    c1.print();
    c1++;
    c1.print();
    c1--;
    c1.print();
    return 0;
}

int main04() {
    //运算符重载加深

    Complex c1(1, 2);
    cout << c1 << "haha" << endl;
    return 0;
}

int main02() {
    //运算符重载

//    int a = 0;
//    int b = 0;
//    int c = 0;
//    c = a + b;

    //复数 实数+虚数
    Complex c1(1, 2);
    c1.print();
    Complex c2(3, 4);

    Complex sum;//sum c1+c2 c++编译器如何支持操作符重载
    sum = myAdd(c1, c2);

//    sum = c1 + c2;
//    sum.print();
    /**
     * 不可以重载的运算符
     * 1、 . :  成员访问运算符
     * 2、 .* ->* 成员指针访问运算符
     * 3、 ::  作用域运算符
     * 4、 sizeof  长度运算符
     * 5、 ?:  三目运算符
     * 6、 # 预处理符
     */
    // new delete new[] delete[] 不可以

    //重载运算符步骤

    //一元运算符重载
    int a = 10;
    int b = 2;
    a++;
    ++b;

    Complex c5(3, 3);
    ++c5;//重载++
    c5.print();
    --c5;
    c5.print();

    return 0;
}

class Test3 {
public:
    int i;

    Test3(int i) {
        this->i = i;
    }

    Test3 &operator+(Test3 &t) {
        cout << "重载+" << endl;
        Test3 temp(0);
        i = i + t.i;
        return *this;
    }

    bool operator&&(Test3 t) {
        cout << "重载&&" << endl;
        return i && t.i;
    }
};

int main() {
    cout << "运算符重载" << endl;

    //&& || 重载  最好不好重载这两个运算符 无法处理逻辑短路原则

    Test3 t1 = 0;
    Test3 t2(1);
    if ((t1 + t2) && t1) {

    }
    cout << "===" << endl;
    if (t1 && (t1 + t2)) {

    }

    return 0;
}