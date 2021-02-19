/*******************************************************************
 *
 *     File Name    :      dir_disp.c
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Wed 21 Oct 2020 09:43:25 AM CST
 *
 ******************************************************************/

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>


int main(int argc, char ** argv)
{
    if(argc != 2)
    {
        printf("arguement error\n");
        return -1;
    }
    DIR * ptr_dir = opendir(argv[1]);
    if(ptr_dir == NULL)
    {
        perror("opendir()");
        return -1;
    }
    struct dirent * ptr_dirI = NULL;
    
    while(ptr_dirI = readdir(ptr_dir))
        printf("dir_Iterm is :%s\n",ptr_dirI->d_name);
     
    if (ptr_dirI == NULL)
        perror("readdir()");

    return 0;
}
