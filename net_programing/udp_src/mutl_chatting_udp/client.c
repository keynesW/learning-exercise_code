//client

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <unistd.h>
#include <sys/types.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>



int main( int argc , const char * argv[] )
{

    printf("argc : %d\n",argc);

    int sfd = -1;/*{{{*/
    if((sfd = socket(AF_INET,SOCK_DGRAM,0)) ==  -1)
    {
        perror("socket()");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in svr_addr;
    struct in_addr nsvr_ip;

    if( argc == 1 )
    {
        bzero(&svr_addr,sizeof svr_addr);
        //nsvr_ip.s_addr = inet_addr("192.168.44.150");
        nsvr_ip.s_addr = inet_addr("192.168.0.121");

        svr_addr.sin_family = AF_INET;
        svr_addr.sin_port  = htons(atoi("65523"));
        svr_addr.sin_addr = nsvr_ip;

        printf("default ip to connect : %s\n",inet_ntoa(svr_addr.sin_addr));
        printf("default server port num %d\n",ntohs(svr_addr.sin_port));
    }
    else
        if( argc == 3 )
        {
            bzero(&svr_addr,sizeof svr_addr);
            nsvr_ip.s_addr = inet_addr(argv[1]);

            svr_addr.sin_family = AF_INET;
            svr_addr.sin_port  = htons(atoi(argv[2]));
            svr_addr.sin_addr = nsvr_ip;
        }
        else
            fprintf(stderr,"arguement error\n");/*}}}*/
    //////////////////////////////////////////////////////////////



    char sndbuf[500] = "hello world";
    char recvbuf[128] = {'\0'};
    pid_t ret_pid =  -1;

    if ((ret_pid = fork()) == -1)
    {
        perror("socket()");
        exit(EXIT_FAILURE);
    }


    if ( ret_pid  == 0 )
    {
    struct sockaddr_in sock_addr;
    bzero(&sock_addr,sizeof sock_addr);

    socklen_t socklen = sizeof (struct sockaddr_in);
    //printf("waiting for respone \n");
        while(1)
        {

    //printf("---------------waitting for message -----------------\n");
            if(recvfrom(sfd, recvbuf, sizeof recvbuf,\
                    0 , (struct sockaddr *)&sock_addr,&socklen ) < 0) 
            {
                perror("client recvfrom()");
                exit(EXIT_FAILURE);
            }

    //system("clear");

            printf("message recived from ip :%s, port: %d,\n\
                message: %s \n",inet_ntoa(sock_addr.sin_addr),ntohs(sock_addr.sin_port),recvbuf);
            putchar('\n');
            printf("--------------------------------------------\n");

            putchar('\n');
            putchar('\n');

            printf("---------------please input-----------------\n");
            putchar('\n');
        }
    }

    if ( ret_pid  > 0)
    {
        while(1)
        {

            int i = 0;
            while((sndbuf[i++] = getchar()) != '\n')
                ;

            for(char *iter = sndbuf; *iter ; iter ++)
                if(*iter == '\n')
                {
                    *iter = '\0';
                    break;
                }
            //printf("in sndbuf : %s\n", sndbuf);


            if (sendto(sfd,sndbuf,strlen(sndbuf),0,\
                    (const struct sockaddr *)&svr_addr ,\
                    sizeof(struct sockaddr)) ==-1 )
            {
                perror("client sendto()");
                exit(EXIT_FAILURE);
            }

            printf("---------------message  sent----------------\n");
            //printf("--------waitting for another message--------\n");
            
            putchar('\n');

            if(strncmp(sndbuf,"quit",4) == 0)
            {
                printf("bybe bybe\n");
                close(sfd);
                return 0;
                //exit(EXIT_SUCCESS);
            }
        }
    }


    return 0;
}

