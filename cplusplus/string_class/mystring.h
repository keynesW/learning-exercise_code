#ifndef _SSTRING_H_
#define _SSTRING_H_

#include <iostream>
using namespace std;

class MyString{
private:
    char *pstr;
    int len;
    //    int size_;
public:
    MyString();
    MyString(const char * ptr_c);
    MyString(char ch,int n);
    MyString(int n,char ch);
    MyString(const MyString & ref_str);

    MyString & operator=( const MyString & ref_str );
    MyString  operator+(const MyString & ref_str)const;
    MyString & operator+=(const MyString & ref_str);

    char operator[](int n)const;
    bool operator==(const MyString & ref_str)const;
    bool operator!=(const MyString & ref_str)const;

    friend ostream & operator<<(ostream & os,const MyString & ref_str);
    friend MyString & operator>>(istream & os, MyString & ref_str);
    //friend istream & operator>>(istream & os, MyString & ref_str);
    
    int size()const;
    void clear();

    ~MyString();

};

#endif 
