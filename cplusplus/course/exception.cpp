/*******************************************************************
 *
 *     File Name    :      main.cpp
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Thu 12 Nov 2020 04:08:28 PM CST
 *     Description  :       Hello Word in C++ , GUN-style
 *
 ******************************************************************/

#include <iostream>

using namespace std;

void devide()
{
    int divisor;
    cout << "please enter a divisor" << endl;
    cin >> divisor;
    try{

        if(!divisor)
            throw "divisor zero";
        int ret = 666/divisor;
        cout << ret << endl;

    }catch(const char * e){

        cout << "expection   " << e << endl;
        throw ;
    }

    cout << "divisor end" << endl;

}
 
int main( int argc,const char * argv[] )
{
    while(1)
    {
        try{
            devide();
        }catch(const char * e){
            cout << "catch in main" << endl;
        }
    }

    return 0;
}
