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


int main( int argc , const char * argv[] )
{
    int * ptr = (int *)malloc(sizeof (int));    
    *ptr = 666;
    cout << *ptr << endl;
    
    int (*ptr1)[3] = (int (*)[3])malloc( 3*sizeof (int) );
    (*ptr1)[0] = 1;
    (*ptr1)[1] = 2;
    (*ptr1)[2] = 3;

    cout << (*ptr1)[0] << '\n' <<\
        (*ptr1)[1] << '\n' << (*ptr1)[2] << endl;
    
    int *ptr2 = (int *)malloc( 3*sizeof (int) );
    ptr2[0] = 1;
    ptr2[1] = 2;
    ptr2[2] = 3;

    cout << ptr2[0] << '\n' <<\
        ptr2[1] << '\n' << ptr2[2] << endl;
    
    free(ptr);
    free(ptr1);
    free(ptr2);

    int*ptrn = new int;
    *ptrn = 666;
    //int*ptrn = new int(666);
    cout << *ptrn <<endl;

    //int *ptrna = new int [3];
    int *ptrna = new int [3]{1,2,};
    for (int i = 0; i < 3; i++)
        cout << ptrna[i] <<endl;
    
    cout << ptrn <<endl;
    delete ptrn;
    ptrn = nullptr;
    cout << ptrn <<endl;
    delete ptrn ;

    delete [] ptrna;
    ptrna = nullptr;
    delete ptrna ;

    return 0;
}

