/*******************************************************************
 *
 *     File Name    :      main.cpp
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Fri 13 Nov 2020 09:05:23 AM CST
 *     Description  :       Hello Word in C++ , GUN-style
 *
 ******************************************************************/

#include <iostream>
#include <cstring>
using namespace std;
/* 
int compare(int a,int b); 
int compare(double a,double b); 
int compare(string a,string b); 
*/
template <typename Tp> int compare(Tp a,Tp b);
//template <> int compare<const char *>(const char * a,const char * b);
//template <> int compare(const char * a,const char * b);
template int compare<const char *>(const char * a,const char * b);

int main( int argc,const char * argv[] )
{
    int a =1,b= 2;
    double c = 3, d = 4;
    string str("abd");
    string str1("a1bd");
    cout << compare(a,b) << endl;
    cout << compare(d,c) << endl;
    cout << compare(str,str1) << endl;

    const char *pstr = "hello";
    const char *pstr1 = "word";
    cout << (void *) pstr << endl;
    cout << (void *) pstr1 << endl;
    cout << compare(pstr,pstr1) << endl;

    return 0;
}

template <typename Tp>
int compare(Tp a,Tp b)
{
   if(a == b)
       return 0;
    return  (a > b? (1):(-1));
}

//template <> 
//int compare<const char *>(const char * a,const char * b)
//int compare(const char * a,const char * b)

/*
int compare(int a,int b) 
{
   if(a == b)
       return 0;
    return  (a > b? (1):(-1));
}
int compare(double a,double b) 
{
   if(a == b)
       return 0;
    return  (a > b? (1):(-1));
}

int compare(string a,string b)
{
   if(a == b)
       return 0;
    return  (a > b? (1):(-1));
}
*/
