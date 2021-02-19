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
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>


void recursive_readdir(char * dir_name,unsigned int indentation );

int main(int argc, char ** argv)
{
    
    if(argc != 2)
    {
        printf("arguement error\n");
        return -1;
    }

    recursive_readdir(argv[1],0);

     

    return 0;
}

void recursive_readdir(char * path_name,unsigned int indentation )
{
    
    DIR * ptr_dir = opendir(path_name);
    if(ptr_dir == NULL)
    {
        perror("opendir()");
        return;
    }

    struct dirent * ptr_dirI = NULL;

    while(ptr_dirI = readdir(ptr_dir))
    {
        if (ptr_dirI == NULL)
            perror("readdir()");

        if(ptr_dirI->d_type != DT_DIR ) 
        {
            for(int i = 0; i < indentation ; i++)
                printf("\t");
            printf("dir_Iterm is :%s\n",ptr_dirI->d_name);
        }
        else
        {
            if( *ptr_dirI->d_name != '.' ) 
            {
                char path_name_cat[256]  = {'\0'};

                for(int i = 0; i < indentation ; i++)
                    printf("\t");

                int s = 0;
                for(  ;path_name[s] ;s++)
                    path_name_cat[s] = path_name[s];
                path_name_cat[s] = '/' ;
                path_name_cat[s+1] = '\0' ;

                strcat(path_name_cat,ptr_dirI->d_name);

                printf("dir to opendir :%s\n",path_name_cat);

                recursive_readdir( path_name_cat,indentation +1 );
            }
        }
    }
   // return ptr_dirI;
}
