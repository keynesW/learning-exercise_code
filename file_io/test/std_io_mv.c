/*******************************************************************
 *
 *     File Name    :      std_io_mv.c
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Tue 20 Oct 2020 05:07:52 PM CST
 *
 ******************************************************************/

#include <stdio.h>

int main(int argc , char ** argv)
{
    printf("moving %s to %s \n",argv[1],argv[2]);

    if (argv[1] == NULL)
    {
        printf("please enter a src file to move \n");
        return -1;
    } 
    if (argv[2] == NULL)
    {
        printf("please enter a dst path to store \n");
        return -1;
    }  
    
    FILE * fps = NULL ,  * fpd = NULL;

    if((fps = fopen(argv[1],"r")) == NULL)
        printf("src open failed\n");
    if((fpd = fopen(argv[2],"w+")) == NULL)
        printf("dst open failed\n");
    
    char buf[1024] = {0};

    size_t retS = -1,retD = -1;
    while( (retS = fread(buf,sizeof buf, 1, fps)) > 0 )
    {
        retD = fwrite(buf,sizeof buf,1,fpd);
    }

    retS = fread(buf,sizeof buf, 1,fps);
    retD = fwrite(buf,sizeof buf,1,fpd);
    

    remove(argv[1]);
    fclose(fpd);

    printf("moving success \n");
    return 0;
}

