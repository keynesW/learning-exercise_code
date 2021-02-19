/*******************************************************************
 *
 *     File Name    :      test3.c
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Fri 22 Jan 2021 07:15:32 PM CST
 *     Description  :      Hello Word in C++ , GUN-style
 *
 ******************************************************************/

#include <stdio.h>

union test{
    int a ;
    struct stru{
        char c;
        short d;
        char e;
    }c;
};
 
int main( int argc,const char * argv[] )
{
    char array[12] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
    double a[4][4];
    double (*p)[3];
    union test c;
    p = (void *)a;
    
    unsigned long long int *pint64 = (unsigned long long int *) array;
    printf("%#llx\n",*pint64); 

    printf("%zd\n",sizeof(c.c));
    printf("%zd\n",sizeof(c));

    printf("%zd\n",&p[3][1]-&a[3][1]); 
    return 0;
}
