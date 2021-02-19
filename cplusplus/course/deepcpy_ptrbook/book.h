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
using namespace std;
class Book {
    
private :
    int id;
public :
    Book();
    Book(int _id):id(_id){};
    Book(int _id,string _name):id(_id){};
    void show();
    //Book(const Book & ref_stud);
    ~Book(){ cout << "in book' deconstructor" << endl; }
};
class Person;

class Friendclass{

    public :
        void show(const Person & ps);

};
#endif
