#include<stdio.h>  // perror
#include<string.h>  
#include<errno.h> // strerror errno


int main(int argc,char **argv)
{
    FILE * fps = fopen(argv[1],"r");
    FILE * fpd = fopen(argv[2],"w+");
    char buf[123] = {'\0'};
    int numbyte = -1; 

    //printf("%d\n",EOF);

    if(fps == NULL)
    {
        printf("fps open failed\n");
        return -1;
    }
    if(fpd == NULL)
    {
        printf("fpd open failed\n");
        return -1;
    }

    while( (numbyte = fread(buf,sizeof buf,1,fps)) >= EOF )
    {
        printf("%s\n",buf);
        if( fwrite(buf,sizeof buf, 1, fpd) < 0 )
            printf("fwrite error\n");

    }
    if(numbyte == -1)
        printf("fread failsd\n");

    fclose(fps);
    fclose(fpd);

    return 0;
}
