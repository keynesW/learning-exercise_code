/*******************************************************************
 *
 *     File Name    :      tst.cpp
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Thu 03 Dec 2020 12:06:45 PM CST
 *     Description  :      Hello Word in C++ , GUN-style
 *
 ******************************************************************/

#include <iostream>
#include <functional>
using namespace std;


/*
template<typename T>
void func( T a )
{
    a();
    cout << "func called" << endl;
}
*/

//void func(std::function<std::string()> const &f )
void func(std::function<void()> const &f )
{
    //std::cout << f() << std::endl;
    f();
}

/*
void func( void (*ptr)( ))
{
    ptr();
    cout << "func called" << endl;
}
*/

/*
void func(string(*f)() )
{
    std::cout << f() << std::endl;
}
*/

/*
void print(std::function<std::string()> const &f )
{
    std::cout << f() << std::endl;
}
*/
 
int main( int argc,const char * argv[] )
{
    int i = 0;
    for(i = 0 ; i < 4; i++ ) 
    {
        //anon();
        auto anon = [i]{cout << "anonymous func called i :"  << i << endl;} ;
        cout << i << endl;
    }
    cout << "----------------------------" << endl;
    //anon();
    func([]{cout << "an func called " << endl;}); 


    return 0;
}
