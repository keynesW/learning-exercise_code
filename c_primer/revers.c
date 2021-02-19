#include <stdio.h> 

void find_exr(int *arry,int SIZE,int *max, int* min); 
void revers(int *arry,int SIZE);
void print_arry(int *ptr_a,int size);
void print_arr(char *ptr_a,int size);

int main()
{
    char arry_c[3] = {'a','b','c'};
    char arry_s[3] = {'a','b','c'};
    int arry[] = { 4,5,2,6,23,67,9};
    int max = 0 , min = 0;

    printf("addr of arr_c : %p\n" ,arry_c);
    printf("addr of arr_s : %p\n" ,arry_s);

    printf("addr of max : %p\n" ,&max);
    printf("addr of min : %p\n" ,&min);
    printf("addr of arry : %p\n" ,arry);
    printf("addr of arry : %p\n" ,&arry+1);

    printf("-------------------------------\n");

    printf("in arry_c : %s\n",arry_c);
    printf("in arry_s : %s\n",arry_s);
    print_arr(arry_c,3);

    printf("-------------------------------\n");

    char arry_t[4] = {'\0','0','1'};
    print_arr(arry_t,4);

    print_arry(arry,sizeof arry / sizeof arry[0]) ;

//***************************  1  *******************************//

    find_exr(arry,sizeof arry/sizeof (int),&max,&min);
    printf("max = %d, min = %d \n",max,min);

//***************************  2  *******************************//

    revers(arry,sizeof arry/sizeof (int));
    print_arry(arry,sizeof arry / sizeof arry[0]) ;
    
    return 0 ;
}



void find_exr(int *arry,int SIZE,int *max, int* min)
{
    *max = arry[0];
    *min = arry[0];
    for(int i = 0 ; i < SIZE; ++i)
    {
        if(*max < arry[i])
            *max = arry[i];
        if(*min > arry[i])
            *min = arry[i];     
    }
}

void revers(int *arry,int SIZE)
{
    for(int iter_i = 0 ; SIZE/2 - iter_i > 0 ; ++iter_i)
    {
        int temp = 0;
        temp = arry[iter_i];
        arry[iter_i] = arry[SIZE-iter_i-1];
        arry[SIZE-iter_i-1] = temp;
    }
}

void print_arry(int *ptr_a,int size)
{
    for(int i=0 ; i < size;++i)
        printf("a[%d] = %d ",i,ptr_a[i]);
    printf("\n");

}

void print_arr(char *ptr_a,int size)
{
    for(int i=0 ; i < size;++i)
        printf("a[%d] = %c ,ascii is : %d\n",i,ptr_a[i],ptr_a[i]);
    printf("\n");

}
