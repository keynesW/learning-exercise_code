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
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <fcntl.h>
#include <wait.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/sem.h>

#include <pthread.h>



void * thread_handle(void * arg);

int main(int argc , const char * argv[])
{
    pthread_t pth_id = 0;
    pthread_create(&pth_id,NULL,thread_handle, (void *)10 );

    void * thread_ret = NULL;
    printf("thread_ret == (void *) 0 : %d\n",thread_ret == (void *) 0);

    pthread_detach(pth_id); // this will igornal the pthread_join;

    pthread_join(pth_id,&thread_ret);

    printf("%p\n",thread_ret);  // thread_ret == (void *) 0


    //printf("thread_ret value is %d\n",*(int *)thread_ret);
    printf("in parent progress, pthread ended\n");


    /////////////////////////////////////////////////////////
    //return and exit() are not used  
    //but replased with pthread_exit()
        pthread_exit(NULL);    
    //this will end the main progress 
    //but the program will not terminate 
    //unitl the last child progress terminate
    /////////////////////////////////////////////////////////


    return 0;
}


void * thread_handle(void * arg)
{
    printf("in pthread pthread_self() : %lu \n",pthread_self());

    printf("%d\n",(int)arg); printf("%p\n",(int *)arg);

    int ret = 10;                  
    void * thread_ret =(void *)&ret; // can not success temp pointer
    printf("%p\n",&ret);

    pthread_exit(thread_ret);   //pthread_exit( (void *) 1);
}
