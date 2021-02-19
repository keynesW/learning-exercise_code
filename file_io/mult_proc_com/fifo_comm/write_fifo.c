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


int main(int argc , const char * argv[])
{

    int ret = mkfifo("myfifo.ipc",0666);
    if (ret == 1)
    {
        if(errno == 17)
        {
            perror("mkfifo()");
            return -1;
        }

    }

    int fd = 0;
    char buf[28] = {"helloworld\nhelloworld\n"};

    if( ( fd =  open("myfifo.ipc",O_WRONLY)) != -1)
    {
        printf("fifo open sucess\n");
        while(1)
        {
            write(fd,buf, sizeof buf);
            printf("write sucess\n");

        }
    }

    close(fd);
    
    return 0;

}
