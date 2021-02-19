/*******************************************************************
 *
 *     File Name    :      process.c
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Thu 22 Oct 2020 10:29:18 AM CST
 *
 ******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc ,char ** argv)
{
    int cunt = 0;

    printf("welcome to process \n");
    while(cunt < 5)
    {
        cunt ++;
        printf("process.c :hello again\n");
        sleep(3);
    }

    exit(2);

}
