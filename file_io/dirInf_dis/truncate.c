/*******************************************************************
 *
 *     File Name    :      truncate.c
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Tue 20 Oct 2020 04:51:52 PM CST
 *
 ******************************************************************/

#include <stdio.h>
#include <unistd.h>

int main(int argc, char ** argv)
{
    int ret = truncate(argv[1],40);

    ret = truncate(argv[1],100);

    return 0;
}
