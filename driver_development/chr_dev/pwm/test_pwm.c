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
    char buf[2] = {0};

    int fd = open("/dev/pwm_0",O_RDWR);
    if(fd < 0)
        perror("open:\n");

    struct termios oldSet,newSet;

    tcgetattr(fileno(stdin),&oldSet);

    newSet = oldSet;
    newSet.c_lflag &= ~ECHO | ~ICANON;
    //newSet.c_lflag &= ~ICANON;
    newSet.c_cc[VMIN] = 1; 	
    newSet.c_cc[VTIME] = 0;

    if( tcsetattr(fileno(stdin),TCSAFLUSH,&newSet)!= 0 )
        fprintf( stderr,"Could not set attrbutes of terminal!\n" );

    while( (buf[0] = getchar()) != 'q')
    {
        printf("you intput the char: %c \n",buf);
        write(fd,buf,1);
    }

    tcsetattr( fileno(stdin),TCSANOW,&oldSet );
    close(fd);
    return 0;
}
