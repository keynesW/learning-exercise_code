/*******************************************************************
 *
 *     File Name    :      person_class.h
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Tue 10 Nov 2020 09:16:29 AM CST
 *
 ******************************************************************/
#ifndef _CLASS_STUDENT_H_
#define _CLASS_STUDENT_H_

#include <iostream>
#include <string>
#include "person_class.h" 
class Student : public Person{
    
private :
    int id;
public :
    Student();
    Student(int _id):id(_id){};
    Student(int _id,string _name):id(_id){};
    void show();
    Student(const Student & ref_stud);
    ~Student(){ cout << "in students' deconstructor" << endl; }
};
#endif
