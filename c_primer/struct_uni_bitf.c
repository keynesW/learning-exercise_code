/*******************************************************************
 *
 *     File Name    :      tst.c
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Tue 08 Dec 2020 05:29:01 PM CST
 *     Description  :      Hello Word in C++ , GUN-style
 *
 ******************************************************************/

#include <stdio.h>

struct size{
    int a;
    char b;
    double c;
};

union un{
    int d;
    char e;
struct {
    int a:2;
    int b:3;
    int : 2;
    int c:1;
    };
};
 
int main( int argc,const char * argv[] )
{

    struct size a;
    printf("sizeof struct : %zd\n",sizeof (a));
    union un b;
    b.d = 0;
    b.a = 3;
    b.b = 3;
    printf("bit field : %d\n",b.d);

    return 0;
}
