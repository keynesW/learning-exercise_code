/*******************************************************************
 *
 *     File Name    :      ffork.c
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Thu 22 Oct 2020 02:27:51 PM CST
 *
 ******************************************************************/

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc , char ** argv)
{
    pid_t ret = fork();
    if(ret == -1)
    {
        perror("fork()");
    }


    if (ret > 0)
        ret = fork();

    if(ret == 0)
    {
        ret = fork();
        if(ret > 0)
            ret = fork();
    }

    while(1)
        sleep(5);
    return 0;
}
