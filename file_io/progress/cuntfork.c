/*******************************************************************
 *
 *     File Name    :      cuntfork.c
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Thu 22 Oct 2020 07:01:01 PM CST
 *
 ******************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    int i = 0;
    printf("in main i = %d\n",i);
    /*
    if(fork() > 0)
    if(fork()&&fork()||fork())
    {
        fork();
        i ++ ;
        printf("i = %d\n",i);
    }
    */
    (fork()&&fork()||fork());

    while(1)
        sleep(5);
    return 0;
}
