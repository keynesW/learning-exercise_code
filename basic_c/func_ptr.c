#include <stdio.h>


int sub(int a, int b)
{
    return (a - b);
}
int add(int a, int b)
{
    return (a + b);
}

int mult(int a, int b)
{
    return (a * b);
}

int calcul(int a , int b ,int (*ptr_f)(int a,int b))
{

    int result ;
    result = ptr_f(a,b);
    return result;
}


    int cunt = 0;
/*
int main()
{
    for(;cunt < 10;) 
    {
        cunt ++;
        printf("result of calcul ; %d\n",calcul(10,20,main));
    }
    return 0;
}
*/

int calculate(int a ,int b , int (**ptr_f)(int ,int ),int *result)
{

    for( ; *ptr_f ;ptr_f ++)
        *result ++ = (*ptr_f)(a,b);
}


int _calculate(int a ,int b , int (*(*ptr_f)[])(int ,int ),int *result)
{

    for(int iter = 0 ; (*ptr_f)[iter] ;iter ++ )
        *result ++ = (*((*ptr_f)[iter]))(a,b);
        //*result ++ = (((*ptr_f)[iter]))(a,b);
}


int main()
{
    int result[4] = {0};
    int (*ptr_f[])(int a,int b) = {sub,add,mult,NULL};

    //calculate(10,20,ptr_f,result);
    _calculate(10,20,&ptr_f,result);
    
    for(int iter = 0 ; iter < 4 ;iter++)
        printf("result[%d] = %d\n",iter, result[iter]);

}
