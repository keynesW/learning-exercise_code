#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <poll.h>
#include <signal.h>

#define KEY2 2
#define KEY3 3

struct key_event{
	int code ;
	int value;
};

int fd;
struct key_event event;

void catch_signale(int signal){
	if(signal == SIGIO){
		read(fd, &event, sizeof(event));
		if(event.code == KEY3){
            printf(" code: %d event : %d\n",event.code,event.value);
			if(event.value == 1){
				printf("key3 down\n");
			}else{
				printf("key3 up\n");
			}
		}
	}
}


int main(int argc, const char *argv[])
{
	fd = open("/dev/key3", O_RDWR | O_NONBLOCK);
	if(fd < 0){
		perror("open");
		exit(1);
	}
	// 1,�����źŴ�����
	signal(SIGIO,catch_signale);
	// 2������ǰ�������ó�SIGIO����������
	fcntl(fd, F_SETOWN, getpid());
	// 3����ioģʽ���ó��첽ģʽ
	int flags  = fcntl(fd, F_GETFL);
	fcntl(fd, F_SETFL, flags | FASYNC );
	for(;;){
		printf("i'm working\n");
		sleep(1);
	}



	return 0;
}
