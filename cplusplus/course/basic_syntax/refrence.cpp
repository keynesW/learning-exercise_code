/*******************************************************************
 *
 *     File Name    :      hollowrod.cpp
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Mon 09 Nov 2020 09:12:52 AM CST
 *
 ******************************************************************/
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

static inline void refrence_change( int & a );
//static inline void refrence_myswap(int a , int b);
static inline void refrence_myswap(int &a , int &b);
static inline void refrence_myswap(int *a , int *b);

int getStaticLocal();
int& getStaticLocalRe();
int getLocal();
int& getLocalRe();

const int & tst( int const & a)
{

    cout << " a : " << a << endl;
    return a ;
}

int main()
{
    string str;/*{{{*/
    string strw = "word";
    str = "hello word ";
    cout << str << endl;

    bool rsltstrcpy = str > strw;
    cout << rsltstrcpy << endl;
    cout << (str + strw) << endl;
    cout << str << endl;
    cout << (str += strw) << endl;
    cout << str << endl;
    cout << str[2] << endl;

    //string & strrefre = str;
    string & strrefre = str;
    cout << strrefre << endl;
    strrefre[5] = 'j';
    cout << str << endl;/*}}}*/
    
    int n = 1,m = 3;
    tst(n);
    refrence_change( n );
    refrence_myswap( n , m);
    cout << "n = "  << n << '\n' << "m = " << m << endl;
    cout << ++getStaticLocalRe() << endl;

    refrence_myswap( &n , &m);
    cout << "n = "  << n << '\n' << "m = " << m << endl;
    return 0;
}

static inline void refrence_change( int & a )
{
    a++;
}

static inline void refrence_myswap(int a , int b)
{
    printf("int a\n");

}
static inline void refrence_myswap(int &a , int &b)
{
    printf("int &a\n");
   int temp;/*{{{*/
   temp = a;
   a = b ;
   b = temp;

    a+= b;
    b = a - b;
    a = a - b;

    a ^= b;
    b ^= a;
    a ^= b;
/*
    a *= b;
    a /= b;
    b /= a;
*//*}}}*/
}

static inline void refrence_myswap(int *a , int *b)
{

    printf("int *a\n");
    *a+= *b;
    *b = *a - *b;
    *a = *a - *b;

}
int getStaticLocal()
{
    static int a = 1;
    return a;
}
int& getStaticLocalRe()
{
    static int a = 1;
    return a;
}
int getLocal()
{
    static int a = 1;
    return a;
}
int& getLocalRe()
{
    static int a = 1;
    return a;
}
