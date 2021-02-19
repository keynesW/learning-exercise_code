#include"stdio.h"
#include"stdlib.h"


//printf("%d,%d",'0',0);
    
int c = 0;
int d = 1;

int func(int a)
{
    a += 1;
    printf("\t\t  in func &a = %p\n",&a);
    return 0;
}
int main()
{
    int a = 0;
    int b = 0b01;
    int *ptr = NULL;
    b <<= 4; //  b<<4;
    printf("croll = %d \n",b);

    if(1)
            printf("first line\n");
    else 
            printf("third line\n");
            printf("fourth line\n");

    printf("——————————————————————————————\n");
    ptr = malloc(4); 
    printf("addr of:\n \
                 global c = %p\n \
                 global d = %p\n \
                 local  a = %p \n \
                 local  b = %p \n \
                 malloc(ptr) = %p \n",&c,&d,&a,&b,&ptr);
    func(a);

    printf("——————————————————————————————\n");
    printf("after assignment of ptr = %d\n",*ptr = 6);
    printf("before free ptr\n");
    printf("——————————————————————————————\n");

    free(ptr);  // after free ptr will point to data/bss section (global variable) 
    printf("after free ptr = %p\n",ptr);
    printf("*ptr = %d\n",*ptr);
    printf("assign after free ptr = %d\n",*ptr = 5);
    printf("——————————————————————————————\n");

    for (int iter_i = 0;iter_i < 6;iter_i++)
            printf("ptr[%d] = %d ",iter_i,ptr[iter_i]);
    printf("\n");

    printf("——————————————————————————————\n");
    int arry_t[] = {34,32,44,55};
    int *ptr_t = arry_t;
    printf("ptr_t reference to arry_t[3] = %d\n",ptr_t[3]);
    printf("ptr_t reference to *(arry_t+3) = %d\n",*(ptr_t+3));


    printf("——————————————————————————————\n");
    int arr[3][4] = {
            {1,3,4,5},
            {11,22,33,44},
            {123,345,123,113}
    };
    printf("in int arr[3][4]\n");
   // printf("a[3][3] =  %d\n",a[2][3]);
    printf("sizeof arr = %zd \n",sizeof arr);
    printf("&arr = %p\n",arr);
    printf("addr of arr = %p\naddr of &arr+1 = %p\n",&arr,&arr+1);
/
    printf("——————————————————————————————\n");
    char arry[5]="hello"; 
    char * ptr_s = "world";

    printf("in char arry[5]\n");
    printf("addr of ptr_s= %p\n",ptr_s);
    printf("addr of arry = %p\n",arry);
    printf("sizeof  arry = %zd\n",sizeof arry);
    printf("addr of (arry+1)%p\n",(arry+1));
    printf("addr of (&arry+1)%p\n",(&arry+1));
    printf("——————————————————————————————\n");
    printf("addr of ptr_s= %p\n",ptr_s);
    //*(ptr_s + 1) = 'h';    

    /////////////////////////////////////////////////////////////////////////////// 
    // string pointer char * ptr_s = "world"; initialized in this way            // 
    // the string will stored in static store area which user can not change;    //
    // char arry[5]="hello";                                                     //
    // arry[5] initialized in this way will get a copy of string to stack;       //
    //      **pointer been freed likely will point to const stored area          //
    //      **and can used to change things                                      //
    ///////////////////////////////////////////////////////////////////////////////


    printf("ptr_s after modify %s\n",ptr_s);
            
    printf("——————————————————————————————\n");
    char (*ptr_arry)[5] = &arry;

    printf("test of char (*ptr_arry)[5]\n");
    printf("addr of *ptr_arry %p\n",*ptr_arry);
    //*****************************//
            ptr_arry++ ;
    //*****************************//
    printf("addr of *ptr_arry %p\n",*ptr_arry);

    printf("——————————————————————————————\n");
    // ptr =(int *) 
    // &arry+1;
    char * ptr_a = NULL;

    printf("modify char arry[5]\n");
    ptr_a =(char *)(&arry+1);
    ptr_a--; 
    // if you modify the contains in the memery 
    // after the arry , system will find a stack smashing 
    *ptr_a = 'w';    
    *(ptr_a +1)='\0';
    printf("modified arry %s\n",arry);
    printf("after the char arry %d\n",*(ptr_a));//(ptr_a + 1)
    printf("——————————————————————————————\n");
    
    
    return 0;
}
//////////////////////////////////////////////////////////////////
//      int byte;                                               //
//      struct bit_struct *ptr_s = (struct bit_struct *)&byte;  //
//      now we can change bit of byte like bit_struct member    //
//                                                              //
//                                                              //
//    can not cast an selfbuild type object                     //
//    but can do this:    *(int *)& selfbuild_type              //  
//                                                              //
//      data &= ~(0xf << 12) ;                                  //
//      data |=  (0x9 << 12) ;                                  //
//////////////////////////////////////////////////////////////////



//      to cancel the struct aligent add this line 
//      after the declearation of the struct   :
//              __attribute__((packed));


////////////////////////////////////
//       core area;               //
//       stack area;              //
//       heap area;               //
//       static storage area;     //
//       data area;               //
//       code area;               //
//       reserved area;           //
////////////////////////////////////

//////////////////////////////////////////
//    printf("%d\n",5++);               //
//    ++/-- need an lvalue operands     //
//////////////////////////////////////////

/**************************************
 *     char arry[] | char *ptr        *
 **************************************/
/*
#include"stdio.h"

void print(char * ptr[]);
void strmodify(char * ptr);
int machine_code(int num);


int main ()
{
    int a = -11;

char * arry[] = {"hell", "uorllld","inthearry"};
char  arr[] = "nothing";
char * ptr = "test";
        printf("%p\n",arry);
        printf("sizeof arry = %zd\n",sizeof arry);
        printf("sizeof arry = %zd\n",sizeof (*arry[1]));
        printf("sizeof str = %zd\n",sizeof "hellower");
        printf("sizeof *ptr = %zd\n",sizeof ptr);
        printf("sizepf int %zd\n",sizeof (int));
        print(arry);
        strmodify(arr);
        strmodify(&arr[3]);
        strmodify(*arry);
        //strmodify(ptr);
//    machine_code(a);
    return 0;
}

void print(char * ptr[])
{
   for(int i = 0 ; i < 3; ++i) 
   {
         printf("%s\n",ptr[i]);
         printf("%p\n",&ptr[i]);
         printf("%p\n",ptr[i]);
   for(;*ptr[i]!= '\0';++ptr[i])
         printf("%c",*ptr[i]);
   printf("\n");
   }
}
void strmodify(char * ptr)
{
    if (*ptr != '\0')
           *ptr = 'a';
    printf("%s\n",ptr);

}

*/
//*********get the bit of byte in the memory***********//
/*
int machine_code(int num)
{
       char *ptr = (char *)&num;
       int iter_i = 0,sum = 0 ;
       for (;iter_i<4;++iter_i,ptr ++)
       {
            int i = 0 ,temp;
            unsigned char n = 1;
            for(i = 0,n = 1;i<8;i++)
            {   
                 temp = 0;
                 //temp = n & *ptr ;
                 //temp >>= i;
                 temp = (n & *ptr) >> i;
                 n <<= 1;
                 printf("%d",temp);
*/
         //********************************// 
                 ///*
  //                  sum = 10*sum + temp;
                 //*/
         //*******************************//

   //         }
     //     printf("\n");
      //      printf("sum for bit disp = %d",sum);   
         //********************************// 
      //              sum = 0;
         //********************************//
       //     printf("\n");
      // }
//}




//*************************************************************************//

/*****************************************************
 * a function to print the element of an Arry        *
 *****************************************************/

/*
#include"stdio.h"

int printArry(int cunt , int (*arr)[]);
int printArr(int cunt,int *arr);
int main ()
{
    int arry[5] = {11,22,33,44,55};
    int (*ptr)[5] = NULL;
    ptr = &arry;//not  prt = arry;
    printArry(5,ptr);
    printArr(5,arry);
return 0;
}

int printArry(int cunt , int (*arr)[])
{   
    int i = 0 ;
    for(;i<cunt;++i)
    {
        printf("arr[%d] = %d ",i,**arr);        
           
    }
    printf("\n");
    return 0;
}

int printArr(int cunt,int *arr)
{
    int i = 0;
    for (;i<cunt;++i)
    {
        printf("arr[%d] = %d ",i,*arr); 
    }
    printf("\n");
    return 0;
}




	printf("this is a test program\n");
	return 0;
}

*/

//**********************     muti demension arry      ***************************//


/* 
#include <stdio.h>

int func(int a[][4]);
int funcpp(int **a);
int funcp(int (*a)[4]);
int funcj(int (*a)[5][4]);

int main()
{

    int a[5][4] = {33,4}; 
    int (*ptr)[4] = a; 

    //   printf("&a = %p\n",a); printf("ptr = %p \n", ptr);
    //  printf("*(ptr+2) = %p \n", *(ptr + 2));
    // printf("*(ptr+2)+3 = %p \n", *(ptr + 2)+3);

    printf("ptr = %p,(ptr + 1) =%p \n",ptr,(ptr+1));
    printf("&ptr = %p,&(ptr + 1) =%p \n",&ptr,(ptr++));
    ++ptr;
    printf("%p\n",&ptr);
    //  ++a;
    printf("& a= %p,& a[1]=%p \n",a,a[1]);
    printf("& a= %p,& a[1]=%p \n",a,&a[1]);
    //for a[5][4] the address of a[1] and  &a[1] are equal;
*/


/*
* ********************************************************************
*       a[1] ==> means the address of a[1][0]                        *
*       the type of a[1] is int *                                    *
*       a and &a[0] means the address of a[0]                        *
*       the type of a is &a[0] ==> int (*)[4]                        *
*                                                                    *
*   the arry name will be a pointer which point to it's element      *
*   get the address of an arry name means a type of pointer which    *
*   point to an arry                                                 *
**********************************************************************
*/

////////////////////////////////////////////////////////////////////////////////
//    char *arry[10];                                                         //
//    the element of arry are pointers which point to a char                  //
//                                                                            //
//    the name  arry  means the pointer point to it's element                 //
//                                                                            //
//    so the type of neme  arry will  be a pointer point to a char_pointer    //
////////////////////////////////////////////////////////////////////////////////

/*
    int sub = 0 ;
    //int * ptr[3] = {NULL};
    int * ptr[3] = {&sub,&sub,&sub};
    void * ptr[3] = {&sub,&sub,&sub};
    ptr[0] = &sub;

    ********************************************
    ***     int *(*ptr_a)[3] = &ptr;         ***
    ********************************************

    printf("%p\n%p\n%p\n",&ptr[0],&ptr[1],&ptr[2]);

*/


/*
    int *ptr_r = NULL;
    ptr_r = a[1];
    // printf("a[1] = %d\n",a[1]);
    // printf("a[1] = %d\n",a);
    // printf("a[1] = %d\n",&a[1]);
   
       func(a);
       funcp(a);
       funcpp(&a[5]);
    funcj(&a);
  
    return 0;
}
int funcpp(int **a)
{
    printf(" a[0][1] = %d \n",a[0][1]);
    printf(" &a = %p \n",a);
    printf(" &a = %p \n",a+1);
}

int func(int a[][4])// int func( int (*a) [4])
{

        printf(" a[0][1] = %d \n",a[0][1]);
        printf(" &a = %p \n",a);
        printf(" &a = %p \n",a+1);
}

int funcp(int (*a)[4] )
{

        printf(" a[0][1] = %d \n",a[0][1]);
        printf(" &a = %p \n",a);
        printf(" &a = %p \n",a+1);

}
int funcj(int (*a)[5][4])
{

        printf(" a[0][1] = %d \n",(*a)[0][1]);
        printf(" a[0][1] = %d \n",a[0][0][1]);
        printf(" &a = %p \n",a);
        printf(" &a = %p \n",a+1);

}
*/

/*
    int i=5;
    while(i<10)
    {
        ++i;
        printf("i = %d ",i);
    
    }
    printf("\n");
    i = 0 ;
    do{
        ++i;
        printf("i = %d ",i);
    
    }while(i<10); 
*/

//******************   in/output the element of an arry  ******************//

/*
#include<stdio.h>

int input_arry(int * ptr_a , int size);
void output_arry(int *ptr_a,int size);

int main()
{
//  int iter = 0; 
    int arry[8] = {0};
//  int* ptr = &arry[0];
//
   for(;iter < 4; iter++)
   //     ptr[iter] = iter;
   //   *(ptr + iter) = iter;

   {
       // *ptr = iter;
       //ptr ++;
        *ptr++ = iter;
   }
//
   for(iter = 0;iter < 4; iter++)
        printf("arry[%d] = %d ",iter,arry[iter]);

   int cunt = 0;
   cunt = input_arry(arry,sizeof arry /sizeof arry[0]);
   printf("cunt = %d\n",cunt);

   output_arry(arry,sizeof arry /sizeof arry[0]);
    return 0 ;

}

int input_arry(int * ptr_a , int size)
{
    int cunt = 0;
    printf("please input 4 numbers :\n");
    for(int iter = 0 ; iter < size ; iter++)
    {
        if(scanf("%d",&ptr_a[iter]))
                cunt++;
        printf("iter = %d\n",iter);
    }

    //////////////////////////////////////////////////////////
    //                 scanf("%d",addr);                    //
    // if scanf encounter an element that's not an integer  //
    // it will leave the element in the input buffer which  //
    // will make the cyclic continue with read failer then  //
    // the iter will ++ until the cyclic end                //
    //////////////////////////////////////////////////////////
    
    return cunt;
}

void output_arry(int *ptr_a,int size)
{

    for(int iter = 0 ; iter < size ; iter++)
        printf("arry[%d] = %d\n",iter,ptr_a[iter]);
}
*/
