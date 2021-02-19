/*******************************************************************
 *
 *     File Name    :      myadd.c
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Wed 13 Jan 2021 03:51:49 PM CST
 *     Description  :      Hello Word in C++ , GUN-style
 *
 ******************************************************************/

#include <linux/module.h>
 
int my_add( int a ,int b)
{
    return a+b;
}

int my_add_p(int * a, int *b)
{

    return *a+*b;
}
EXPORT_SYMBOL(my_add);
EXPORT_SYMBOL(my_add_p);
MODULE_LICENSE("GPL");
