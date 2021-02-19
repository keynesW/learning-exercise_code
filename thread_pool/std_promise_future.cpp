/*******************************************************************
 *
 *     File Name    :      std_promise_future.cpp
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Thu 03 Dec 2020 10:46:46 AM CST
 *     Description  :      Hello Word in C++ , GUN-style
 *
 ******************************************************************/

#include <iostream>
#include <thread>
#include <future>

using namespace std;

void thread_func(std::promise<int> * promObj)
{
    cout << "in thread created" << endl;
    promObj->set_value(20);
}
 
 
int main( int argc,const char * argv[] )
{
    promise<int> promiseObj;
    future<int> futureObj = promiseObj.get_future();

//std::thread is a class , thread_setpromise means an object
    std::thread  thread_setprom(thread_func,&promiseObj);

    cout << futureObj.get() << "  main thread wakeup" << endl;

    thread_setprom.join();

    return 0;
}
