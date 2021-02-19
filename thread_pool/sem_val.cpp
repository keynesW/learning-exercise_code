/*******************************************************************
 *
 *     File Name    :      sem_val.cpp
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Fri 04 Dec 2020 02:39:44 PM CST
 *     Description  :      Hello Word in C++ , GUN-style
 *
 ******************************************************************/

#include <iostream>

#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;



class Sem{

private:
    int     sem_cunt;
    int     wakeups;
    std::mutex    sem_mutex;
    std::condition_variable     cond;

public:
    Sem(int i = 1);
    ~Sem(){}
    void passeren();
    void vrijgeven();

};

Sem::Sem(int i): sem_cunt(i)
{}

void Sem::passeren()
{
    std::unique_lock<std::mutex> lock(sem_mutex);
    if( --sem_cunt < 0)
    {
        cond.wait(lock);
        //cond.wait(lock,[&]()->bool {return sem_cunt >= 0;});
    }
}
void Sem::vrijgeven()
{
    std::lock_guard<std::mutex> lock(sem_mutex);
    if(++sem_cunt <= 0)
    {
        cond.notify_one();
        //cond.notify_all();
    }
}


void print_thread(int & a);

Sem mainsem;
Sem childsem;

mutex mainlock;
mutex childlock;


int main( int argc,const char * argv[] )
{

    int i = 4;
    childsem.passeren();
    childlock.lock();

    thread print(print_thread,ref(i));
    while(1)
    {
        cout << "main thread" << endl;
        // this_thread::sleep_for(chrono::seconds(3));
        //childlock.unlock();
        //mainlock.lock();
        // std::unique_lock<std::mutex> lock( mut );
//        mut.lock();
        childsem.vrijgeven();
        mainsem.passeren();
//        mut.unlock();
    }

    return 0;
}

void print_thread(int & a)
{
    
    while(1)
    {
        //std::unique_lock<std::mutex> lock( mut );
//        mut.lock();
        childsem.passeren();
        cout << "child thread  a :" << a << endl;
        //mainlock.unlock();
        //childlock.lock();
        //mainsem.vrijgeven();
//        mut.unlock();
    }
    return ;
}
