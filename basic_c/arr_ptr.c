#include <stdio.h>

int  arrylen(int (*ptr_arr)[],int n );
void input_arry(int *ptr,int size);
void output_arry(int *ptr,int size);
void _input_arry(int (*ptr)[3],int size);
void _output_arry(int (*ptr)[3],int size);
void to_upper(char (*ptr)[10],int size);
int islittle(char chr);
void print_chr_arr(char (*ptr_c)[10],int size);
void print_p_arr(int ** ptr_a,int dems,int size);
void print_p_arry(int **ptr_a,int dems,int size);
void print_ptr_arr(char *(*ptr)[5]);

int main()
{
    char buf[100]; 
    char *ptr = buf;
    printf("sizeof *ptr = %zd\n",sizeof *ptr);

    printf("sizeof int %zd\n",sizeof (int));
    int arry[5] = {1,2,3,4,5};
    int a, b ,c = 5;
    a = b += c ;
    int (*ptr_arr)[] = &arry;
    
    ////////////////////////////

        char arr_c[] = {1,2,3,4,5};
        char *ptr = (char *)(&arr_c + 1) ;
//        printf("*ptr = %d\n",ptr[-1]);

//        ptr = (char *)((int)&arr_c +1);
//        printf("*ptr = %d\n",*ptr);

//        ptr = (char *)((int*)&arr_c +1);
//        printf("*ptr = %d\n",*ptr);

    /////////////////////////// 

    int arry_t[2][3] = {0};
/*
    input_arry(arry_t[0],sizeof arry_t/sizeof arry_t[0][0]);
    output_arry(arry_t[0],sizeof arry_t /sizeof arry_t[0][0]);
    _input_arry(arry_t,sizeof arry_t/sizeof arry_t[0][0]);
    _output_arry(arry_t,sizeof arry_t /sizeof arry_t[0][0]);
    

    arrylen(ptr_arr,sizeof arry/sizeof arry[1]);
*/
    ////////////////////////////////////////////////////////
    

    char arry_c[3][10] = { {"abcA"},{"EFGH"},{"Hijk"}};


    to_upper(arry_c,3); 
    print_chr_arr(arry_c,3);

    int arr_i[3][4] = {1,2,3,4,5,6,7,8,9,0,1,2};

    int *ptr_a[] = {arr_i[0],arr_i[1],arr_i[2]};
    print_p_arr(ptr_a,3,4);
    print_p_arry(ptr_a,3,4);

   ///////////////////////////////////////////////////////
   

    char * arr[5] = {"dfa","fasdf","dlda",NULL};
    print_ptr_arr(&arr) ;

    return 0; 
}

void print_ptr_arr(char *(*ptr)[5])
{

    for (int iter = 0 ; (*ptr)[iter]; iter ++)
        printf("arr[%d] : %s \n",iter,(*ptr)[iter]);
} 

void input_arry(int *ptr,int size)
{
    for(int iter = 0; iter < size ;iter++)
        scanf("%d",ptr + iter);
}

void output_arry(int *ptr,int size)
{
    for(int iter = 0; iter < size ;iter++)
        printf("in arr_t[%d] = %d\n",iter,ptr[iter]);
}

void _input_arry(int (*ptr)[3],int size)
{
    for(int iter = 0; iter < size ;iter++)
        scanf("%d",ptr[0] + iter);
}

void _output_arry(int (*ptr)[3],int size)
{
    for(int iter = 0; iter < size ;iter++)
    {
        printf("in arr_t = %d\n",ptr[0][iter]);
        printf("in arr_t = %d\n",*((*ptr)+iter));
    }
}

int  arrylen(int (*ptr_arr)[5],int n)
{
    for(int iter = 0; iter < 5;iter ++) 
    printf("arry[%d] = %d\n", iter,(*ptr_arr)[iter]);
    
    printf("sizeof *ptr_arr %zd\n",sizeof *ptr_arr);
    printf("sizeof *ptr_arr %p\n",ptr_arr);

}

int islittle(char chr)
{
    if(chr>=97&&chr<=122)
        return 1;
    return 0;
}

void to_upper(char (*ptr)[10],int size)
{
    int iter_i = 0 ,iter_j = 0;
    
    for( ;iter_i <size ; iter_i ++)
    {
        for( iter_j = 0 ;iter_j < 10; iter_j ++)
        if(islittle(ptr[iter_i][iter_j]))
            ptr[iter_i][iter_j] -= 32;
    }
}

void print_chr_arr(char (*ptr_c)[10],int size)
{
    int iter_i = 0 ,iter_j = 0;
    
    for( ;iter_i < size ; iter_i ++)
    {
        for(iter_j = 0 ;iter_j < 10; iter_j ++)
        //printf("in arry_c arryc[%d][%d] = %c \n",
        //           iter_i,iter_j,ptr_c[iter_i][iter_j]);
            printf("%c",ptr_c[iter_i][iter_j]);
        printf("\n");
    }
}

void  print_p_arr(int ** ptr_a,int dems,int size)
{
    int iter_i = 0 ,iter_j = 0;
    for( ; iter_i < dems ; iter_i ++)
    {
        for (iter_j = 0 ;iter_j < size ; iter_j ++)
            printf(" %d ",ptr_a[iter_i][iter_j]);
    printf("\n");
    }
}

void print_p_arry(int **ptr_a,int dems,int size)
{
    int iter_i =0, iter_j = 0 ;
    for( ;iter_i<dems;iter_i++)
    {
        for(iter_j = 0;iter_j<size; iter_j ++)
            printf("%d ",(*ptr_a)[iter_j]);
        ptr_a++;
        printf("\n");
    }
}
