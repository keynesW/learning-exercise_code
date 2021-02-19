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

void Person::prv_tst()
{
    cout<<"in prv_tst"<< endl;

}
void Person::prv_tst(char * ptr_c)
{
    
    cout<<"in prv_tst  with para"<< endl;

}
char * Person::prv_tst(char * ptr_c,int n)
{

    cout<<"in prv_tst  with return val"<< endl;
    return ptr_c;

}
Person::Person()
{
    name = "non";
    gender = 1;
    age = 18;
    cunt ++;
    pbk = new Book;    
    cout << "in persons' default constructor" << endl;
}

Person::Person(string _name):name(_name)
{
    pbk = new Book;    

   cout << "in persons' one para constructor" << endl;
}

Person::Person(string name,bool gender,int age)
{
    this->name = name;
    this->gender = gender;
    this->age = age;
    cunt++;
    pbk = new Book;
    cout << "in persons' three para constructor" << endl;
}

Person ::Person(const Person & ref_person)
{
    name = ref_person.name;
    gender = ref_person.gender;
    age = ref_person.age;
    cunt++;
    pbk = new Book;
    *pbk = *ref_person.pbk;
    cout << "in persons' copy constructor" << endl;
}

void Person:: show() 
{
    prv_tst();
    cout << name << endl;
    cout << gender << endl;
    cout << age << endl;
    cout << cunt << endl;
    pbk = new Book;
}

Person & Person::operator=(const Person & ref_person)
//Person  Person::operator=(const Person & ref_person)
//void Person::operator=(const Person & ref_person)
{
    this->name = ref_person.name;
    this->gender = ref_person.gender;
    this->age = ref_person.age;
    cunt++;
    cout << "operator = " << endl;
    this->pbk = new Book;
    *(this->pbk)= *ref_person.pbk;
    return *this;
}

void borrow(Person & ps)
{
    cout << "in friend func :  " << ps.name << endl;
}

Person::~Person()
{ 
    cunt--;
    cout << "in persons' deconstructor" << endl;
    cout << cunt << endl; 
    delete pbk; 
}
void Friendclass::show( const Person & ps )
{
    cout << "in friend class : " << ps.name << endl;

}
