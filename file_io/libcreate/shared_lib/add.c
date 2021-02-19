#include "add.h"

//
//
//  #include "add.h" in this file ( add.c )is not used to declearation the fucntion head
//  the extern function and varable declearation in add.h are used for other files to reference
//  
//  in this file (add.c) 
//  add.h is used to include 
//          macro defines which defined in add.h 
//          and other head files used by add.c which include in add.h 
//
//

//extern int add(int a,int b);
//extern int mul(int a,int b);

#include "sub.h"

char char_arry[100] = {'\0'};

int add(int a , int b)
{
    return (a+b);
}

int mul(int a , int b)
{
    return (a*b);
}

int sub_mul(int a , int b)
{

    return  sub(a,mul(a,b));

}
