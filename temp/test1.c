/*******************************************************************
 *
 *     File Name    :      test.c
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Wed 20 Jan 2021 06:27:37 PM CST
 *     Description  :      Hello Word in C++ , GUN-style
 *
 ******************************************************************/

#include <stdio.h>
#include <stdlib.h>

struct st_t{
    int status;
    short * pdata;
    char errstr[32];
    int a[0];
}; 
const static volatile int abcd; 
int main( int argc,const char * argv[] )
{
    unsigned char a = 256;
    struct st_t st[16];
    printf("sizeof st_t  %zd\n",sizeof(struct st_t));
    char *p = (char *)(st[2].errstr + 32);
    printf("%d\n",p - (char *)st);

    struct st_t * pstru = malloc(sizeof(struct st_t)+3*sizeof(int));
    printf("malloc %d\n",pstru->a[2]);
    pstru->a[2] = 3;    
    printf("malloc %d\n",pstru->a[2]);

    return 0;
}

/*
struct HAR{
    int x;
    int y;
    struct HAR *p;
}h[2]; 
 
int main( int argc,const char * argv[] )
{
    h[0].y = 2;
    h[1].x = 3;
    h[0].p = &h[1];
    h[1].p = h;
    printf("%d %d\n",(h[0].p)->x,(h[1].p)->y);
    return 0;
}
*/
/*
void func(int *s)
{
    static int i = 0;
    do{
        s[i] += s[i + 1];
    }while(++i < 2);
}

int main( int argc,const char * argv[] )
{
    int k;
    int a[10] = {1,2,3,4,5,};
    for(k = 1; k < 3; k++)
        func(a);
    for(k = 0; k < 5; k++)
        printf("%d ",a[k]);
    return 0;
}
*/

/*
int main( int argc,const char * argv[] )
{
    int k = 0;
    int a[5][3] = {1,2,3,
        4,5,6,
        7,8,9,
        10,11,12,
        13,14,15
    };

    printf("%d\n",a[2][3]);
    int *p = a[0];
    printf(" *p %d\n",p[2*3+3]);

    int (*pa)[5][3] = &a; 
    printf("* pa %d \n",(*pa)[2][3]);
    
    int (*pa_1d)[3] = &a[2];
    printf("* pa_1d %d\n",(*pa_1d)[3]);
    
    pa_1d = a;
    printf("* pa_1d %d\n",pa_1d[2][3]);

    //int **p2 = (int **)a;
    //printf("* pa_1d %d\n",p2[2][3]);

    int **p2 = &p;
    printf("**p %d\n",(*p2)[2*3 + 3]);
    for(k = 0; k < 15; k++)
        printf("%d ",a[0][k]);
    putchar('\n');
    return 0;
}
*/
