#include <stdio.h>


int recursive_mul(int m)
{
    int mul = m;

    if (m > 1)
        mul = m * recursive_mul(m-1);
    return mul;

}


int main()
{
    int a = 0;
    printf("please enter a number\n");
    scanf("%d",&a);
    
    a = recursive_mul(a);

    printf("recursive_mul of a = %d\n",a);

    return 0;
}
