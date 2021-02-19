#include <stdio.h>
#include <unistd.h>

int main(int argc, char ** argv )
{
    FILE * fp = fopen(argv[1],"a+");
    char str[12];
    
    fseek(fp,0,SEEK_END);

    size_t ret = ftell(fp);

    if(ret < 10)
    {
        printf("there is not 10 charcters\n");
        return -1;
    }
    else
    {
        fseek(fp,-10,SEEK_END);
        fread(str,10,1,fp);
        printf("str : %s\n",str);
    }        
    return 0;
}
