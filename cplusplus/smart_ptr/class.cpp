/*******************************************************************
 *
 *     File Name    :      class.cpp
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Fri 13 Nov 2020 03:21:10 PM CST
 *     Description  :      Hello Word in C++ , GUN-style
 *
 ******************************************************************/

#include <iostream>
using namespace std;
template<typename T>
class A{
private:
    T a;
public:
    A (T _a ):a(_a){}
    A():A(2){}
//    void show();
    void show()
    {
        cout << a << endl;
    }
    ~A(){}
};
/*
template <typename T> 
void A<typename T>::show()
{
    cout << a << endl;
}
*/
int main( int argc,const char * argv[] )
{

    A<int> a(1);
    a.show();

    A<int> b;
    b.show();

    return 0;
}
