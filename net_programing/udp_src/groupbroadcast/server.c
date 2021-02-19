#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
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

	//填充组播地址与端口号(224.0.0.8)
	socklen_t len = sizeof(struct sockaddr_in);
	memset(&grp_cast_addr,0,sizeof(grp_cast_addr));
	grp_cast_addr.sin_family = AF_INET; 
	grp_cast_addr.sin_addr.s_addr = inet_addr(argv[1]);
	grp_cast_addr.sin_port = htons(atoi(argv[2]));
	
	while(1)
	{
		memset(wbuffer,0,sizeof(wbuffer));		
		fprintf(stdout,"Server > ");
		fflush(stdout);

		fgets(wbuffer,sizeof(wbuffer),stdin);
		wbuffer[strlen(wbuffer) - 1] = '\0';
		
		//发送给多播组(所有的客户端都可以收到消息)
		wbytes = sendto(sockfd,wbuffer,strlen(wbuffer) + 1,0,
					(const struct sockaddr *)&grp_cast_addr,len);

		if (wbytes < 0)
		{
			perror("sendto()");	
			break;
		}
	}


	close(sockfd);
	return 0;
}
