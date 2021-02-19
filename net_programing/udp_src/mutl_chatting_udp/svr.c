/*******************************************************************
 *
 *     File Name    :      svr.c
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog?? :      http://www.    .com/ 
 *     Created Time :      Thu 29 Oct 2020 11:28:08 AM CST
 *
 ******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <sys/types.h>
#include "server.h"

int main()
{
    int sfd ;
    sfd = socket( AF_INET, SOCK_DRGRM, 0);
    if (sfd == -1)
        {
            perror("socket()");
            eixt(EXIT_FAILURE);
        }

    struct sockaddr_in  svr_addr;

    bzero(&sve_addr,sizeof(svr_addr));
    svr_addr.sin_family = AF_INET；
    svr_addr.sin_port = htons(atoi(argv[2]));
    svr_addr.sin_port = inet_addr(argv[1]);

    if( bind(sfd,(const struct sockaddr *)&svr_addr,sizeof(svr_addr)) < 0 ) 
    {
        perror("bind() :");
        exit(EXIT_FAILURE);

    }


    return 0;
}
