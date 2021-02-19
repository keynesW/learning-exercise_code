#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc,char *argv[])
{
	int sockfd;
	struct sockaddr_in grp_cast_addr;
	char wbuffer[1024];

	if ((sockfd = socket(AF_INET,SOCK_DGRAM,0)) < 0)
	{
		perror("socket()");	
		exit(EXIT_FAILURE);
	}
	
	int wbytes;

	//填充广播地址与端口号
	socklen_t len = sizeof(struct sockaddr_in);
	memset(&grp_cast_addr,0,sizeof(grp_cast_addr));
	grp_cast_addr.sin_family = AF_INET; 
	grp_cast_addr.sin_addr.s_addr = inet_addr(argv[1]);
	grp_cast_addr.sin_port = htons(atoi(argv[2]));
	
	//允许发送广播
	int on = 1;
	if (setsockopt(sockfd,SOL_SOCKET,SO_BROADCAST,&on,sizeof(on)) < 0)
	{
		perror("setsockopt()");	
		exit(EXIT_FAILURE);
	}


	while(1)
	{
		memset(wbuffer,0,sizeof(wbuffer));		
		fprintf(stdout,"Server > ");
		fflush(stdout);

		fgets(wbuffer,sizeof(wbuffer),stdin);
		wbuffer[strlen(wbuffer) - 1] = '\0';
		
		wbytes = sendto(sockfd,wbuffer,strlen(wbuffer) + 1,0,
					(const struct sockaddr *)&grp_cast_addr,len);

		if (wbytes < 0)
		{
			perror("sendto()");	
			break;
		}

		if (strncmp(wbuffer,"quit",4) == 0)
			break;
	}


	close(sockfd);
	return 0;
}
