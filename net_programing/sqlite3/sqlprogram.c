/*******************************************************************
 *
 *     File Name    :      sqlprogram.c
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Wed 04 Nov 2020 06:45:53 PM CST
 *
 ******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int main(int argc, const char ** argv)
{
    if(argc < 2)
    {
        printf("invalid arguement\n");
        exit(EXIT_FAILURE);
    }
    if(argv[1] == NULL)
    {
        printf("invalid arguement\n");
        exit(EXIT_FAILURE);
    }

    int ret = -1;
    sqlite3 * ptrDB = NULL;
    if ((ret = sqlite3_open(argv[1],&ptrDB)) != SQLITE_OK)
    {
        fprintf(stderr,"sqlite3 open() : %s\n",sqlite3_errmsg(ptrDB));
        exit(EXIT_FAILURE);
    }
    //sprintf(sql,"insert into students (name, age ,score)values ( %s,%d,%d)",name,age,socre);
    char sql[2][128] = {
        "insert into mytable (name,age,score) values('stupid',0,0);",
        //".headers on",
        //".mode column",
        //"select * from mytable;",
        "select * from mytable;"
    };

   // char *psqlsa[]
    char * errmsg = NULL ;
    for(int i = 0; i < 1 ; i++)
        if(sqlite3_exec(ptrDB,sql[i],NULL,NULL,&errmsg) != SQLITE_OK)
            fprintf(stderr,"sqlite3_exec() : %s\n",errmsg);

    char **ptrRSLT = NULL;
    int pnRow = 0,pnColumn = 0;
    if (sqlite3_get_table(ptrDB,sql[1],&ptrRSLT,&pnRow,&pnColumn,&errmsg) != SQLITE_OK)
            fprintf(stderr,"sqlite3_exec() : %s\n",errmsg);
    int index = 0;
    for(int i = 0 ; i < pnRow; i++)
    {
        for( int j = 0;j < pnColumn; j++ )
        {
            printf("\t%s",ptrRSLT[index++]);
        }
        putchar('\n');
    }

//    sqlite3_free(ptrRSLT);
/*
    for(int i = 0 ; i < pnRow *pnColumn; i++ )
            printf("\t%s",ptrRSLT[i]);

*/


    sqlite3_close(ptrDB);

    return 0;
}
