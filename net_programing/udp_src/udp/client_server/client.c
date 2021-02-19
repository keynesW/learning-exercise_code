#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <strings.h>

#include <unistd.h>
#include <sys/types.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>



int main(int argc,const char * argv[])
{

    printf("argc : %d\n",argc);
/*{{{*/ // configure server ip and port to connect
    int sfd = -1;
    if( (sfd = socket(AF_INET,SOCK_DGRAM,0)) ==  -1)
    {
        perror("socket()");
        exit(EXIT_FAILURE);
    }

    struct in_addr svr_addr;
    uint16_t nport ;

    if(argc == 1)
    {
        char pstr_ip[] ="192.168.44.150";
        char hostport[] = "65523";

        svr_addr.s_addr =  inet_addr(pstr_ip);

        printf("%s \n",inet_ntoa(svr_addr));

        nport = htons(atoi(hostport));
        //printf("65523 : %#x\n",nport);
        printf("%d\n",ntohs(nport));
    }
    else
        if(argc == 3)
        {

            svr_addr.s_addr =  inet_addr(argv[1]);
            nport = htons(atoi(argv[2]));
        }
        else
            fprintf(stderr,"arguement error");

    struct sockaddr_in sock_addr;
    bzero(&sock_addr,sizeof sock_addr);

    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = nport;
    sock_addr.sin_addr = svr_addr;

    /*}}}*/


    char recvbuf[128] = {'\0'};
    char sndbuf[500] = "hello world";

    while(1)
    { 
        ///////////////////////////////////////
       

        int i = 0;
        while((sndbuf[i++] = getchar()) != '\n')
                ;
        sndbuf[i] = '\0';

        printf("in sndbuf : %s\n", sndbuf);

        if(strncmp(sndbuf,"quit",4) == 0)
            exit(EXIT_SUCCESS);
        /*    
              read(sfd,sndbuf,strlen(sndbuf)+1);
              write(sfd,sndbuf,strlen(sndbuf)+1);
              */       

        if(sendto(sfd,sndbuf,strlen(sndbuf)+1, 0,\
                (const struct sockaddr *)&sock_addr ,sizeof(sock_addr)) == -1)
        {
            perror("sendto() :");
            exit(EXIT_FAILURE);
        }
        bzero(sndbuf,sizeof sndbuf);

        if(recvfrom(sfd, recvbuf, sizeof recvbuf,\
                0, NULL, NULL ) < 0)
        {
            perror("server recvfrom()");
            exit(EXIT_FAILURE);
        }
        printf("response recived from server : %s\n", recvbuf);
    }
/*{{{*/
///////////////////////////////////////////////////////////////////////

/*
        ///////////////////////////////////////
        bzero(&snder_sockaddr,sizeof snder_sockaddr);
        if(recvfrom(sfd, recvbuf, sizeof recvbuf,\
                0, (struct sockaddr *)&snder_sockaddr, &socklen) < 0)
        {
            perror("server recvfrom()");
            exit(EXIT_FAILURE);
        }

        printf("-------------------------------------------------\n");
        printf("ip %s\n",inet_ntoa(sock_addr.sin_addr));
        printf("port %d\n",ntohs(sock_addr.sin_port));
        printf("-------------------------------------------------\n");

        printf("socklen :%d\n",socklen);

        printf("in snder_sockaddr :\n");
        int i = 0;
        int * iter = NULL;

        for( i = 0 , iter = (int *)&snder_sockaddr; i < sizeof snder_sockaddr/4; i++)
                printf("%#x\t",iter[i]);

        putchar('\n');
        putchar('\n');
        printf("ip addr %s , port %#x\n", inet_ntoa(snder_sockaddr.sin_addr),snder_sockaddr.sin_port);

        printf("message recived : %s \n",recvbuf);


        if(sendto(sfd,recvbuf,strlen(recvbuf)+1, 0,\
                (const struct sockaddr *)&snder_sockaddr ,sizeof(snder_sockaddr)) == -1)
        {
            perror("server sendto()");
            exit(EXIT_FAILURE);
        }

        if(strncmp(recvbuf,"quit",4) == 0)
            exit(EXIT_SUCCESS);
        bzero(recvbuf,sizeof recvbuf);

    }
*//*}}}*/
    return 0;
}
