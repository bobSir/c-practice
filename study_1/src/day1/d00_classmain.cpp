//
// Created by bob on 2019/10/13.
//
#include <iostream>

#include "../../include/MyTeacher.h"

using namespace std;

// :: 作用域限定运算符

int a;

int main() {
    MyTeacher t1{};
    t1.setAge(11);
    t1.getAge();
    cout << "t1.age: " << t1.getAge() << endl;

    float a;
    a = 33;

    ::a = 5;
    return 0;
}