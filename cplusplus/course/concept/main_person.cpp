/*******************************************************************
 *
 *     File Name    :      main_person.cpp
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Tue 10 Nov 2020 09:57:13 AM CST
 *
 ******************************************************************/

#include <iostream>
#include "person_class.h"
#include "student.h"


using namespace std;
    
    //int Person::cunt = 1;

int main( int argc , const char * argv[] )
{
    /*{{{
    {
        Person joker;
        joker.show();
        cout << joker.tst << endl;
        cout << "-------------------------" << endl;
        {
            Person loserZ("loser",0,18);
            loserZ.show();  
        }   
        cout << "-------------------------" << endl;
        Person tom("tom",0);
        tom.show();
        cout << "-------------------------" << endl;
        Person keynes(tom);
        keynes.show();
        cout << "-------------------------" << endl;
        Person jerry = Person("ljerry",1);
        jerry.show();
        cout << "-------------------------" << endl;

        Person *ps = new Person("lazyzhang",2);
        ps->show();
        enum CMD cmd = AGE;
        ps->get(cmd);
        delete ps;
        cout << "-------------------------" << endl;
    }
    cout << "-------------------------" << endl;
    Person:: getstatic();
    char *buf = new char[10]{'a','b'};
    cout << buf << endl;
    Person *ptrs = new (buf) Person("joker",1);
    ptrs->show();
    cout << buf << endl;
    cout << "-------------------------" << endl;
    delete ptrs;
    cout << "-------------------------" << endl;
    *//*}}}*/
/*
//{{{//
cout << "-------------------------" << endl;
    string strtst = "akdfaksjdf"; 
    Person ps = strtst;
cout << "-------------------------" << endl;

    Person ps1;
    ps1 = strtst;
cout << "-------------------------" << endl;
//}}}//
*/
    Person ps;
    int Person::*mptst = &Person::tst;
//    int Person::*mpage = &Person::age;
//    cout << mptst << endl; 
    printf("pps : %p\n",mptst);

    return 0;
}
