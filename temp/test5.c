/*******************************************************************
 *
 *     File Name    :      test5.c
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Tue 26 Jan 2021 07:21:04 PM CST
 *     Description  :      Hello Word in C++ , GUN-style
 *
 ******************************************************************/

#include <stdio.h>
#include <stdlib.h>

struct s1{
    char ch, *q;
    union str{
        short a;
        short b;
        int c:2,d:1;
    }str;
};
int fun(int x)
{
    static int temp = 2;
    temp += x;
    return temp;
}
struct s1 t;
struct s1 *ps;

int main( int argc,const char * argv[] )
{
    int k = 2,m = 1, ret;
    ret = fun(k);
    ret += fun(m);
    printf("%d\n",ret);
    printf("--------------------------------\n");
    
    int data1 = -16;
    unsigned int data2 = 4;

    printf("%d\n",data1 + data2);
    (data1 + data2) > 0? printf(" > 0\n"):printf(" > 0\n");
    printf("--------------------------------\n");
    
    char *p ,*q;
    p = (char *)malloc(sizeof(char *)*20);
    q = p;
    scanf("%s%s",p,q);
    printf("%s %s\n",p,q);

    printf("--------------------------------\n");
    printf("%zd\n",sizeof(t));
    ps = &t;
    ps->str.a = 12;
    ps->str.b = 13;
    printf("%d\n",ps->str.c);
    printf("%d\n",ps->str.d);

    ps->str.a = (ps->str.a)^5;
    ps->str.a = (ps->str.a)|5;
    printf("%d\n",ps->str.a);
    printf("%d\n",ps->str.a);

    return 0;
}
