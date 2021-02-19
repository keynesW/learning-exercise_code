#include <stdio.h>

void changeval(int *ptr_t, int *ptr_s);
void swap(int *a, int *b);
int main()
{
    int data = 0x12345678;
    int a = 5, b = 4 ;
    int *ptr = &data;
    int **ptr_r = &ptr;

    const int arry[3] = {0};

    *ptr = 200 ;
    printf("*ptr = %d\n",data);
    
    **ptr_r = 200 ; 
    printf("**ptr_r = %d\n",data);
    //changeval(&a,&b);
    swap(&a,&b);
    printf("a = %d , b = %d\n",a,b);
    printf("----------------------------------\n");

    
    const int * ptr_tst = &a;
    const int ** ptr_ts = &ptr_tst;
    //const int **const ptr_ts = &ptr_tst;
    printf("const int **ptr_ts = %d \n",**ptr_ts);
    ptr = arry;
    *ptr = 1;
    printf("arry[0] = %d\n",arry[0]);

    ptr = &a;
    ptr_ts = &ptr;   // assign a pointer which is not const 
                    //to an const pointer pointer
    *ptr = 10 ;
    printf("const int **ptr_ts = %d \n",**ptr_ts);

    return 0;
}
void changeval(int *ptr_t, int *ptr_s)
{
        int temp = 0;
        temp = *ptr_t;
        *ptr_t = *ptr_s;
        *ptr_s = temp;

}
void swap_step(int *ptr_t ,int *ptr_s)
{

        int temp = 0;
        temp = *ptr_t;
        *ptr_t = *ptr_s;
        *ptr_s = temp;

}
void swap_sp(int **ptr_t ,int **ptr_s)
{

        int temp = 0;
        temp = **ptr_t;
        **ptr_t = **ptr_s;
        **ptr_s = temp;

}
void swap(int *a, int *b)
{
        int *ptr_t =a ,*ptr_s =b;
        swap_step(ptr_t,ptr_s);
        //swap_sp(&ptr_t,&ptr_s);

}

