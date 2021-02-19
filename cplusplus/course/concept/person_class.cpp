/*******************************************************************
 *
 *     File Name    :      person_class.cpp
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Tue 10 Nov 2020 09:16:29 AM CST
 *
 ******************************************************************/
#include "person_class.h"

int Person:: cunt = 0;

Person::Person()
{
    name = "non";
    gender = 1;
    age = 18;
    cunt ++;
   cout << "in persons' default constructor" << endl;
}

Person::Person(string _name)
{
   name = _name; 
   cout << "in persons' one para constructor" << endl;
}

Person::Person(string name,bool gender,int age)
{
    this->name = name;
    this->gender = gender;
    this->age = age;
    cunt++;
    cout << "in persons' three para constructor" << endl;
}

Person ::Person(const Person & ref_person)
{
    name = ref_person.name;
    gender = ref_person.gender;
    age = ref_person.age;
    cunt++;
    cout << "in persons' copy constructor" << endl;
}

void Person:: show() 
{
    cout << name << endl;
    cout << gender << endl;
    cout << age << endl;
    cout << cunt << endl;
}

void Person::get(enum CMD cmd) const
{
    cout << "const" << endl;
    switch(cmd)
    {
    case NAME:
        cout << name << endl;
        break;
    case GENDER:
        cout << gender << endl;
        break;
    case AGE:
        cout << age << endl;
        break;
    }
}

void Person::get(enum CMD cmd)
{
    switch(cmd)
    {
    case NAME:
        cout << name << endl;
        break;
    case GENDER:
        cout << gender << endl;
        break;
    case AGE:
        cout << age << endl;
        break;
    }
}

void Person:: set(void *str,enum CMD cmd)
{
    ;
}

void Person::getstatic()
{

    cout << "cunt = " << cunt << endl;

}

Person Person::operator=(const Person & ref_person)
{
    name = ref_person.name;
    gender = ref_person.gender;
    age = ref_person.age;
    cunt++;
    cout << "operator = " << endl;
    return *this;
}
Person::~Person()
{ 
    cunt--;
    cout << "in persons' deconstructor" << endl;
    cout << cunt << endl; 
}
