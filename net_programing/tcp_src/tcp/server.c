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
#include <sys/un.h>



#define MAX_LISTEN  30

int main(int argc,const char * argv[])
{

    printf("argc : %d\n",argc);

/*{{{*/  // configure server ip and port
    int sfd = -1;
    if( (sfd = socket(AF_INET,SOCK_STREAM,0)) ==  -1) 
    { 
        perror("socket()"); 
        exit(EXIT_FAILURE);
    }

    struct in_addr svr_addr;
    uint16_t nport ;
    if(argc == 1)
    {
        char pstr_ip[] ="192.168.44.128";
        char hostport[] = "65523";

        svr_addr.s_addr =  inet_addr(pstr_ip);

        //printf("%s \n",inet_ntoa(svr_addr));

        nport = htons(atoi(hostport));
        //printf("%d\n",ntohs(nport));
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

    printf("ip addr %s , port %d\n",\
        inet_ntoa(sock_addr.sin_addr),\
                (sock_addr.sin_port));

    if(bind(sfd,(const struct sockaddr *)&sock_addr,\
            sizeof (struct sockaddr_in)) == -1 )
    {
        perror("bind() :");
        exit(EXIT_FAILURE);
    }

    //////////////////////////////////////////////////////////////////
    
    if (listen(sfd,MAX_LISTEN) == -1)
    {
        perror("listen() :");
        exit(EXIT_FAILURE);
    }/*}}}*/

    int confd = -1;
    struct sockaddr_in  con_sockaddr;
    socklen_t  sockaddr_len; 

    sockaddr_len = sizeof (struct sockaddr_in);
    if( (confd = accept(sfd, (struct sockaddr *)&con_sockaddr,\
                &sockaddr_len)) == -1)
    {
        perror("accept() :");
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        char recvbuf[128] = {'\0'};
        /*
           read(confd,recvbuf,strlen(recvbuf)+1);
           printf("msg recived : %s\n",recvbuf);
           write(confd,recvbuf,strlen(recvbuf)+1);
           bzero(recvbuf,sizeof recvbuf);
           */
        int nbyte = 0;
        if ((nbyte = recv( confd,recvbuf,sizeof recvbuf,0)) == -1)
        {
            perror("recv() :");
            exit(EXIT_FAILURE);
        }
        if (!nbyte)
        {
            printf("client disconnected\n");
            break;
        }
        printf("msg recived : %s\n",recvbuf);
        if( strncmp(recvbuf,"quit",4) == 0  )
            exit(EXIT_SUCCESS);
        bzero(recvbuf,sizeof recvbuf);

    }
    close(sfd);
    return 0;
}
        //////////////////////////////////////////////////////////////////
/*{{{   //                       not used code                          //
        //////////////////////////////////////////////////////////////////
    
       char recvbuf[128] = {'\0'};
       char sndbuf[500] = "hello world";

       struct sockaddr_in snder_sockaddr;

       socklen_t socklen =  sizeof(struct in_addr);

       while(1)
       { 
       if(recvfrom(sfd, recvbuf, sizeof recvbuf,\
       0, (struct sockaddr *)&snder_sockaddr, &socklen) < 0)
       {
       perror("server recvfrom()");
       exit(EXIT_FAILURE);
       }

       printf("ip addr %s , port %d\n", inet_ntoa(snder_sockaddr.sin_addr),ntohs(snder_sockaddr.sin_port));
       printf("message recivead : %s \n",recvbuf);


       if(sendto(sfd,recvbuf,strlen(recvbuf)+1, 0,\
       (const struct sockaddr *)&snder_sockaddr ,sizeof(struct sockaddr_in)) ==-1)
       {
       perror("server sendto()");
       exit(EXIT_FAILURE);
       }

       if(strncmp(recvbuf,"quit",4) == 0)
       exit(EXIT_SUCCESS);
       bzero(recvbuf,sizeof recvbuf);

       }
       */   /*}}}*/
