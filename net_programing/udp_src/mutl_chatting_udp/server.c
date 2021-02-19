//server

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <errno.h>

#include <unistd.h>
#include <sys/types.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "linklist.h"

int main(int argc,const char * argv[])
{

    printf("argc : %d\n",argc);

    /*{{{*/  // configure server ip and port

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
        //char pstr_ip[] ="192.168.44.150";
        char pstr_ip[] ="192.168.0.121";
        char hostport[] = "65523";

        svr_addr.s_addr =  inet_addr(pstr_ip);

        printf("%s \n",inet_ntoa(svr_addr));

        nport = htons(atoi(hostport));
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

    printf("--------------------server is ready------------------\n");
    putchar('\n');

    struct sockaddr_in sock_addr;
    bzero(&sock_addr,sizeof sock_addr);

    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = nport;
    sock_addr.sin_addr = svr_addr;

    if(bind(sfd,(const struct sockaddr *)&sock_addr,\
            sizeof (struct sockaddr_in)) == -1 )
    {
        perror("bind() :");
        exit(EXIT_FAILURE);
    }
    /*}}}*/


    char recvbuf[128] = {'\0'};
    char sndbuf[500] = "hello world";

    struct sockaddr_in snder_sockaddr;

    socklen_t socklen =  sizeof(struct sockaddr_in);

    client_t client_list ;
    client_list_init(&client_list);

    while(1)
    { 
        bzero(&snder_sockaddr,sizeof snder_sockaddr);

        if(recvfrom(sfd, recvbuf, sizeof recvbuf,\
                0, (struct sockaddr *)&snder_sockaddr, &socklen) < 0)
        {
            perror("server recvfrom()");
            exit(EXIT_FAILURE);
        }
        printf("in recvbuf : %s\n",recvbuf);

        if(strncmp(recvbuf,"quit",4) == 0)
        {
            client_list_del(&client_list,inet_ntoa(snder_sockaddr.sin_addr),\
                snder_sockaddr.sin_port);
            printf("client %s offline \n",inet_ntoa(snder_sockaddr.sin_addr));
            continue;
        }
        putchar('\n');

       /*{{{*/ // not used code
        //else
        /*
           printf("in snder_sockaddr :\n");
           int i = 0;
           char * iter = NULL;

           for( i = 0 , iter = (char *)&snder_sockaddr; i < sizeof snder_sockaddr; i++)
           printf("%c",iter[i]+48);

           putchar('\n');
           putchar('\n');

*/
        //printf("socklen : %d\n",socklen);
        //printf("naddr in snder_sockaddr %#x\n",snder_sockaddr.sin_addr.s_addr);
        //printf("nport in snder_sockaddr %#x\n",snder_sockaddr.sin_port);

        //printf("ip addr %s , port %d\n", inet_ntoa(snder_sockaddr.sin_addr),\
        ntohs(snder_sockaddr.sin_port));

        //printf("message recived : %s \n",recvbuf);

        //printf("%zd\n",sizeof(inet_ntoa(snder_sockaddr.sin_addr)));

        ////////////////////////////////////////////////////////////////////////


        /*
           for( ; list_iter && \
           ! strcpy(list_iter->cli_ip,inet_ntoa(snder_sockaddr.sin_addr)) ;\
           list_iter = list_iter->next)
           ;
        // (*(int *)(list_iter->cli_ip) != snder_sockaddr.sin_addr.s_addr) ;\
        list_iter = list_iter->next)
        ;

        if( list_iter == NULL )
        */

        /*}}}*/

        client_list_add(&client_list,\
            inet_ntoa(snder_sockaddr.sin_addr), snder_sockaddr.sin_port);

/*{{{*/ // not used code
        // print_list(&client_list);
        ////////////////////////////////////////////////////////////////////////

        //        printf("%s\n",client_list.next->cli_ip);
        //            printf("%s\n",client_list->cli_ip);
/*}}}*/
        client_t *list_iter = &client_list;

        //system("clear");
        printf("------------------dealing with client message-----------------\n");

        for(list_iter = client_list.next ; list_iter;
            list_iter = list_iter->next)
        {

            printf("\t---------------------------------------\n");
            snder_sockaddr.sin_family = AF_INET;
            snder_sockaddr.sin_addr.s_addr = inet_addr(list_iter->cli_ip);
            snder_sockaddr.sin_port = (list_iter->cli_port);
            printf("\tto ip addr %s , port %d\n", inet_ntoa(snder_sockaddr.sin_addr),ntohs(snder_sockaddr.sin_port));

            /////////////////////////////////////////////////////////////////////////

            //printf("prepare sending\n");
            putchar('\n');

            if(sendto(sfd,recvbuf,strlen(recvbuf)+1, 0,\
                    (const struct sockaddr *)&snder_sockaddr ,sizeof(struct sockaddr_in)) ==-1)
            {
                perror("server sendto()");
                exit(EXIT_FAILURE);
            }

            printf("\tmessage \" %s \" has been sent \n",recvbuf);
            putchar('\n');
            printf("\t---------------------------------------\n");
        }
        //printf("--------------------end of client message process------------------\n");
        bzero(recvbuf,sizeof recvbuf);
        printf("\tall messages has been sent ,total : %d\n",cunt);
        printf("--------------------end of one time service-------------------\n");

        putchar('\n');
    }

    //    }

    return 0;
}
