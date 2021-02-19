#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
typedef  int int_32_t;
typedef  int * int_ptr;
typedef  int arry5[5];
typedef  int func(int , int);
typedef  int (*func_ptr)(int,int);

//int add(int a ,int b);
func add;
int main()
{
    int_32_t  a = 10 ;
    int_ptr ptr_int = &a;
    arry5  arry = {0};
    func *func_pf; // typedef will add () for the content to replace
    func_ptr add_ptr;

    func_pf = add;
    add_ptr = add;

   printf("add %d\n", add(a,a));
   printf("*ptr_int %d\n", *ptr_int);
   printf("fucn_pf %d\n" , func_pf(a,a));
   printf("add_ptr %d\n",add_ptr(a,a));
    



    return 0;

}
int add(int a ,int b)
{

    return (a + b);

}
*/


struct student {
            char name[20] ;
            int age ;
            int high;
            };

void scan_stud(struct student * stu);
void print_stud(struct student * stu);

struct tst {
    double doub;
    char chr;
    short shr;
    };

struct tt{
    short  c;
    char   a;
    double e;
    int    b;
};

union unin{
       int   a ;
       char  b ;
       short c ;
    };

struct bit_str{

        unsigned int bit_fd3 :8;
        unsigned int bit_fd1:2;
        unsigned int bit_fd2:10;
        unsigned int bit_fd:8;
        unsigned int bit_fd4:3;

    };


enum color {

    red,
    green =3,
    blue,

};

void show_color(enum color a);


#define DATA  (8-3) 
#define MIN(x,y)  ((x) < (y) ?  (x): (y))

int main() 
{

    int  a = 2,b = 3; 
#ifdef DEBUG 
    printf("mcro debug\n"); 
#elif LINUX
    printf("mcro linux\n"); 
#else
    printf("no mcro\n"); 
#endif




    struct student stu[3] = {{"neanreraererdfaf",12,12}};

/*
    for(int iter = 0 ;iter < sizeof stu/ sizeof stu[0];iter ++)
    {
        scan_stud(stu);
        print_stud(stu);
    }
*/ 
    struct tst tet;
    struct tt tt1;
//    printf("sizeof student %zd\n",sizeof tet);

    printf("sizeof student %zd\n",sizeof tt1);
    printf("address of tt1.c %p\n",&tt1.c);
    printf("address of tt1.e %p\n",&tt1.e);
    printf("address of tt1.b %p\n",&tt1.b);
    printf("%s\n",&stu[0].name[10]);

//
//      int byte;
//      struct bit_struct *ptr_s = (struct bit_struct *)&byte;
//      now we can change bit of byte like bit_struct member 
//
//      to cancel the struct aligent add this line 
//      after the declearation of the struct   :
//              __attribute__((packed));
//
//    can not cast an selfbuild type object
//    but can do this:    *(int *)& selfbuild_type
//
//      data &= ~(0xf << 12) ;
//      data |=  (0x9 << 12) ;
//

    union unin tst_unin;
    tst_unin.a = 0x12345678;
    if(&tst_unin.a == (int*)&tst_unin.b)
        tst_unin.b = 0x11;
    else
        tst_unin.b = 0x22;

    printf("%#x\n",tst_unin.a);
    
    
    struct bit_str bit_area;
    printf("%p\n",&bit_area);
    bit_area.bit_fd3 = 67;
//    pritnf("%p\n",&bit_area.bit_fd);
//    pritnf("%p\n",&bit_area.bit_fd1);
    char *ptr_c = (char *) &bit_area;
    printf("in bit_area %c\n",*ptr_c);


    enum color color_a = 4 ;
/*    
    printf("address of red %p\n",&red);
    printf("address of green %p\n",&green);
    printf("address of blue %p\n",&blue);
*/
    show_color(++color_a);
    printf("color of a %d\n",color_a);
    printf("address of color_a %p\n",&color_a);
    printf("red :%d,green :%d,blue :%d\n",red,green,blue);


    return 0 ;    
}

void show_color(enum color a)
{
    switch (a){
       
    case red:
        printf("a is red.\n");
        break;
    case green:
        printf("a is green.\n");
        break;
    case blue:
        printf("a is blue.\n");
        break;
    default :
        printf("a is black.\n");

    }
}


void scan_stud(struct student * stu)
{
//    char arry[20] = {'\0'};
    printf("please enter your name :\n");
    scanf("%s",stu->name);
//    scanf("%s",arry);
//    strcpy(stu->name,arry);
    
    printf("please enter your age :\n");
    scanf("%d",&stu->age);

    printf("please enter your hight :\n");
    scanf("%d",&stu->high);

}

void print_stud(struct student * stu)
{

    printf("hello        :%s\n",stu->name);
    printf("your age  is :%d\n",stu->age);
    printf("your high is :%d\n",stu->high);

}
