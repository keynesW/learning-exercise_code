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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <poll.h>
#include <signal.h>

struct key_event{
    int code;
    int value;
};
 
void identify_key(struct key_event event)
{
    switch(event.code)
    {
    case 1:
        //if( event.code == 1 )
        if(event.value == 2)
            printf("app key3 down\n");
        else
            printf("app key3 up\n");
        break;
    case 2:
        //if( event.code == 2 )
        if(event.value == 2)
            printf("app key2 down\n");
        else
            printf("app key2 up\n");
        break;
    case 3:
        //if( event.code == 3 )
        if(event.value == 2)
            printf("app key4 down\n");
        else
            printf("app key4 up\n");
        break;
    }
    //usleep(10000);
    memset(&event,0,sizeof event);
    //printf("adfkasdfkj\n");
}

int main( int argc,const char * argv[] )
{
    int fd;
    int i ;
    int j = 0;
    int ret;
    struct key_event event;
    struct pollfd pfd[2];
    char  std_in[128] = {'0'};

    if((fd = open("/dev/key3",O_RDWR |O_NONBLOCK)) < 0)
    {
        printf("open falied\n");
        exit(EXIT_FAILURE);
    }

    pfd[0].fd = fd;
    pfd[0].events = POLLIN;
    pfd[1].fd = 0;
    pfd[1].events = POLLIN;
    
    while(1)
    {
        if( (ret = poll(pfd,2,-1)) < 0){
            perror("poll\n"); 
            exit(EXIT_FAILURE);
        }
        printf("ret : %d\n",ret);

        for(i = 0 ; i < 2 && j < ret; i++) {
            if( pfd[i].events & pfd[i].revents ){
                j++;
                switch (i) {
                case 0:
                    read(pfd[i].fd,&event,sizeof(event));
                    identify_key(event);
                    break;
                case 1:
                    //read(pfd[1].fd,&event,sizeof(event));
                    //fgets(std_in,sizeof(std_in),stdin);
                    fgets(std_in,sizeof(std_in),stdin);
                    printf("in std_in buff : %s \n",std_in);
                    break;
                }
            }
        }
        j = 0;
    }

    return 0;
}
