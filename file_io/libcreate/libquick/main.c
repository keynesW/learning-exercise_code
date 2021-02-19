#include<stdio.h>
#include"quick.h"


int main()
{
    int a[] = {3,2,8,4,5,6,7,0};
//    select_sort(a,(sizeof a / sizeof a[0])-1);

    
    quick_sort(a,0,sizeof a/ sizeof a[0] -1); 

    for(int i = 0;i<sizeof a/sizeof a[0];i++)
    {
        printf("%d ",a[i]);
    }
    putchar('\n');
    return 0;
}
