#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>

#define LED_MAGIC 'L'

#define LED_ON	_IOW(LED_MAGIC, 0, int)
#define LED_OFF	_IOW(LED_MAGIC, 1, int)

//#define TSTVAL 0x8ff
#define TSTVAL 0x4ff

int main(int argc, char **argv)
{
	int fd;

	fd = open("/dev/led", O_RDWR);
	if (fd < 0) {
		perror("open");
		exit(1);
	}

	while(1){
        int low;
    /*
        int i = 0 ;
        for( ;i < 10000; i++ ){
           ioctl(fd, LED_ON);
           usleep(100000);
           ioctl(fd, LED_OFF);
           usleep(100000);
        }
     */
        /*TSTVAL CAN BE A DURATION*/
        for(low = 0; low < TSTVAL; low ++) {
            ioctl(fd, LED_ON);
            usleep(low);
            ioctl(fd, LED_OFF);
            usleep(TSTVAL - low);
        }
        for( ;low > 0 ; low-- ){
            ioctl(fd, LED_ON);
            usleep(low);
            ioctl(fd, LED_OFF);
            usleep(TSTVAL - low);
        }
    }

	return 0;
}
