#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
int main(int argc,char *argv[])
{
	int sockfd;	
	
	struct sockaddr_in local_addr;//客户端地址结构对象(自身的ip地址与端口号)

	struct ip_mreq mreq;//多播的地址结构体

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
   	//2.将当前主机添加到多播组
	memset(&mreq,0,sizeof(mreq)); 
	mreq.imr_multiaddr.s_addr = inet_addr(argv[1]);//组播的 ip地址
	mreq.imr_interface.s_addr = INADDR_ANY;//本地 ip 地址,INADDR_ANY:本机上任意的ip地址
	
	//3.修改当前的 socket 属性为多播属性
	if (setsockopt(sockfd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq)) < 0)
	{
		perror("setsockopt()");	
		exit(EXIT_FAILURE);
	}

#if 0
	int loop = 1;
	if (setsockopt(sockfd,IPPROTO_IP,IP_MULTICAST_LOOP ,&loop,sizeof(loop)) < 0)
	{
		perror("setsockopt()");	
		exit(EXIT_FAILURE);
	}
#endif	

	//4.绑定 ip 地址与端口号(自身)
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
	}

	//退出多播组
	if (setsockopt(sockfd,IPPROTO_IP,IP_DROP_MEMBERSHIP,&mreq,sizeof(mreq)) < 0)
	{
		perror("setsockopt()");	
		exit(EXIT_FAILURE);
	}

	close(sockfd);
	return 0;
}
