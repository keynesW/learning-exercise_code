/*******************************************************************
 *
 *     File Name    :      class_main.cpp
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Fri 13 Nov 2020 10:18:01 AM CST
 *     Description  :       Hello Word in C++ , GUN-style
 *
 ******************************************************************/

#include <iostream>
#include <cstdlib>
#include "class_template.h"
using namespace std;

int main( int argc,const char * argv[] )
{

    string str("adf");
    Demo< const char *, int > de("hello",2);
    cout << de.compare() << endl;
//    de.show(2.3);
    return 0;
}
