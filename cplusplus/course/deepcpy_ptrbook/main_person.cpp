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
#include "book.h"


using namespace std;
    

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
*/
//cout << "-------------------------" << endl;
    string strtst = "akdfaksjdf"; 
    Person ps = strtst;
cout << "-------------------------" << endl;
    Person ps1;
cout << "-------------------------" << endl;
    ps1 = strtst;
cout << "-------------------------" << endl;
    ps1.show();
//    borrow(ps1); 
//    Friendclass fc;
//    fc.show(ps1);
//cout << "-------------------------" << endl;
/*
//}}}//
*/
   //return an obj will call it's copy constructor
   //
   //////////////////////////////////////////////
   //with -fno-elide-constructors
   //Person ps = strtst 
   //call one para constructor than call copy constructor
   ///////////////////////////////////////////////
   //by default ps = strtst 
   //call it's one para constructor
   ///////////////////////////////////////////////
    return 0;
}
