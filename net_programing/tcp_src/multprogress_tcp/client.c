#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <errno.h> 
#include <unistd.h>
#include <sys/types.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <pthread.h>

#define RECVBUFSIZE  1024

enum packet_type
{
    DATA = 0, 
    HEART_DATA,
};

typedef struct packet_data{
    enum packet_type  type;
    char recvbuf[RECVBUFSIZE];
}packet_t;



void * heart_thread(void *arg);


int main( int argc , const char * argv[] )
{

    printf("argc : %d\n",argc);
/*{{{*/
    int sfd = -1;
    if((sfd = socket(AF_INET,SOCK_STREAM,0)) ==  -1)
    {
        perror("socket()");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in svr_addr;
    struct in_addr nsvr_ip;

    if( argc == 1 )
    {
        bzero(&svr_addr,sizeof svr_addr);
        nsvr_ip.s_addr = inet_addr("192.168.44.150");

        svr_addr.sin_family = AF_INET;
        svr_addr.sin_port  = htons(atoi("65523"));
        svr_addr.sin_addr = nsvr_ip;

        printf("default ip %s\n",inet_ntoa(svr_addr.sin_addr));
        printf("port num %d\n",ntohs(svr_addr.sin_port));
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

///////////////////////////////////////////////////////////////////////
    
    if (connect(sfd, (const struct sockaddr *)&svr_addr ,sizeof svr_addr ) == -1)
        {
            perror("connect() :");
            exit(EXIT_FAILURE);
        }

    pthread_t thread_num;
    pthread_create(&thread_num,NULL,heart_thread,(void *)sfd);
    pthread_detach(thread_num);

    char sndbuf[500] = "hello world";
    while(1)
    {

        int i = 0;
        while((sndbuf[i++] = getchar()) != '\n')
                ;
        sndbuf[i] = '\0';

        printf("in sndbuf : %s\n", sndbuf);

/*{{{  // not used code
        for(char *iter = sndbuf; *iter ; iter ++)
            if(*iter == '\n')
            {
                *iter = '\0';
                break;
            }
*//*}}}*/

        if(strncmp(sndbuf,"quit",4) == 0)
            exit(EXIT_SUCCESS);
        /*    
              read(sfd,sndbuf,strlen(sndbuf)+1);
              write(sfd,sndbuf,strlen(sndbuf)+1);
              */       
        if(send(sfd,sndbuf,strlen(sndbuf)+1,0) == -1)
        {
            perror("send() :");
            exit(EXIT_FAILURE);
        }
        bzero(sndbuf,sizeof sndbuf);

        if(recv(sfd,sndbuf,sizeof sndbuf,0) == -1)
        {
            perror("send() :");
            exit(EXIT_FAILURE);
        }
        printf("response recived from server : %s\n", sndbuf);
    }
///////////////////////////////////////////////////////////////////////

    close(sfd);
    return 0;
}
/*{{{  not used code

    char sndbuf[500] = "hello world";
    char recvbuf[128] = {'\0'};

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
        printf("in sndbuf : %s\n", sndbuf);


        if(strncmp(sndbuf,"quit",4) == 0)
            exit(EXIT_SUCCESS);

        if (sendto(sfd,sndbuf,strlen(sndbuf),0,\
                (const struct sockaddr *)&svr_addr ,\
                        sizeof(struct sockaddr)) ==-1 )
        {
            perror("client sendto()");
            exit(EXIT_FAILURE);
        }

        if(recvfrom(sfd, recvbuf, sizeof recvbuf,\
               0 , NULL, NULL ) < 0) 
        {
            perror("client recvfrom()");
            exit(EXIT_FAILURE);
        }
        printf("message recivead : %s \n",recvbuf);
    }
*//*}}}*/

void * heart_thread(void *arg)
{
    int sfd = (int) arg;   
    packet_t heart_packet;
    heart_packet.type = HEART_DATA;
    strcpy(heart_packet.recvbuf,"heart beat\n");
    while(1)
    {
        if(send(sfd,&heart_packet,sizeof heart_packet,0) == -1)
        {
            perror("send() :");
            exit(EXIT_FAILURE);
        }
        sleep(2);
    }

}
