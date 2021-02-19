/******************************************************************
 *
 *     File Name    :      hollowrod.cpp
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Mon 09 Nov 2020 09:12:52 AM CST
 *
 ******************************************************************/
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;


int main()
{
    
    int n = 1,m = 3;
    double result = static_cast<double>(m)/10;
    cout << result << endl;

    int * ptr = reinterpret_cast<int *>( malloc(sizeof (int)));
    cout << *ptr << endl;
    
    const int num = 5;// const int 
    const int * ptr1 = &num; 
    //int * ptr2 = &num;
    int * ptr3 = const_cast<int *>(&num);
    *ptr3 = 3;
    cout << *ptr1 << endl;

/*
    volatile const int k = 1;
    volatile const int * p = &k;
    *(int *)p = 2;
    *const_cast<int *>(p) = 2;
    cout << n << endl;
*/
    const int k = 1;
    const int * p = &k;
    *(int *)p = 2;
    *const_cast<int *>(p) = 2;
    cout << n << endl;         //be careful with this line
    cout << *p << endl;

    return 0;
}

