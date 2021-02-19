#include <stdio.h>
#include "quick.h"

 int *const quick_sort( int *const a, unsigned  int start, unsigned int end )
{
    unsigned int i = start  ;
    unsigned int j = end  ;
    int key = a[i];

    if( a != NULL && start >= 0 && (end-start) > 0)
    {
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

        if( i > start )
            quick_sort( a, start, i-1 );
        if( i < end )
            quick_sort( a, i+1, end );
        return a;
    }
    else
    {
        if( a == NULL )
            printf("invalid target to sort\n");
        if( start < 0 )
            printf("inappropriate start \n");
        if( (end < start)  )
            printf("inappropriate end \n");
        return NULL;
    }

}
