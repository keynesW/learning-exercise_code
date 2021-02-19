/*******************************************************************
 *
 *     File Name    :      daemon.c
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Fri 23 Oct 2020 10:45:42 AM CST
 *
 ******************************************************************/

#include <stdio.h>
//#include <string.h>
#include <stdlib.h>
#include <unistd.h>
//#include <sys/wait.h>
#include <sys/types.h> 
#include <sys/stat.h>
//#include <fcntl.h>


int main()
{
    if(fork() ==  0)
    {
        setsid();
        chdir("/");
        umask(0);
        int num = getdtablesize();
        for(int i = 0; i <= num ; i++)
        {
            close(i);
        }

        while(1)
        {
            sleep(5);
        }

    }


    return 0;

}
