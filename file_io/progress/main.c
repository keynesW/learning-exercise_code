/*******************************************************************
 *
 *     File Name    :      main.c
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Thu 22 Oct 2020 10:39:51 AM CST
 *
 ******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h> 

int main(int argc ,char ** argv)
{
    int cunt = 0;
    int status = 0; 

    printf("hello \n");

    pid_t ret = fork();

    if(ret == -1)
        perror("fork()");

    if(ret > 1)
    {
        printf("in parent' progress\n");
    }


    if(ret == 0)
    {
        printf("in child progress return sucess\n");
        if( (ret = execlp( "/home/keynes/workdir/file_io/progress/pro","pro","-ef",NULL)) != -1 )
        {
            printf("childe progress return sucess\n");
        }
        printf("back2main.c");
    }

    while(cunt < 15)
    {
        cunt ++;
        printf("main.c : hello again\n");
        sleep(1);
    }

    return 0;

}
