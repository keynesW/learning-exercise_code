#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main( int argc ,char ** argv)
{
    int fdd,fds;

    if((fds = open(argv[1],O_RDONLY,0766))<0)
    {
        perror("failed to open");
        return -1;
    }

    if((fdd = open(argv[2],O_CREAT|O_TRUNC|O_WRONLY,0644))<0)
    {
        perror("failed to open");
        return -1;
    }

    char buffer[1023] = { '\0' };
    int numbyte = -1;
    
    while( numbyte = read(fds,buffer,sizeof buffer) )
    {
       if( write( fdd, buffer, numbyte ) < 0 )
       {
            printf("write failed");
       }
    }
    if(numbyte == -1)
        printf("read error");
    
    close(fds);
    close(fdd);

    return 0;
}

