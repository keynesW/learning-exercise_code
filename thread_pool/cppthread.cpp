/*******************************************************************
 *
 *     File Name    :      cppthread.cpp
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Fri 04 Dec 2020 01:32:56 PM CST
 *     Description  :      Hello Word in C++ , GUN-style
 *
 ******************************************************************/

#include <iostream>
//#include <unistd.h>
#include <thread>
#include <future>
#include <chrono>


using namespace std;

void print_thread(promise<int> *a)
{
    while(1)
    {

//        cout << a << endl;
        cout << "in print thread " << endl;
        this_thread::sleep_for(chrono::seconds(2));
        a->set_value(5);
        //a->set_value(6);
        return;
    }
    
}
 
int main( int argc,const char * argv[] )
{
    promise<int> promiseObj;

    future<int> futureObj = promiseObj.get_future();
    
    int i = 6;
    thread t(print_thread,&promiseObj);
    cout << "in main thread " << endl;
    cout << "futureObj.get : " << futureObj.get()  << endl;
    //cout << futureObj.get()  << endl;
    while(1)
    {
        cout << "main thread sleep" << endl;
        this_thread::sleep_for(chrono::seconds(2));
        //    sleep(2);
    }

    return 0;
}
