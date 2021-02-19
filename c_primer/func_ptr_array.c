#include <stdio.h>


int func(int a);
int func1(int a);
int (* func2(int a))(int);

int main()
{
    int a = 5;
    //typedef int (*pfunc)(int );
    //pfunc arr[10]= {func,func1};
    //arr[1](a);

    int (* pfunc[10])(int) = { func, func1 };

    int (* (*pfunc_arr)[10])(int) = &pfunc;

    pfunc[1](a);

    return 0;
}

int func(int a)
{
    printf("%d  \n",a);
    return a;
}

int func1(int a)
{
    printf("%d  \n",a);
    return a;
}

int( * func2(int a))(int)
{
	//extern int func(int);
	printf("%d  ",a);
	return &func;
}
