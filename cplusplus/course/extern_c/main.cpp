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

extern "C"
{
    #include "tst.h"
}

using namespace std;
 
 
int main( int argc,const char * argv[] )
{
    int a = 1 , b = 3;
    int res = add(a,b);

    cout <<  res << endl;

    return 0;
}
