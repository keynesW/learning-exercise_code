#include <stdio.h>/*{{{*/
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

#include <pthread.h>


#include <sys/select.h>
#include <sys/time.h>

//#include "link_list.h"
/*}}}*/

#define MAX_LISTEN  30


int main(int argc,const char * argv[])
{

    printf("argc : %d\n",argc);
    /*{{{*/ // configure server ip and port
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
        //char pstr_ip[] ="192.168.44.150";
        char pstr_ip[] ="192.168.0.121";
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
        ntohs(sock_addr.sin_port));
    putchar('\n');

    if(bind(sfd,(const struct sockaddr *)&sock_addr,\
            sizeof (struct sockaddr_in)) == -1 )
    {
        perror("bind() :");
        exit(EXIT_FAILURE);
    }

    if (listen(sfd,MAX_LISTEN) == -1)
    {
        perror("listen() :");
        exit(EXIT_FAILURE);
    }

    /*}}}*/

    //////////////////////////////////////////////////////////////////
/*{{{*/  // difine varable used in select
    int confd = -1;
    struct sockaddr_in  con_sockaddr;
    socklen_t  sockaddr_len; 
    sockaddr_len = sizeof (struct sockaddr_in);


    int cfd , maxfd = 0,ret;
    struct timeval timevl,tmp_timevl;
    timevl.tv_sec = 3;
    timevl.tv_usec = 0;

    fd_set rfds, tmpfds;

    FD_ZERO(&rfds);
    FD_ZERO(&tmpfds);

    FD_SET(sfd,&rfds);

    maxfd = sfd;

    int nbyte = -1;
    char recvbuf[1024] = {'\0'};

    printf("sfd :%d\n",sfd);/*}}}*/

    while(1)
    {
        
        tmpfds = rfds;
        tmp_timevl = timevl;

        if( (ret = select (maxfd +1, &tmpfds,NULL,NULL,&tmp_timevl)) <= 0 )
        {/*{{{*/ //dealing wiht select returned with an error
            if( ret == 0 )
                printf("wait timeout\n");
            else 
            {
                perror("select()");
                exit(EXIT_FAILURE);
            }
        }/*}}}*/
        else
        {/*{{{*/  //select normally returned 
            for(int i = 0; i <= maxfd ; i ++) // becarful with the condition in for loop
            {
                //printf("i : %d, maxfd : %d\n",i, maxfd);
                if(FD_ISSET(i,&tmpfds))
                {
                    if( i == sfd )
                    {/*{{{*/ //deal with a connect request
                        //printf("i : %d,sfd :%d\n",i,sfd);
                        int confd_tmp = -1;
                        if ( (confd_tmp = accept(sfd,(struct sockaddr*)&con_sockaddr,&sockaddr_len))  == 0)
                        {
                            perror("accept()");
                            exit(EXIT_FAILURE);
                        }
                        else
                        {
                            printf("client connected ip : %s, port : %d\n",inet_ntoa(con_sockaddr.sin_addr),ntohs(con_sockaddr.sin_port));
                            FD_SET(confd_tmp,&rfds); 
                            maxfd = ( maxfd < confd_tmp )?( confd_tmp ):(maxfd);
                            printf("maxfd %d\n,confd_tmp : %d\n",maxfd,confd_tmp);
                        }
                    } /*}}}*/
                    else //a connected confd is ready to read
                    {
                        /*{{{*/  // a msg recived from client
                        if( (nbyte = recv(i,recvbuf,sizeof recvbuf,0)) <= 0 )
                        {
                            if (nbyte == 0)
                            {
                                printf("client offine\n");
                                close(i);
                                FD_CLR(i,&tmpfds);
                            }
                            else
                            {
                                perror("i recv()");
                                exit(EXIT_FAILURE); 
                            }
                        }
                        else//successfully recived a msg 
                        {
                            printf("msg recived : %s\n",recvbuf);
                            bzero(recvbuf,sizeof recvbuf);
                        }

                    }/*}}}*/

                }

            }

        }
        /*}}}*/
    }

    return 0;
}


