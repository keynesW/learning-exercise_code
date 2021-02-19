/*******************************************************************
 *
 *     File Name    :      person_class.h
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog： :      http://www.    .com/ 
 *     Created Time :      Tue 10 Nov 2020 09:16:29 AM CST
 *
 ******************************************************************/
#ifndef _CLASS_PERSON_H_
#define _CLASS_PERSON_H_

#include <iostream>
#include <string>
#include "book.h"


using namespace std;

enum CMD{NAME = 1,
    GENDER,
    AGE
};

class Person{
    friend class Friendclass;
private:
    string name;
    bool   gender;
    int    age;
    static int cunt ;
    static const int test = 5;
    Book *pbk;

    void prv_tst();
    void prv_tst(char * ptr_c);
    char * prv_tst(char * ptr_c,int n);

public:
    Person();
    Person(string _name);
    //Person(string name,bool gender,int age );
    Person(string name,bool gender,int age );
    Person(const Person & ref_person);
    ~Person();

    void show();
    Person & operator=( const Person & ref_person );
    //void operator=( const Person & ref_person );
    //Person operator=( const Person & ref_person );
    //Person & operator=( const Person & ref_person );
    void friend  borrow(Person & ps);

};

#endif

