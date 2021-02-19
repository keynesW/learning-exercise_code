/******************************************************************
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
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;


int f(int a, int b);
double f(double b, double a = 10.3);
long int f(long int  b, long int a);
int order(int a, int b,bool (*p)(int a,int b));

int main( int argc , const char * argv[] )
{
    int a = 3 , b = 7;
    double c = 11.3;
    a+=a-=a*a;
    cout << a << endl;
    cout << f(a) << endl;

    auto d = c;
    cout << d << endl;

    int n = 0;
    //n = [=](int a,int b)->int{return a+b;}(a,b);
    //n = [](int a,int b){return a+b;}(a,b);
    
    auto funcptr = [](int a,int b){return a+b;};
    n = funcptr(a,b);

    cout << "n = " << n << endl;

    order(a,b,[](int a, int b){return a < b;});

    return 0;
}

int f(int a, int b)
{
    printf("in func int  a b\n");
    return a+b;
}

double f(double b, double a )
{
    printf("in func double b a \n");
    return a+b;
}

long int f(long int b, long int  a )
{
    printf("in func long b a\n");
    return a+b;
}

int order(int a, int b,bool (*p)(int a,int b))
{
    char space = 32;
    if(p(a,b))
    {
        cout << b << space << a << endl;
    }
    else
    {
        cout << a << ' ' << b << endl;
    }

    return 0;
}


