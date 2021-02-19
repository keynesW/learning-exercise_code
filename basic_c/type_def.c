#include <stdio.h>


typedef  int int_32_t;
typedef  int * int_ptr;
typedef  int arry5[5];
typedef  int func(int , int);
typedef  int func(int , int);
typedef  int (*func_ptr)(int,int);

//int add(int a ,int b);
func add;
int main()
{
    int_32_t  a = 10 ;
    int_ptr ptr_int= &a;
    arry5  arry = {0};
    func *func_pf; // typedef will add () for the content to replace
    func_ptr add_ptr;

    func_pf = add;
    add_ptr = add;

    printf("add %d\n", add(a,a));
    printf("fucn_pf %d\n" , func_pf(a,a));
    printf("add_ptr %d\n",add_ptr(a,a));

    return 0;

}
int add(int a ,int b)
{
    return (a + b);
}
