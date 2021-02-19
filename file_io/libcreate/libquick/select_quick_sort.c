#include<stdio.h>


int * select_sort(int *a,int n);
void quick_sort(int *a,int i,int j);


int main()
{
    int a[] = {3,2,8,4,5,6,7,0};
//    select_sort(a,(sizeof a / sizeof a[0])-1);

    
    quick_sort(a,0,sizeof a / sizeof a[0]-1);

    for(int i = 0;i<sizeof a/sizeof a[0];i++)
    {
        printf("%d ",a[i]);
    }
    putchar('\n');
    return 0;
}

void quick_sort(int *a,int start,int end )
{
    int i = start  ;
    int j = end  ;
    int key = a[i];

    while (i < j)
    {
        while( a[j] >= key && j > i )
            j--;

        a[i] = a[j];


        while( a[i] <= key && i < j )
            i++;

        a[j] = a[i];
    }

    a[i] = key;

    if( i-1 > start )
        quick_sort(a,start,i-1);
    if( i+1 < end )
        quick_sort(a,i+1,end);

}


int * select_sort(int *a,int n)
{
    int i,j  ;
    for(i = 1;i < n; i++)
    {
        int temp = a[i];
        for( j = i -1 ;j >= 0 && temp < a[j]; j--)
        {
                a[ j+1 ] = a[j];
        }
        a[j+1] = temp;
    }

}
