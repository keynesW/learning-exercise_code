#include"stdio.h"
#include"string.h"
#include"stdlib.h"
#include"ctype.h"
int main()
{
//***************************************//
/*
	puts("please input string");
	char str[127];
	gets(str);
	printf("%s",str);

	int r=0;
	r = printf("hello\n");
	printf("r = %d \n",r);

	int n = 0;
	r = scanf("%d",&n);
	printf("r = %d \n",r);

	r = putchar('a');
	putchar('\n');
	printf("r = %d\n",r);

	r = getchar();
	printf("r = %d \n",r);

	r = isalpha('a');
	printf("r = %c \n",r );

	r = tolower('A');
	printf("r = %d \n",r);

	r = toupper('a');
	printf("r = %d \n",r);

	r = isdigit('b');
	printf("r = %di\n",r); 
	unsigned int r = 0;
	r = strlen("hello");
	printf("r =  %d\n",r);
	
	char dest[128]={0};
	strcpy(dest,"hello");
	printf("%s\n",dest);
*/
//*****************************************//	
/*
	char *pch =NULL;
	pch = strchr("hello","world");
	if(pch == NULL)
	{
		printf("no chr \n");	
	}else{
	
		printf("char : %c\n",*pch);	
	}
	pch = strstr("hello world","hua");
//	printf("%s\n",pch);
	int dest[10]={2,5};
	int tst[3] = {6,8,2};	
	memset(&dest[3],'\0',3);
	printf("%d\n",dest[0]);	
	memcpy(&dest[4],tst,1);
*/
//***********************************************//
/*
	int r =1; 
	r = strcmp("world\0a","world\0b");
	printf("%d\n",r);
	printf("%d\n",r); 
	r = memcmp("world\0a","world\0b",7);
	printf("%d\n",r);
	{
		printf("before exit\n");	
	//	exit(1);
		printf("after exit\n");
	}
*/
//**********************************************//
/*
    int i = 3;
	i = atoi("234");
	printf("this is i = %d\n",i);
*/
//*********************************************//
/*
	printf("sizeof 'a' = %zd\n",sizeof ('a'));
	printf("sizeof 'a' = %zd\n",sizeof (short));
	printf("sizeof 'a' = %zd\n",sizeof (int));
	printf("sizeof 'a' = %zd\n",sizeof (float));
	printf("sizeof 'a' = %zd\n",sizeof (double));
	
	printf("sizeof U = %zd\n",sizeof (21744836U));
	printf("sizeof F = %zd\n",sizeof (3.14F));
	printf("sizeof L = %zd\n",sizeof (3.14L));
	printf("sizeof e = %zd\n",sizeof (3.14e5));

	printf("ASCII of a %d\n",'a');
	
	printf("ASCII of A %d\n",'A');	

	printf("ASCII of space %d\n",' ');	
	printf("ASCII of NULL %d\n",'\0');	
	printf("ASCII of space %d\n",' ');	
	printf("ASCII of  %d\n",'0');

	printf("%d\n",'\a');
*/
//************************************************//
/*
    char ch = 0 ;
    ch  = 'a';
    printf("%d\n",ch);

    ch = '\x61';
    printf("%d\n",ch);
    
    ch = '\141';
    printf("%d\n",ch);
    
    ch = '\n';
    printf("%d\n",ch);
    
    ch = '\xa';
    printf("%d\n",ch);

    ch = '\12';
    printf("%d\n",ch);
*/
//******************************************************//
/*

        printf("%u\n",2222222222U);
        printf("%ld\n",2222222222);
        printf("%u\n",2222222222U);

        printf("d : %d\n",123);
        printf("o : %o\n",123);
        printf("x : %x\n",123);

        printf("f : %f \n",32.5);
        printf("e : %e \n",32.5);
        printf("g : %g \n",32.5);
        printf(" %i\n ",-87); 
        printf("%%\n");
        printf(" %a \n",(double)0x1f); int tst = 2323;
        printf("%-3.d\n",tst);
*/
//*****************************************************//

 //   char ch = 'a' ;
/*
    ch = getchar();
    putchar(ch);
    putchar('\n');
*/
/*
    char  chrs[23] = {0};
    gets(chrs);
    puts(chrs);
    printf("strlen = %zd\n",strlen(chrs));
    strcpy(&chrs[3],"hello");
    printf("in chrs %s\n",chrs);

    memset(chrs,ch,4);
    printf("in chrs %s\n",chrs);
    printf("atoi %d \n",atoi("14dfa42")); 
//    fgets(chrs);
   // fputs(chrs);

    
//    printf("%s\n",chrs);
*/
//***********************************************//
/*
    char a = 0;
    a = getchar();
    putchar(a);
    putchar('\n');
    a = isalpha(a);
    printf("sizeof a  = %zd \n",sizeof a);
*/
//    printf("%d",\b1011); 
//***************************************************//
/*
    int n = 123;
    printf("%d \n",n);
    printf("%6d\n",n);
    printf("%06d\n",n);
    printf("%+6d\n",n);
    printf("%-6d\n",n);
    printf("%2.9d\n",n);
    printf("%.2d \n",n);

    double d = 23.234;
    printf("%f\n",d); 
    printf("%4.5f\n",d);    
    printf("%6.5f\n",d); 
    printf("%.2f\n",d); 
    printf("%+5.2f\n",d);
*/
/* 
    printf("please enter an integer\n");
    scanf("%d",n);
    printf("%d\n",n);
*/
/*
    printf("enter [abc]\n");
    char str1[128]={0};
    scanf("%[abc]",str1);
    printf("str : %s\n",str1); 
    //scanf("%[^\n]",str1);
    //[^\n] means any str and \n
    //printf("str : %s\n",str1);

    const char * str = "hello";
    printf("s : %s \n",str);
    printf("s : %s \n",str);
    printf("s : %s \n",str);
*/
//******************************************//
/* 
    //getchar();
    //getchar();
    //getchar();
    printf("-----------------------\n");
    int num1 = 0;
//  scanf("%*c");
//  scanf("%*c");
//  scanf("%*c");
// get a char from stream buffer and not save
*/
    
/********************************************
*  every program has three standard file    * 
*  stdin  stdout stderrr                    *
*********************************************/
/*
    scanf("%*[^\n]%*c");
    // clear stream buffer
    scanf("%3d",&num1);//
    printf("%d\n",num1);
    
#define MIN(x,y) x>y? y:x
    printf("%d\n",MIN(5,8));
    num1 = 4 > 5? 5 : 8 ; 
    printf("%d\n",num1);
    
    num1 = 97;
    printf("%d\n",-num1++);
*/
//*********************************************//
/*
    printf("%c\n","hello"[3]);

    int anum = 123;
    printf("a = %d \n",anum);

    int * ptr = malloc(4);
    printf("*p = %d\n",*ptr);
    *ptr = 345;
    printf("*ptr = %d\n",*ptr);

    free(ptr);
*/ 
//**********************************************//
/*
    void func(int au )
    {
        au += 1;
        printf(" a = %d \n",au );
     }

    void func_g(int *ptr)
     {
         *ptr +=1;
         printf("*ptr = %d\n",*ptr);
       
     }
    void fout(int *ptr,int *ptr1)
     {
          *ptr += 1;
          *ptr1 +=1; 
     }
*/
//*******************************************//
/*
    int nu = 1;
    func(nu);
    printf("n = %d \n",nu);
    
    func_g(&nu);
    printf("n = %d \n",nu);
    fout(&nu,&nu); 
*/
//******************************************//
    char arr[] = "world";
    int arry[3][4]={
            {11,12,13,14},
            {22,23,24,25},
            {33,34,35,35},
            };
    int *ptr_arry = arry[0];
    int i = 0 ,j = 0;


    unsigned int a = 6;
    int b = -20;

    printf("testafada %d\n",((a+b)>6));

    printf("sizeof 0.0 = %ld\n",sizeof 0.0);

    float float_x = 0.0;
    printf("float_x = %f\n",float_x); 
    for(;i<3;++i){
        for(j=0;j<4;++j){
            printf("arry[%d][%d]=%d  ",i,j,*(ptr_arry+i*4+j)); 
        } 
            printf("\n");
    }

    char *ptr_tst = NULL;
    ptr_tst = arr;
    if(ptr_tst)
        printf("this is the test\n");
    printf("strlen %ld\n",strlen(arr));
    printf("strlen %ld\n",strlen("hello"));
    return 0;	
}

//************** ++ and * ********************//
/*
 
#include <stdio.h>


int main()
{

    unsigned char a , *ptr;
    unsigned int x = 0x12345678;

    ptr = (unsigned char *)&x;
    printf(" ptr  value  ; %p",ptr);

    //printf("%d\n",5++);

    a = *ptr++;
    printf(" ptr  value  ; %p\n",ptr);
    printf(" a    value  : %#x\n", a);
    printf(" x    value  : %#x\n",x);

    a = ++*ptr;
    printf(" ptr  value  ; %p\n",ptr);
    printf(" a    value  : %#x\n", a);
    printf(" x    value  : %#x\n",x);

    a = *++ptr;
    printf(" ptr  value  ; %p\n",ptr);
    printf(" a    value  : %#x\n", a);
    printf(" x    value  : %#x\n",x);

    a = (*ptr)++;
    printf(" ptr  value  ; %p\n",ptr);
    printf(" a    value  : %#x\n", a);
    printf(" x    value  : %#x\n",x);

}
*/
