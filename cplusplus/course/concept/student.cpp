/*******************************************************************
 *
 *     File Name    :      student.cpp
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Wed 11 Nov 2020 10:03:17 AM CST
 *     Description  :       Hello Word in C++ , GUN-style
 *
 ******************************************************************/

#include "student.h"

Student::Student()
{
    cout << "in students' default constructor" << endl;
}

void Student::show()
{
    cout << id << endl;
    this->Person::show();
}
 
Student::Student(const Student & ref_stud) : Person(ref_stud)
{
    this->id = ref_stud.id;
    cout << "in students' default constructor" << endl;
}
 
