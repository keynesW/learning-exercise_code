/*******************************************************************
 *
 *     File Name    :      test.c
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Tue 03 Nov 2020 08:14:32 AM CST
 *
 ******************************************************************/

#include <stdio.h>


void func()
{

    printf("in func, func : %p\n, &func : %p\n", func, &func );
    putchar('\n');

}

int main()
{
    
    void (*p)() = NULL ;


    printf("void (*p)() ;\np :%p,\n *p : %p,\n &p : %p,\n",p,*p,&p); 
    putchar('\n');

    //p = func;
    
    *(int *)&p =(int)func;
    printf("*(int *)&p =(int)func;\np :%p,\n *p : %p,\n &p : %p,\n",p,*p,&p); 
    putchar('\n');

    func();

/////////////////////////////////////////////////    
    (int *)p =(int)func;
/////////////////////////////////////////////////

    printf("(int *)p =(int)func;\np :%p,\n *p : %p,\n &p : %p,\n",p,*p,&p); 
    putchar('\n');

//    p();

/*
    (int *) p =(int)func+1;
    printf("p :%p,\n *p : %p,\n &p : %p,\n",p,*p,&p); 
    printf(" func %p, &func %p\n",func,&func);
*/

    return 0;

}
