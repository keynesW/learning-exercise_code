#include <stdio.h>/*{{{*/
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <unistd.h>
#include <sys/types.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <pthread.h>
#include <signal.h>
/*}}}*/


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
        //nsvr_ip.s_addr = inet_addr("192.168.44.150");
        nsvr_ip.s_addr = inet_addr("192.168.0.121");

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
            fprintf(stderr,"arguement error\n");

    ///////////////////////////////////////////////////////////////////////

    if (connect(sfd, (const struct sockaddr *)&svr_addr ,sizeof svr_addr ) == -1)
    {
        perror("connect() :");
        exit(EXIT_FAILURE);
    }/*}}}*/

    char sndbuf[500] = "hello world";

    pid_t ret_pid;
    if( (ret_pid = fork()) == -1)
    {
        perror("fork() :");
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        if(ret_pid > 0)
        {
            int i = 0;
            while((sndbuf[i++] = getchar()) != '\n')
                ;
            sndbuf[i] = '\0';
            /*
               for(char *iter = sndbuf; *iter ; iter ++)
               if(*iter == '\n')
               {
                    *iter = '\0';
                    break;
               }
            */
            printf("in sndbuf : %s\n", sndbuf);
            /*    
                  read(sfd,sndbuf,strlen(sndbuf)+1);
                  write(sfd,sndbuf,strlen(sndbuf)+1);
                  */       
            if(send(sfd,sndbuf,strlen(sndbuf)+1,0) == -1)
            {
                perror("send() :");
                pthread_exit(NULL); 
            }

            if(strncmp(sndbuf,"quit",4) == 0)
            {
                kill(ret_pid,SIGKILL);
                return 0;
                //exit(EXIT_SUCCESS);
            }
        }

        if(ret_pid == 0)
        {
            bzero(sndbuf,sizeof sndbuf);
            int nbyte = -1;
            if( (nbyte = recv(sfd,sndbuf,sizeof sndbuf,0)) == -1)
            {
                perror("send() :");
                pthread_exit(NULL); 
            }
            printf("response recived from server : %s\n", sndbuf);

            if(nbyte == 0)
            {
                //perror("recv() :");
                fprintf(stderr,"server exit");
                kill(ret_pid,SIGKILL);
                pthread_exit(NULL);
            }
        }
    }
    ///////////////////////////////////////////////////////////////////////{{{
    /*

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


    close(sfd);
    return 0;
}
