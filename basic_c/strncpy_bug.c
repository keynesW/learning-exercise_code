/*******************************************************************
 *
 *     File Name    :      main.c
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Sat 14 Nov 2020 06:42:16 PM CST
 *     Description  :      Hello Word in C++ , GUN-style
 *
 ******************************************************************/

#include <stdio.h>
#include <string.h> 
 
int main( int argc,const char * argv[] )
{
    char arrc[] = "aldfjaksdf\0kadfjajfl";
    char tmp[1024] ;
    printf("sizeof arrc = %zd\n",sizeof arrc);
    printf("in arrc %s\n",arrc);

    printf("----------------------\n");
    strncpy(tmp,arrc,21);
    printf("in tmp  : %s\n",tmp);
    printf("in tmp  : %s\n",&tmp[15]);
    printf("----------------------\n");
    for(int i = 0; i < 21; i++ )
        tmp[i] = arrc[i];
    printf("in tmp  : %s\n",tmp);
    printf("in tmp  : %s\n",&tmp[15]);

    return 0;
}
