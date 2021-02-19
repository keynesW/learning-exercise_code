#include <stdio.h>

/*
int minner(int a ,int b );
double mutplate(double a ,double b );
double devide(double a ,double b );
int calculate(int*sub,double * mut,double *dev);
int calc(int ** ptr);


static int a = 4,b = 2;
static double c = 2.3 , d = 5 ;

int main()
{
    int sub = 0 ;
    double mut = 0 , dev = 0 ;

    int sub = 0 ;
    //int * ptr[3] = {NULL};
    int * ptr[3] = {&sub,&sub,&sub};
   ///////////////////////////////////////////
   // void * ptr[3] = {&sub,&sub,&sub};     //
   // arguement of void type pointer can    //
   // recive any pointer type               // 
   ///////////////////////////////////////////
   ptr[0] = &sub;
    int *(*ptr_a)[3] = &ptr;
    printf("%p\n%p\n%p\n",&ptr[0],&ptr[1],&ptr[2]);

    printf("minner : %d\n",minner(5,3));
    printf("mutplate :%f\n",mutplate(7.5,3));
    printf("devide : %f\n",devide(6.2,3));
   
    //calculate(&sub,&mut,&dev);
    calc(ptr);
    printf("sub = %d, mutplate = %f, devide = %f\n"\
       , sub,mut,dev);
    return 0;
}


int minner(int a ,int b )
{
    int result = 0 ;
    result = a - b ;
    return result;
}



double mutplate(double a ,double b )
{

    double result = 0 ;
    result = a*b ;
    return result;
}



double devide(double a ,double b )
{

    double result = 0 ;
    result = a / b ;
    return result;
}


int calculate(int*subb,double * mutt,double *devv)
{
//    extern int a , b ;
    extern double c , d;

    *subb = minner(a,b);
    *mutt = mutplate(c,d);
    *devv = devide(c,d);

    return 0;
}

int calc(int ** ptr)
{
    **ptr = minner(a,b);
    return 0 ;
}

*/

void swap(int * a, int * b );

int main()
{
    int a = 24, b = 25;

    swap(&a,&b);
    printf("a = %d, b = %d\n",a,b);
    printf("%d \n",1^1);
    return 0;
}

void swap(int * a, int * b )
{
/*
    *a += *b;
    *b = *a -*b;
    *a = *a -*b;
*/
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
    
}
