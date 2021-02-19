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

#include <sys/wait.h>
#include <signal.h>

//#include <sys/un.h>


#define MAX_LISTEN  30
#define RECVBUFSIZE  1024
/*}}}*/

/*{{{*/ // packet protocol
enum packet_type
{
    DATA = 0, 
    HEART_DATA,
};

typedef struct packet_data{
    enum packet_type  type;
    char recvbuf[RECVBUFSIZE];
}packet_t;

void child_sighandler(int confd);
void child_process(int confd); 
void alarm_signal_handler(int arg);

packet_t recv_packet;/*}}}*/

int main(int argc,const char * argv[])
{

    printf("argc : %d\n",argc);

    /*{{{ // not used code
      if( signal(SIGCHLD,child_sighandler) == SIG_ERR )
      {
      perror("SIGCHLD signal()");
      exit(EXIT_FAILURE);
      }

      void child_sighandler(int confd)
      {
      printf("in child_progress_handle\n");
      wait(NULL);
      }
      *//*}}}*/

    /*{{{*/ //configure ip and port
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
        char pstr_ip[] ="192.168.44.150";
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
    }

    /*}}}*/

    int confd = -1;
    struct sockaddr_in  con_sockaddr;
    socklen_t  sockaddr_len; 
    sockaddr_len = sizeof (struct sockaddr_in);

    struct timeval timevl,tmp_timevl;
    timevl.tv_sec = 3;
    timevl.tv_usec = 0;
    socklen_t  timevl_len = sizeof timevl;

    int set_sock_ret = -1;
    if((set_sock_ret = setsockopt(sfd,SOL_SOCKET,SO_RCVTIMEO,(void *)&timevl,timevl_len)) == -1)
    {
        perror("setsock() :");
        exit(EXIT_FAILURE);
    }

    while(1)
    {

        if( (confd = accept(sfd, (struct sockaddr *)&con_sockaddr,\
                    &sockaddr_len)) == -1 )
        /*{{{*/ //deal with the confd which returned by accept 
        {
            if( errno == EAGAIN || errno ==EBADF ||errno == EINTR )
            {
                printf("accept time out\n");
                continue;                   ///////////////////////////
            }
            else
            {
                perror("accept() :");
                exit(EXIT_FAILURE);
            }
        }

        printf("confd : %d\n",confd);
        /*}}}*/

        ////////////////////////////////////////////////////////////////////

        pid_t ret_pid = -1;
        if ((ret_pid = fork()) == -1)
            /*{{{*/ // deal with fork() error 
        {
            perror("fork() :");
            exit(EXIT_FAILURE);
        }/*}}}*/

        if ( ret_pid == 0 )
        {
            child_process(confd);
        }

        if ( ret_pid > 0 )
        { /*{{{*/
            close(confd);// deal with in child progress no need in parent pro
            printf("progress %d has benn produced\n",ret_pid);
        }/*}}}*/
    }
    /*{{{
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
    {
    close(confd);
    exit(EXIT_SUCCESS);
    }
    bzero(recvbuf,sizeof recvbuf);

    }
    *//*}}}*/
    close(sfd);
    return 0;
}

void alarm_signal_handler(int arg)
{
    printf("client offline\n");
    exit(EXIT_FAILURE);
}

void child_process(int confd)
{ 
/*{{{*/

    printf("in child_progress_handle\n");

    if( signal(SIGALRM,alarm_signal_handler) == SIG_ERR)
    {
        perror("ALRM signal()");
        exit(EXIT_FAILURE);
    }
    alarm(10);


    printf("confd : %d\n",confd);

    while(1)
    {
        /*
           read(confd,recvbuf,strlen(recvbuf)+1);
           printf("msg recived : %s\n",recvbuf);
           write(confd,recvbuf,strlen(recvbuf)+1);
           bzero(recvbuf,sizeof recvbuf);
           */
        int nbyte = 0;
        if ((nbyte = recv( confd,&recv_packet,sizeof recv_packet,0)) == -1)
        {
            if( errno == EAGAIN || errno ==EBADF ||errno == EINTR )
            {
                printf("recive time out\n");
                continue;
            }
            else
            {
                perror("recv() :");
                exit(EXIT_FAILURE);
            }
        }

        if (!nbyte)
        {
            printf("client disconnected\n");
            exit(EXIT_FAILURE);
        }
        else//not empty packet
        {
            if( recv_packet.type == HEART_DATA )
            {
                printf("heart packet recived, %s\n",recv_packet.recvbuf);
                alarm(10);
            }
            else//data packet
            {

                printf("in progress %d msg recived : %s\n",getpid(),recv_packet.recvbuf);
/*
                if ((nbyte = send( confd,&recv_packet,strlen((const char *)&recv_packet)+1,0)) == -1)
                {
                    perror("send() :");
                    exit(EXIT_FAILURE);
                }
                if( strncmp(recv_packet.recvbuf,"quit",4) == 0  )
                    exit(EXIT_SUCCESS);
*/
                bzero(&recv_packet,sizeof recv_packet);

            }
        }
    }/*}}}*/
}

