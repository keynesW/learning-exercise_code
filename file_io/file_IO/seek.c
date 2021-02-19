#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main()
{
    int fd ;
    char  buffer[100] = {'\0'};

    if( (fd = open("test.txt",O_RDWR|O_CREAT|O_TRUNC,0666)) < 0 )// O_APPEND 
    {
        perror("file open");
        printf("failed to open :%s\n",strerror(errno));
        return -1;
    }
    //printf("%d\n",fd);
    int numbyte = write(fd,"this is a sentence used to test",44);

    lseek(fd,0,SEEK_SET);

    if( read(fd,(void *)buffer,numbyte) )
        printf("in buffer :%s\n",buffer);
    else 
        printf("failed to read\n");

    close(fd);

    return 0;
}
