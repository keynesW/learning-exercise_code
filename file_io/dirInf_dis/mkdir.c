/*******************************************************************
 *
 *     File Name    :      mkdir.c
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Wed 21 Oct 2020 10:27:36 AM CST
 *
 ******************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

int main(int argc , char ** argv)
{
    mkdir(argv[1],0777);

    return 0;
}
