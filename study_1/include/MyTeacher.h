//
// Created by bob on 2019/10/13.
//

#pragma once //只包含一次

//这里宏的作用 防止重复导入
//#ifndef CPLUS_MYTEACHER_H
//#define CPLUS_MYTEACHER_H

class MyTeacher {
private:
    int m_age;
    char m_name[32];
public:

    void setAge(int age);

    int getAge();
};

//#endif //CPLUS_MYTEACHER_H
