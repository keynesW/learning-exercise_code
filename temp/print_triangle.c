/*******************************************************************
 *
 *     File Name    :      tst.c
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog?? :      http://www.    .com/ 
 *     Created Time :      2021年01月06日 星期三 09时38分19秒
 *     Description  :      Hello Word in C++ , GUN-style
 *
 ******************************************************************/

#include <stdio.h>
 
 
int main( int argc,const char * argv[] )
{
    int n = 0 ;
    scanf("%d",&n);

    for(int i = 1; i <= n; i++)
    {
        int j = 0;
        for( ; j < n-i; j++)
            printf(" ");
        for( ; j < n + i - 1; j++)
            printf("*");
        printf("\n");
    }

    return 0;
}
