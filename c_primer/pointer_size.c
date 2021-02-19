#include <stdio.h>

int  byte_sum(unsigned char *ptr_c,int size);
void swap_byte(unsigned char *ptr_c,int size);
void print_byte(unsigned char * ptr_c,int size);
void byte_swap(unsigned char * ptr_c,int size);

int main()
{
    int *ptr_i = NULL;
    printf("sizeof int *ptr_i  = %zd\n",sizeof ptr_i);
//*******************************************************//


    int sum = 0 ;
    unsigned int x = 0x12345678;
    print_byte((unsigned char *)&x,sizeof x);
    printf("\n");

//    sum = byte_sum((unsigned char *)&x,sizeof x);
    swap_byte((unsigned char *)&x,sizeof x);
    print_byte((unsigned char *)&x,sizeof x);
    printf("\n");

    printf("x = %#x\n", x);
    printf("\n");

 //   printf("sum of int bit %d\n",sum);
    byte_swap((unsigned char *)&x,sizeof x);
    printf("x = %#x\n", x);

    return 0;
}

int  byte_sum(unsigned char *ptr_c,int size)
{

    int sum = 0 ;

    for(int iter = 0 ; iter < size ;iter++)
            sum += ptr_c[iter];

    return sum;

}

void swap_byte(unsigned char *ptr_c,int size)
{
    unsigned char *ptr_s = ptr_c, *ptr_e = ptr_c + size -1;
     for(int iter = 0 ;ptr_c < ptr_e ;ptr_c++,ptr_e--)
      {
            unsigned char temp = 0 ;
            temp =  *ptr_c;
            *ptr_c = *ptr_e;
            *ptr_e = temp;
     }

}

void print_byte(unsigned char * ptr_c,int size)
{
    for (int iter = 0 ; iter < size ;iter ++) 
        printf("byte of Arguement : %#x\n",ptr_c[iter]);
}

void byte_swap(unsigned char * ptr_c,int size)
{

    for (int iter = 0 ; iter < size ;iter ++) 
         ptr_c[iter] = (ptr_c[iter] << 4)|(ptr_c[iter] >> 4) ;

}
