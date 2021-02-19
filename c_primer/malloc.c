#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Person {
    int age;
    char ident[10];
    char name[20];
};

void malloc_per_mem( struct Person **ptr_Per ,int size);
void input_iden(struct Person *ptr_Per);
void output_iden(struct  Person *ptr_Per);


void malloc_memory(int ** ptr,int size)
{
    int want_size = 4*size;
    *ptr = (int *)malloc(want_size);
    if(ptr == NULL)
        printf("malloc failed\n");  
}

void write_to_mem(int *ptr,int size)
{
    for(int iter = 0 ; iter < size ;iter ++)
        *ptr ++ = iter;
}
void print_mem(int *ptr, int size)
{
    printf("in memory\n");
    for(int iter = 0 ; iter < size ;iter ++)
        printf("%d elem = %d\n",iter +1,*ptr ++);
}

void string_mem(char **str)
{
    *str = (char *)malloc( 20 );
    strcpy(*str,"HelloWord");
}

void test(char *argv[])
{ 
    printf("______\n");
}


int main()
{
    char **ptr_argv = NULL;
    test(ptr_argv);


    int *ptr = NULL;
    char *ptr_c = NULL;
    string_mem(&ptr_c);
    printf("str : %s\n",ptr_c);
    
    malloc_memory(&ptr,2);
    printf("addr of ptr before free %p\n",ptr);
    printf("addr of &ptr before free %p\n",&ptr);

    write_to_mem(ptr,4);
    print_mem(ptr,5);

    free(ptr);    
    write_to_mem(ptr,4);
    free(ptr);    
    printf("addr of ptr after free %p\n",ptr);

    print_mem(ptr,5);


/*
    int size = 0;

    struct Person *ptr_Per = NULL;
    char *pstr = "fdadf";
    printf(pstr);

    printf("please enter the num of person\n");
    scanf("%d",&size);

    malloc_per_mem(&ptr_Per,size);

    for(int iter = 0; iter < size; iter++)
    {
        input_iden(&ptr_Per[iter]);
        output_iden(&(ptr_Per[iter]));
    }
*/
/*
    for(int iter = 0; iter < size; iter++)
        output_iden(&ptr_Per[iter]);
*/

//    free(ptr_Per);

/*
    ptr_Per = NULL;
    printf("NULL %d\n",!ptr_Per);
*/

/*
    void *ptr_max = NULL;
    int arry[] = {1024*1024,1024,1};
    for( ; )
       if(malloc(arry[i]))
       {
           i++;
       }
*/
    return 0;
}

void malloc_per_mem( struct Person ** ptr_Per ,int size)
{
    *ptr_Per = (struct Person *)malloc((sizeof (*ptr_Per)) *size);
    if(*ptr_Per == NULL)
        printf("malloc faild!");
}

void input_iden(struct Person *ptr_Per)
{
    printf("please enter your name :\n");
    scanf("%s",ptr_Per->name);

    printf("please enter your ID :\n");
    scanf("%s",ptr_Per->ident);

    printf("please enter your age :\n");
    scanf("%d",&ptr_Per->age);
}

void output_iden(struct  Person *ptr_Per)
{
    printf("hello       %s\n",ptr_Per->name);
    printf("your ID is  %s\n",ptr_Per->ident);
    printf("your age is %d\n",ptr_Per->age);
}
