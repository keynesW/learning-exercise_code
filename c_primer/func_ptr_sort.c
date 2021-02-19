#include <stdio.h>


void sort_up(int *ptr,int cunt);
void sort_down(int *ptr,int cunt);
void print_arry(int *ptr_a,int size);
void sort(int *ptr ,void (*ptr_f)(int *,int ),int size);


int main()
{

    int arry[10] = {23,42,7,5,43,87,55,65,4,2};
    print_arry(arry,sizeof arry / sizeof arry[0]);
//    printf("sizeof arry / sizeof arry[0] %zd\n",sizeof arry / sizeof arry[0]);

    printf("----------------sort up-------------------\n");

    sort( arry,sort_up,sizeof arry / sizeof arry[0] );
    print_arry( arry,sizeof arry / sizeof arry[0] );

    printf("-----------------sort down------------------\n");

    sort( arry,sort_down,sizeof arry / sizeof arry[0] );
    print_arry( arry,sizeof arry / sizeof arry[0] );

    return 0;
}

void sort(int *ptr ,void (*ptr_f)(int * ,int  ),int size)
{

        (*ptr_f)(ptr,size);

}

void print_arry(int *ptr_a,int size)
{
    for(int i=0 ; i < size ;++i)
        printf("a[%d] = %d ",i,ptr_a[i]);
    printf("\n");

}


void sort_up(int *ptr,int cunt)
{

  int iter_i = 0,iter_j= 0 ,temp = 0;
  for(;iter_i<cunt;++iter_i) 
  {
        for(iter_j = 0;iter_j < cunt -1 ;++iter_j)  //   when use cunt there is a bug     ******* should use cunt -1***********
        {
            if(ptr[iter_j]>ptr[iter_j+1] )  
            {
                    temp = ptr[iter_j] ;
                    ptr[iter_j] = ptr[iter_j+1];
                    ptr[iter_j+1] = temp;
            }      
        }    
  }

}


void sort_down(int *ptr,int cunt)
{
//***************************************************//

        int iter_i = 0, iter_j = 0, temp = 0;
        for(;iter_i<cunt;++iter_i)
        {
            for(iter_j = iter_i ;iter_j<cunt;++iter_j) 
            {
                    if (ptr[iter_i]<ptr[iter_j])
                    {
                        temp = ptr[iter_j];
                        ptr[iter_j] = ptr[iter_i];
                        ptr[iter_i] = temp;
                    }    
            }
            //printf("%d  ",ptr[iter_i]);
            //printf("%d  ",iter_i);
            //printf("\n") ;
        }

/////////////////// these two methords under are same ///////////////////////
/*
        int iter_i = 0, iter_j = 0, temp = 0;
        for(;iter_i<cunt;++iter_i)
        {
            for(iter_j = 0 ;iter_j<cunt;++iter_j) 
            {
                    if (ptr[iter_i]<ptr[iter_j])
                    {
                        temp = ptr[iter_i];
                        ptr[iter_i] = ptr[iter_j];
                        ptr[iter_j] = temp;
                    }    
            }
        }
*/
/*
        int iter_i = 0, iter_j = 0, temp = 0;
        for(;iter_i<cunt;++iter_i)
        {
            for(iter_j = 0 ;iter_j<cunt;++iter_j) 
            {
                    if (ptr[iter_i]<ptr[iter_j])
                    {
                        temp = ptr[iter_j];
                        ptr[iter_j] = ptr[iter_i];
                        ptr[iter_i] = temp;
                    }    
            }
        }
*/
}
