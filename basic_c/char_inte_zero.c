/*******************************************************************
 *
 *     File Name    :      tst.c
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Wed 09 Dec 2020 09:54:30 AM CST
 *     Description  :      Hello Word in C++ , GUN-style
 *
 ******************************************************************/

#include <stdio.h>
 
 
int main( int argc,const char * argv[] )
{
    char a = '0';
    int ptr ;

    printf("%c\n",a);

    ptr = (int) &a;
    printf("%#x\n",ptr);
    printf("%p\n",&a);
    *(char *)ptr = '1';
    printf("%c\n",a);

    printf("%d\n",1 << 2);

    return 0;
};
