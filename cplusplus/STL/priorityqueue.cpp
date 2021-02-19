/*******************************************************************
 *
 *     File Name    :      priority_queue.cpp
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Mon 16 Nov 2020 03:45:38 PM CST
 *     Description  :      Hello Word in C++ , GUN-style
 *
 ******************************************************************/

#include <iostream>
#include <queue>
using namespace std;
 
 
int main( int argc,const char * argv[] )
{
    priority_queue<int> ipriority_queue;
    ipriority_queue.push(3);
    ipriority_queue.push(4);
    ipriority_queue.push(35);
    ipriority_queue.push(32);

    for( ; ! ipriority_queue.empty(); ipriority_queue.pop())
    {
        cout << ipriority_queue.top() << endl;
        //cout << ipriority_queue.back() << endl;
        //cout << ipriority_queue.front() << endl;
        //cout << (ipriority_queue.size()) << endl;
    }
    cout << ipriority_queue.size() << endl;
    

    return 0;
}
