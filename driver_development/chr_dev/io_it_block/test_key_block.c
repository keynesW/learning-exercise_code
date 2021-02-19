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

struct key_event{
    int code;
    int value;
};
 
int main( int argc,const char * argv[] )
{
    int fd;
    struct key_event event;


    if((fd = open("/dev/key3",O_RDWR |O_NONBLOCK)) < 0)
    {
        printf("open falied\n");
        exit(EXIT_FAILURE);
    }
    while(1)
    {
        if(read(fd,&event,sizeof(event)) < 0)
            ;
           // perror("read\n");
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

    return 0;
}
