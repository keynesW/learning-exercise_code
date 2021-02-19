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

private:
    string name;
    bool   gender;
    int    age;
    static int cunt ;
    static const int test = 5;
    Book bk;
public:
    int tst;
    //const int tst;
public:
    Person();
    Person(string _name);
    Person(string name,bool gender,int age );
    Person(string _name,bool _gender) :name(_name),gender(_gender)
    {
        // name = _name;
        // gender =_gender;
        cunt ++;
    }
    Person(const Person & ref_person);
    ~Person();

    void show();
    void get(enum CMD cmd)const;
    void get(enum CMD cmd);
    void set(void * value,enum CMD cmd);
    static void getstatic();
    Person operator=( const Person & ref_person );
    /*
       {
       cout << name << ' ' << gender << ' ' << age << endl;
       }
       */

};

#endif

