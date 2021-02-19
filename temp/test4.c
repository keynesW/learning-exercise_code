/*******************************************************************
 *
 *     File Name    :      test4.c
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Mon 25 Jan 2021 06:30:59 PM CST
 *     Description  :      Hello Word in C++ , GUN-style
 *
 ******************************************************************/

#include <stdio.h>

#define _STR(s) #s
#define STR(s) _STR(s)

#define XZ(x) UZ
#define UZ   "werw"

const char *pstr = XZ(UZ);

int foo(int n) 
{
    printf("%d ",n);
    if(n <= 2)
        return n;
    return foo(n - 1) + foo(n - 2);
}

union data{
    struct {
        int x;
        int y;
    }s;
    int x;
    int y;
}d;

typedef struct Data{
    unsigned int a : 2;
    unsigned int b : 4;
    unsigned int   : 0;
    unsigned int c : 3;
    unsigned int   : 0;
//    unsigned int d : 3;
}DATA;

DATA t = {.a = 3, .b = 6, .c = 7};

struct dat{
    long num;
    char * ptr;
    short int data;
    char ha;
    short ba[5];
}*pdat;



int main( int argc,const char * argv[] )
{
    printf("%zd\n",sizeof(t));
    printf("%s\n",pstr);

    printf("%d\n",foo(6));
    d.x = 1;
    d.y = 2;

    printf("%d  %d\n",d.x,d.y);

    d.s.x = d.x * d.x;
    d.s.y = d.y + d.y;
    printf("%d %d \n",d.s.x,d.s.y);

    struct Data *p = &t;
    p->a = (p->a) & 3;
    p->b = (p->b) | 4;
    p->c = (p->c) ^ 5;
    //printf("%p",&p->a,&p->c);
    //unsigned short *pshort = (void *)&t;
    unsigned char *pc = (void *)&t;
    printf("%#x\n",*pc);
    printf("%d %d %d\n",t.a,t.b,t.c);
    
    pdat = (struct dat*)0x10000000;
    printf("%zd\n",sizeof(struct dat));
    printf("%p\n",pdat + 0x200);
    printf("%p\n",(char*)pdat + 0x200);

    printf("%s\n",__DATE__);
    //char buf[1024] = STR(__DATE__);
    char buf[1024] = _STR(__DATE__);
    printf("%s\n",buf);
    //printf("%zd\n",sizeof(long));
    char buff[1024] = "asfjaksdjfk"; 
    printf("%s\n",buff);

    return 0;
}
