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
	
	struct sockaddr_in local_addr;//客户端地址结构对象

	if (argc != 3)
	{
		fprintf(stderr,"Usage : %s <ip address> <port>\n",argv[0]);	
		exit(EXIT_FAILURE);
	}
	//1.建立 socket 文件描述符
	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	if (sockfd < 0)
	{
		perror("socket()");	
		exit(EXIT_FAILURE);
	}
	

	//4.绑定 ip 地址与端口号
	socklen_t len = sizeof(struct sockaddr_in);
	memset(&local_addr,0,sizeof(local_addr));
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(atoi(argv[2]));
	local_addr.sin_addr.s_addr = INADDR_ANY;
	
	if (bind(sockfd,(struct sockaddr *)&local_addr,len) < 0)
	{
		perror("bind()");	
		exit(EXIT_FAILURE);
	}

	char rbuffer[1024];
	int rbytes;	
	struct sockaddr_in cli_addr;

	while(1)
	{
		memset(rbuffer,0,sizeof(rbuffer));	
		rbytes = recvfrom(sockfd,rbuffer,sizeof(rbuffer),0,
							(struct sockaddr *)&cli_addr,&len);
		if (rbytes < 0)
		{
			perror("recvfrom()");	
			break;
		}

		printf("Receive from ip <%s>\n",inet_ntoa(cli_addr.sin_addr));
		printf("Receive from port <%d>\n",ntohs(cli_addr.sin_port));
		printf("Receive buffer : <%s>\n",rbuffer);

		if (strncmp(rbuffer,"quit",4) == 0)
				break;
	}

	close(sockfd);

	return 0;
}
