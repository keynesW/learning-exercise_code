/*******************************************************************
 *
 *     File Name    :      mian.c
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Fri 23 Oct 2020 01:43:32 PM CST
 *
 ******************************************************************/
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>


typedef void (*signalhandler)(int);

void signalhand(int para);
void signalhand1(int para);


int main(int argc , const char * argv[])
{
    
    signal(SIGUSR1,signalhand); 
    signal(SIGUSR2,signalhand1); 
    signal(SIGALRM,signalhand1); 

    pid_t pid = 0;
    if ((pid = fork()) == -1 )
    {
        perror("fork()");
        return -1;
    }

    if( pid == 0 )
    {
        printf("in chid pro \n");
        kill(getppid(),SIGUSR2);
        printf("SIGUSR2 sended\n");
        sleep(2);
        //kill(getppid(),SIGKILL);
        //printf("SIGKILL signal sended\n");
    }

    if( pid > 0 )
    { 
        printf("parent pro sleeping\n");
        raise(SIGUSR1);
        //alarm(10);

        while(1)
            sleep(5);

        printf("sleeping over\n");
    }

    return 0;

}
void signalhand(int para)
{
    printf("in signalhandler\n");
    putchar('\n');
}

void signalhand1(int para)
{
    printf("in signalhandler 1\n");
    printf("SIGALRM setting\n");
    alarm(5);
    putchar('\n');
}
