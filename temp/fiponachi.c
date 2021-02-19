#include<stdio.h>

int recursive(int n);
int cyc_sum(int n);

int main()
{
   /* 
    int a[] = {1,2,3,4};
    
    int *ptr1 = (int *)(&a + 1);
    int *ptr2 = (int *)((int)a +1);

    printf("%x,%x\n",ptr1[-1],*ptr2);
    */
for(int i = 0;i < 6; i ++)
    printf("f(%d) = %d\n",i,cyc_sum(i));

    return 0;
}

int recursive(int n)
{
    if(n <= 1)
        return 1;
    else
        n = recursive(n -1) + recursive(n -2);
    return n;

}

int cyc_sum(int n)
{
    if(n<2)
        return 1;

    int f = 1, s = 1;
    int ret;

    for(int i=2;i<=n; i++)
    {
        ret = f + s;
        s = f;
        f = ret;
    }
    return ret;
}
