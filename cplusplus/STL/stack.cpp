/*******************************************************************
 *
 *     File Name    :      stack.cpp
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Mon 16 Nov 2020 03:45:38 PM CST
 *     Description  :      Hello Word in C++ , GUN-style
 *
 ******************************************************************/

#include <iostream>
#include <stack>
using namespace std;
 
 
int main( int argc,const char * argv[] )
{
    stack<int> istk;
    istk.push(34);
    istk.push(3);
    istk.push(4);
    istk.push(35);
    istk.push(32);

    for( ; ! istk.empty(); istk.pop())
    {
        cout << istk.top() << endl;
        //cout << (istk.size()) << endl;
    }        
    

    return 0;
}
