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

#include "book.h"

Book::Book()
{
    cout << "in book' default constructor" << endl;
}

void Book::show()
{
    cout << id << endl;
    //this->Person::show();
}
/* 
Book::Book(const Book & ref_stud) : Person(ref_stud)
{
    this->id = ref_stud.id;
    cout << "in book' default constructor" << endl;
}
*/ 
