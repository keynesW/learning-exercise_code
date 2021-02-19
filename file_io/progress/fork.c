/*******************************************************************
 *
 *     File Name    :      fork.c
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Thu 22 Oct 2020 11:25:04 AM CST
 *
 ******************************************************************/

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>

/*
int main(int argc , char ** argv)
{
    int i =  0;
loop :
    printf("--------------before fork---------------\n");
    pid_t ret = fork();
    if(ret == -1)
    {
        perror("fork()");
    }
    printf("\n--------------after fork----------------\n");
    printf("fork sucess getpid = %d\n",getpid()); 


    if (ret > 0)
    {
        printf("in parent process ret = %d\n\
                    getpid = %d\n",ret,getpid());
        //sleep(15);
    }
    if(ret == 0)
    {
        //i++;
        //sleep(13);
        printf("in child process ret = %d\n\
                    getppid = %d\n",ret,getppid());
        //sleep(10);
        //if(i < 3)
        //    goto loop;
    }


    sleep(30);
    //goto loop;

    return 0;

}
*/
int main(int argc , char ** argv)
{
    int ret = 0;
    printf("in main");
    ret = fork();
    
    if (ret > 0)
        while(1) sleep(1);

    if (ret = 0)
        while(1) sleep(1);

    return 0;
}
