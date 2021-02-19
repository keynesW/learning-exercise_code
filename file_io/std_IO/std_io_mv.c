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
#include <string.h>

int main(int argc , char ** argv)
{
    printf("moving %s to %s \n",argv[1],argv[2]);
    if(argc != 3)
    {
        printf("arguement error\n");
        return 0;
    }

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
    {
        printf("src open failed\n");
        return -1;
    }

    if( access(argv[2] , F_OK) == 0)
    {
        printf("file already exists\n");
        return -1;
    }
    if((fpd = fopen(argv[2],"w+")) == NULL)
    {
        printf("dst open failed\n");
        return -1;
    }

    char buf[1024] = {0};
    size_t retS = -1,retD = -1;
    //while( (retS = fread(buf,sizeof buf, 1, fps) ) != EOF )
    while( (retS = fread(buf,1,sizeof buf, fps) ) != EOF )
    {
        retD = fwrite(buf,1,retS,fpd);    
        /*
        retD = fwrite(buf,strlen(buf),1,fpd);   
        memset(buf,0,sizeof buf);
        */
        if(retD == -1)
        {
            printf("fwrite failed\n");
            return -1;
        }
        
        if(retS == 0)
            break;
    }

    if(retS == -1)
    { 
        printf("fread failed\n");
        return -1;
    }

    fclose(fps);
    remove(argv[1]);
    fclose(fpd);

    printf("moving success \n");
    return 0;
}

