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
#include <pthread.h>

#include <fcntl.h>
#include <wait.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/sem.h>

static int global = 0;

void * thread_handle(void * arg);


int main(int argc , const char * argv[])
{
    pthread_t pth_id = 0;
    pthread_t pth_id1 = 0;
    pthread_create(&pth_id,NULL,thread_handle, (void *)atoi(argv[1]) );

    void * thread_ret = NULL;
    printf("thread_ret == (void *) 0 : %d\n",thread_ret == (void *) atoi(argv[1]));


///////////////////////////////////////////////////////////////////////

    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_create(&pth_id1,NULL,thread_handle, (void *)atoi(argv[1]) );

    printf("thread_ret == (void *) 0 : %d\n",thread_ret == (void *) atoi(argv[1]) );

    //pthread_detach(pth_id); // this will igornal the pthread_join;

    pthread_join(pth_id,&thread_ret);
    pthread_join(pth_id1,&thread_ret);


    //printf("thread_ret value is %d\n",*(int *)thread_ret);
    printf("in parent progress, pthread ended\n");
    printf(" global : %d \n",global);



    return 0;
}


void * thread_handle(void * arg)
{
    printf("in pthread pthread_self() : %lu \n",pthread_self());

    //printf("%d\n",(int)arg); printf("%p\n",(int *)arg);
    int loop = (int )arg;
    printf("loop : %d\n",loop);
    int j = 0;

    for( int i = 0 ; i < loop; i++)
        {
            //pthread_mutex_t mutex;
            //pthread_mutex_init(&mutex,NULL);
            pthread_mutex_lock(&mutex);
                j = global;
                j++;
                global = j;
            pthread_mutex_unlock(&mutex);

        }

    pthread_exit( (void *) 1);

    //pthread_exit(thread_ret);   
}
