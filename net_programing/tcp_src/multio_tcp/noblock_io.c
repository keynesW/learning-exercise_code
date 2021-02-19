/*******************************************************************
 *
 *     File Name    :      noblock_io.c
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Tue 03 Nov 2020 10:23:35 AM CST
 *
 ******************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>

int main()
{
    int num = 0;
    int flag = fcntl(0,F_GETFL);
    fcntl(0,F_SETFL,flag | O_NONBLOCK);

    scanf("%d",&num);
    printf("num : %d\n",num);


    return 0;
}
