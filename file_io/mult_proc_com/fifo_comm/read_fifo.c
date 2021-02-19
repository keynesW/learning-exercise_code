/*******************************************************************
 *
 *     File Name    :      read_fifo.c
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Fri 23 Oct 2020 03:12:29 PM CST
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


int main(int argc , const char * argv[])
{

    int fd = 0;
    char buf[23] = {"asdfkajlkjlkjs"};
    if(( fd =  open("myfifo.ipc",O_RDONLY))!= -1) 
    {
        while(1)
        {
            read(fd,buf, sizeof buf);
            printf("in buf : %s",buf); 
        }
    }

    close(fd);

    return 0;

}
