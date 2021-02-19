#include "add.h"
#include "sub.h"
#include <stdio.h>

int main()
{

    int a = 4;
    int b = 5;
    
    printf("add of a b = %d\n",add(a,b));
    printf("sub of a b = %d\n",sub(a,b));
    printf("mul of a b = %d\n",mul(a,b));
    printf("divd of a b = %d\n",divd(a,b));
    printf("sub_mul of a b = %d\n",sub_mul(a,b));

    return 0;
}
