/*******************************************************************
 *
 *     File Name    :      test_chr_dev.c
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog?? :      http://www.    .com/ 
 *     Created Time :      2021年01月08日 星期五 15时07分35秒
 *     Description  :      Hello Word in C++ , GUN-style
 *
 ******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <termios.h>
 
int main( int argc,const char * argv[] )
{
    int buf[10] = {0};
    int ret = 0;
    int i = 0;
    int fd = open("/dev/chr_0",O_RDWR);
    if(fd < 0)
        perror("open:\n");

    if((ret = write(fd,buf,4)) < 0)
        perror("open:\n");

    srand((unsigned int )time(NULL));
    while(1)
    {
        /*
        for( ; i < 4; i++)
        {
            write(fd,&i,sizeof i);
            usleep(100000);
        }
        i = 0;
        */
        i = rand()%4;
        write(fd,&i,sizeof i);
        printf("debug info\n");
        usleep(50000);
    }

    close(fd);
        return 0;
}
