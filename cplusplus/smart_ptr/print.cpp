/*******************************************************************
 *
 *     File Name    :      print.cpp
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Fri 13 Nov 2020 03:08:26 PM CST
 *     Description  :      Hello Word in C++ , GUN-style
 *
 ******************************************************************/

#include <iostream>
using namespace std;
 

template <typename T>
void print(T* ptr,int n);

template <typename T>
class Iterator{
private:
    T* start;
    T* end;
    T* iter;
public:
    Iterator(){}
    Iterator(T* _start,T* _end): start(_start),end(_end){}

    void show()
    {
        for(iter = start ; iter < end ; iter++)
            cout << *iter << "  ";
        cout << endl;
    }
    ~Iterator(){}
};

int main( int argc,const char * argv[] )
{
    int a[] ={1,2,34,5} ;   
    double b[] ={1.1,2.2,34,5.3} ;   

    print(a,4);
    print(b,4);
    
    Iterator< int > itera(a,a+4);
    itera.show();

    Iterator<double> iterb(b,b+4);
    iterb.show();

    return 0;
}

template <typename T>
void print(T* ptr,int n)
{
    for(int i = 0 ; i < n ;i++)
        cout << ptr[i] << "  " ;
    cout<< endl;
}
