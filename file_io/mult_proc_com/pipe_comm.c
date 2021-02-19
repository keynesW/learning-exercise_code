/*******************************************************************
 *
 *     File Name    :      mian.c
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Fri 23 Oct 2020 01:43:32 PM CST
 *
 ******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <fcntl.h>
#include <wait.h>


int main(int argc , const char * argv[])
{

    int pfd[2] = {0};
    pipe(pfd);

    printf("pfd[1] = %d  pfd[2] = %d\n",pfd[0],pfd[1]);

    if( fork() == 0 )
    {
        //sleep(6);
        close(pfd[0]);
        write(pfd[1],"helloword",9);
        //write(pfd[0],"writepfdw[0]",9);
        printf("write ended\n");
    }
    else
    {
        char buf[12] = {"init adf"};
        printf("%s\n",buf);

        close(pfd[1]);
        read(pfd[0],buf,sizeof buf);
        printf("read suspended\n");
        printf("%s\n",buf);

        //read(pfd[1],buf,sizeof buf);
        printf("%s\n",buf);
    }


    return 0;

}
