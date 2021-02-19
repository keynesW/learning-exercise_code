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

#include "link_list.h"/*}}}*/

#define MAX_LISTEN  30

void * child_progress_handle(void * confd); 


int main(int argc,const char * argv[])
{

    printf("argc : %d\n",argc);
    /*{{{*/
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
    
        int confd = -1;
        struct sockaddr_in  con_sockaddr;
        socklen_t  sockaddr_len; 
        sockaddr_len = sizeof (struct sockaddr_in);
        ///*
        link_list_t psfd_lklisthead;
        list_Head_Init(&psfd_lklisthead);


        pthread_t thread_num;
        //    pthread_attr_t pthread_attr;

        link_list_t pthread_lklisthead;
        list_Head_Init(&pthread_lklisthead);


    //////////////////////////////////////////////////////////////////

        //*/
    while(1)
    {

        if( (confd = accept(sfd, (struct sockaddr *)&con_sockaddr,\
                    &sockaddr_len)) == -1)
        {
            perror("accept() :");
            exit(EXIT_FAILURE);
        }
        else{
            printf("sfd : %d\n",confd);
            psfd_lklisthead.data = confd;
            list_Insert_end(&psfd_lklisthead,confd);

            //pthread_create(&thread_num, &pthread_attr, child_progress_handle,(void *)&psfd_lklisthead);
            if(pthread_create(&thread_num, NULL, child_progress_handle,(void *)&psfd_lklisthead) != 0 )
            {
                fprintf(stderr,"pthread_create : %s\n",strerror(errno));
                exit(EXIT_FAILURE);
            }
            if(pthread_detach(thread_num) != 0)
            {
                perror("pthread_detach()");
                continue;
            }

            list_Insert_end(&pthread_lklisthead,thread_num);
            print_linklist(&pthread_lklisthead);
        }
    }
    /*{{{*/ //multprogress code not used here
    //print_linklist(&psfd_lklisthead);


    //void child_progress_handle(int confd) 


    //*/
    //////////////////////////////////////////////////////////////////

    //shmget to store confd ( the socket file describetor of which client connected )



    /////////////////////////////////////////////////////////////////




    ////////////////////////////////////////////////////////////////////
    /*
       pid_t ret_pid = -1;
       if ((ret_pid = fork()) == -1)
       {
       perror("fork() :");
       exit(EXIT_FAILURE);
       }

       if ( ret_pid == 0 )
       {
       child_progress_handle(confd); 
       }

       if ( ret_pid > 0 )
       { 
       printf("progress %d has benn produced\n",ret_pid);
       }
       }

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
    */
    /*
       link_list_t * confd_list_iter = &psfd_lklisthead;
       for(;confd_list_iter->next ;confd_list_iter = confd_list_iter->next)
       {
       int  confd_iter = confd_list_iter->data;
       close(confd);
       }
       *//*}}}*/
return 0;
}

void * child_progress_handle(void * ptr) 
/*{{{*/
{
    printf("in child_progress_handle\n");

    while(1)
    {
        int confd = -1;
        confd = ((link_list_t *)ptr)->data;
        //printf("confd : %d\n",confd);
        
        print_linklist((link_list_t *)ptr);

        char recvbuf[128] = {'\0'};
        char offline_msg[] = "clinet offline";
        char *ptrbuf[3] = {recvbuf,offline_msg,NULL}; 

        int msgindx = 0;
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
            pthread_exit(NULL); 
        }

        if (!nbyte)
        {
            close(confd);
            printf("client disconnected\n");
            close(confd);
            msgindx = 1;
            del_node((link_list_t *)ptr,confd); 
            pthread_exit(NULL); 
            //exit(EXIT_FAILURE);
        }

        if( strncmp(recvbuf,"quit",4) == 0  )
        {
            printf("client offine\n");
            close(confd);
            msgindx = 1;
            del_node((link_list_t *)ptr,confd); 
            pthread_exit(NULL);
        }

        printf("in progress %d msg recived : %s\n",getpid(),recvbuf);


        ///////////////////////////////////////////////////////////////////////////////////

        link_list_t * confd_list_iter = ((link_list_t *)ptr)->next;
        for(;confd_list_iter ;confd_list_iter = confd_list_iter->next)
        {
            int  confd_iter = confd_list_iter->data;
            if ((nbyte = send( confd_iter,ptrbuf[msgindx],strlen(ptrbuf[msgindx])+1,0)) == -1)
            {
                perror("send() :");
                //exit(EXIT_FAILURE);
                //pthread_exit(NULL); 
                continue;
            }
            printf("confd_iter->data : %d,\n",confd_iter);

        }
        msgindx = 0;
        bzero(recvbuf,sizeof recvbuf);
        putchar('\n');
    }
}/*}}}*/

