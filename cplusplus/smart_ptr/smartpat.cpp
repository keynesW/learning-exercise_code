/*******************************************************************
 *
 *     File Name    :      smartpat.cpp
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Fri 13 Nov 2020 01:50:05 PM CST
 *     Description  :      Hello Word in C++ , GUN-style
 *
 ******************************************************************/

#include <iostream>
#include <memory>
using namespace std;
 
class B;
class A{

    public:
        A(){
            cout << "A constructor" << endl;
        }
        ~A(){

            cout << "A deconstructor" << endl;
        }
        void test();
        shared_ptr<B> shptrB;

};

void A::test()
{
    cout << "test" << endl;
}
class B{

    public:
        B(){
            cout << "B constructor" << endl;
        }
        ~B(){

            cout << "B deconstructor" << endl;
        }
        void test();
        shared_ptr<A> shptrA;

};

void B::test()
{
    cout << " B test" << endl;
}
int main( int argc,const char * argv[] )
{

//    unique_ptr<A> ptr( new A );
//    (*ptr).test();
//    ptr->test();
/*
    cout << "------------------------" << endl;

    shared_ptr<A>sptr(new A);
    shared_ptr<A>sptr1(sptr);
    shared_ptr<A> sptr2;
    
    sptr2 = sptr1;
    cout << sptr2.use_count() << endl;

    cout << "------------------------" << endl;
*/
    {
        cout << "------------------------" << endl;
        shared_ptr<A>sptr(new A);
        shared_ptr<B>sptr1(new B);
        cout << sptr.use_count() << endl;
        cout << sptr1.use_count() << endl;

        cout << "------------------------" << endl;
        sptr->shptrB = sptr1;
        sptr1->shptrA = sptr;
        cout << sptr.use_count() << endl;
        cout << sptr1.use_count() << endl;

        cout << "------------------------" << endl;
    }

    return 0;
}
