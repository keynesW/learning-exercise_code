/*******************************************************************
 *
 *     File Name    :      test_key_interrupt.c
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Mon 11 Jan 2021 10:32:37 AM CST
 *     Description  :      Hello Word in C++ , GUN-style
 *
 ******************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <poll.h>
#include <signal.h>

struct ev{
   int code;
   int value;
};

int fd;
struct ev event;

void catch_signal(int signal)
{
    if(signal == SIGIO)
    {
        read(fd,&event,sizeof(event));
        if(event.code == 3){
            printf(" code: %d event : %d\n",event.code,event.value);
            if(event.value == 1){
                printf("key3 down\n");
            }
            else{
                printf("key3 up\n");
            }
        }
    }
}

int main( int argc,const char * argv[] )
{

    //if(open("/dev/key3",O_RDWR | O_NONBLOCK) < 0 )
    // use this expression with fd not initialized 
    // when call sleep the program will never wakeup again
    
    if((fd = open("/dev/key3",O_RDWR | O_NONBLOCK)) < 0 )
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    signal(SIGIO,catch_signal);
    fcntl(fd,F_SETOWN,getpid());    

    int flags = fcntl(fd,F_GETFL);
    fcntl(fd,F_SETFL,flags | FASYNC);

	for(;;){
		printf("i'm working...\n");
		sleep(1);
	}
    close(fd);
    return 0;
}
/*
   while(1)
   {
   printf("fadsfadfd\n");
   sleep(1);
   }
   */
