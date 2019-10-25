//
// Created by bob on 2019/10/22.
//

#ifndef CPLUS_MYARRAY_H
#define CPLUS_MYARRAY_H

//&引用  *地址  赋值

/**
 * 配套使用
 * new/delete  new[]/delete[]  在C++中是关键字
 * malloc/free 是C库的函数
 *
 *
 */

class MyArray {
public:
    MyArray(int size);

    MyArray(const MyArray &array);

    ~MyArray();

    void setData();

    int getData();

    int size();

};

//重载 [] = == !=

#endif //CPLUS_MYARRAY_H
