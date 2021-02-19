/*******************************************************************
 *
 *     File Name    :      tst.c
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Mon 14 Dec 2020 08:45:04 AM CST
 *     Description  :      Hello Word in C++ , GUN-style
 *
 ******************************************************************/

#include <stdio.h>
 
 
int main( int argc,const char * argv[] )
{
    char * array[10];
    char  arr[3][5]; char (*)[5];

    char ** ptr = NULL;
    ptr = array;

    ptr = arr; 

    return 0;
}
