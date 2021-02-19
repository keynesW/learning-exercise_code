/*
#include <stdio.h>
#define SIZE 5
void get_pol(int *max, int *min,int *ptr_a);
int main() 
{ 
    int iter = 0, num = 0;
    int arry[SIZE] = {0};
    int max = 0 , min =0;
    printf("please enter the elem \n");
    //scanf("%d",&num);
  
    
//    while(iter<SIZE && scanf("%d",&arry[iter]) != 0)
   {
       // scanf("%d",&arry[iter]); 
//       iter++; 
    }


    while(iter<SIZE )
   {
        scanf("%d",&arry[iter]); 
        iter++; 
    }

    get_pol(&max,&min,arry);

    for(int iter = 0 ; iter < SIZE ; iter ++)
        printf("arry[%d] = %d ",iter,arry[iter]);
    printf("\n");

    printf("max elem = %d, min elem = %d\n",max,min);
    return 0 ;
}



void get_pol(int *max, int *min,int *ptr_a)
{
    *max = ptr_a[0];
    *min = ptr_a[0];
    for(int iter = 0 ; iter < SIZE ; iter ++)
    {   
        
        if(*max < ptr_a[iter])
           * max = ptr_a[iter];
        if(*min > ptr_a[iter])
           * min = ptr_a[iter]; 
    }
}

*/



#include<stdio.h>

int input_arry(int * ptr_a , int size);
void output_arry(int *ptr_a,int size);

int main()
{
  // int iter = 0; 
   int arry[4] = {0};
 //  int* ptr = &arry[0];
/*
   for(;iter < 4; iter++)
   //     ptr[iter] = iter;
   //   *(ptr + iter) = iter;

   {
       // *ptr = iter;
       //ptr ++;
        *ptr++ = iter;
   }

   for(iter = 0;iter < 4; iter++)
        printf("arry[%d] = %d ",iter,arry[iter]);
*/
   int cunt = 0;
   cunt = input_arry(arry,sizeof arry /sizeof arry[0]);
   printf("cunt = %d\n",cunt);

   output_arry(arry,sizeof arry /sizeof arry[0]);
    return 0 ;

}

int input_arry(int * ptr_a , int size)
{
    int cunt = 0;
    printf("please input 4 numbers :\n");
    for(int iter = 0 ; iter < size ; iter++)
    {
        if(scanf("%d",&ptr_a[iter]))
                cunt++;
//        printf("iter = %d\n",iter);
    }

    //******************************************************//
    //                 scanf("%d",addr);                    //
    //  if scanf encounter an element that's not an integer //
    // it will leave the element in the input buffer which  //
    // will make the cyclic continue with read failer then  //
    // the iter will ++ until the cyclic end                //
    //******************************************************//
    
    return cunt;
}

void output_arry(int *ptr_a,int size)
{

    for(int iter = 0 ; iter < size ; iter++)
        printf("arry[%d] = %d\n",iter,ptr_a[iter]);
}
