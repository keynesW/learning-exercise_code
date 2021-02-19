#include<stdio.h>
#include <assert.h>

int strleng(char *ptr);
char * strcopy(char *ptr_t, const char *ptr_s);
char * str_cpy(char *ptr_t, const char *ptr_s ,int n);
char * str_lcpy(char *ptr_t, const char *ptr_s,size_t n);
char * strcatt(char *ptr_t, const char *ptr_s);
int strcmpp(const char *ptr_t, const char *ptr_s);
int atoii(const char *ptr);
int sortt(int *ptr,int cunt);
int sortt(int *ptr,int cunt);
void str_del_chr(char *ptr_s,const char val);
void str_delet_chr(char *ptr_s,const char val);
int chr_in_str(const char chr,const char *ptr_s);
void str_del_chrs(char *ptr_t,const char *ptr_s);

int main ()
{
    int arry[] = {4,36,7,2,8};
    char ptr_c[] = "ABCDAldfAfdAbc";
    printf("str in ptr_c      : \n%s\n",ptr_c);

    int *ptr ;
    //printf("%d\n",' ');
    printf("strlen of ptr_c : %d\n",strleng(ptr_c));
    char ptr_d[] = "areaee234dfe";
    printf("str in ptr_d      : \n%s\n",ptr_d);

    printf("------------------------------------\n");
//    str_cpy(ptr_c,ptr_d,3);

    //str_lcpy(ptr_c,ptr_d,4);
    printf("after copy ptr_c  : \n%s\n",ptr_c);
    str_del_chrs(ptr_c,"Ab");
    printf("after copy ptr_c  : \n%s\n",ptr_c);
    printf("------------------------------------\n");

//   int i ;
//    atoii(ptr_d); 
/*
    sortt(arry,5);
    for(;i<5;++i)
    {
            printf("%d",arry[i]); 
    }
*/
//    strcopy(ptr_c,ptr_d);
//    strcatt(ptr_c,ptr_d);
//    printf("ptr_c %s\n",ptr_c);

    // str_del_chr(ptr_c,'A');
    
    str_delet_chr(ptr_c,'a');
    printf("after delete char in ptr_c :\n%s\n",ptr_c);

    printf("------------------------------------\n");

    printf("result of strcmp : %d\n",strcmpp(ptr_d,ptr_c));
    printf("result of strcmp : %d\n",strcmpp(ptr_c,ptr_d));
//    printf("strcmpp = %d\n",strcmpp(ptr_c,ptr_d));

    return 0;
}

int strleng(char *ptr)
{
/*
    for(;(*ptr>65&&*ptr<90)||(*ptr>97&&*ptr<108);cunt++)
           ++ptr;
*/
/*
    int cunt = 0 ;

    for(;*ptr != '\0'; ++ptr,cunt++)
                ;
    printf("%d\n",cunt);
    
    return cunt;
*/
//////////////////////////////////////////////////

    const char *ptr_m = ptr;

    for(;*ptr != '\0'; ++ptr)
                ;
    return ptr - ptr_m;

}


//******************************************************//

char * strcopy(char *ptr_t,const char *ptr_s)
{   
    char * ptr_t_h = ptr_t;

    if(ptr_t == NULL || ptr_s == NULL) 
        return NULL;

    for(;*ptr_s!='\0';++ptr_s,++ptr_t)  
    {
        *ptr_t = *ptr_s; 
        //++ptr_t;
    }
    *ptr_t = '\0';

    return ptr_t_h;
}

char * str_cpy(char * ptr_t, const char * ptr_s ,int n)
{
    char * ptr_t_h = ptr_t;
    int iter = 1;

    assert(ptr_t != NULL || ptr_s != NULL);

    while((*ptr_t ++ = *ptr_s ++ ) && (iter < n))
                iter++ ;

    return ptr_t_h;
}

char * str_lcpy(char *ptr_t, const char * ptr_s,size_t size)
{
        char *ptr_t_h = ptr_t;
        const char * ptr_s_h = ptr_s;
        int iter = 1,cunt= 0 ;

        assert(ptr_t != NULL || ptr_s != NULL);

        for( ; *ptr_s ;cunt++,ptr_s ++)
                    ;

        size = ( cunt > size ?   size :  cunt ) ;
        ptr_s = ptr_s_h;

        while((*ptr_t ++ = *ptr_s ++ ) && (iter < size))
                         iter++ ;
        
        ptr_t_h[iter] = '\0';

        return ptr_t_h;

}



//************************************************************//

void str_del_chr(char * ptr_t,const char val)
{
    for( ; *ptr_t ;ptr_t++ ) 
        if(*ptr_t == val )
        {
            strcopy(ptr_t,&ptr_t[1]);     
        }
}

//////////////////////////////////////////////////////////////

void str_delet_chr(char * ptr_t,const char val)
{

    char *ptr_new = ptr_t;
    for( ; *ptr_t ;ptr_t ++ , ptr_new ++)
    {
        if(*ptr_t == val)
             ptr_t ++ ;

        *ptr_new = *ptr_t;

    }
    *ptr_new = '\0' ;
}

//////////////////////////////////////////////////////////////

int chr_in_str(const char chr,const char *ptr_s)
{
    for( ; *ptr_s ;ptr_s ++)
        if(chr == *ptr_s)
            return 1;
        return 0;
}



void str_del_chrs(char *ptr_t,const char *ptr_s)
{
    char *ptr_res = ptr_t;
    for( ; *ptr_t;ptr_t++,ptr_res++)
    {
        if(chr_in_str(*ptr_t,ptr_s)) 
                    ptr_t++;
        *ptr_res = *ptr_t;
    }
    *ptr_res = '\0';

}

//**************************************************//
char * strcatt(char * ptr_t,const char *ptr_s)
{

    for (;*ptr_t!='\0';++ptr_t)
          ;

//   if(*ptr_t != '\0')
//         ++ptr_t; 
    for(;*ptr_s!='\0';++ptr_s)
    {
        *ptr_t  = *ptr_s;
        ++ptr_t;
    }
    *ptr_t = '\0';

    return ptr_t; 
}

int strcmpp(const char *ptr_t,const char *ptr_s)
{
    /*
    for(  ; (*ptr_t == *ptr_s)
                    &&((*ptr_s !='\0')
                    &&(*ptr_t != '\0')) ; ++ptr_s , ++ptr_t)                     
                        ;
       {
            if(*ptr_s < *ptr_t)
                    return  -1;
            else 
                    if (*ptr_s > *ptr_t)
                            return 1;
                    else
                            return 0;
       }
*/
       for(  ; *ptr_t && *ptr_s && *ptr_t == *ptr_s ; 
                                    ptr_t ++ , ptr_s ++)
                            ;

       return (*ptr_t - *ptr_s);

}

int atoii(const char * ptr)
{
/*
    int cunt = 0 ,sum =0,i= 0;
    for(;(*ptr != '\0');++ptr)
      {

        if((*ptr>='0')&&(*ptr <='9'))
            {
//                 printf("%c\n",*ptr);
                 i=*ptr-48;//i = ptr - '0';
                 printf("%d\n",i);
                 sum =sum*10+i;
                 printf("%d\n",sum);
                 //sum *=10;
                 ++cunt; 
            }
      }
    printf("\ncunt = %d\n",cunt);
*/
//**************************************************//

    int sum = 0;
    for(;*ptr != '\0'&& *ptr > '0' && *ptr<'9';++ptr )
    {
            sum =10*sum + *ptr - '0'; 
    }    
    printf("atoi = %d\n",sum);
    return sum;
}

//******************************************************************//

int sortt(int *ptr,int cunt)
{
/*
    int iter_i = 0,iter_j= 0 ,temp;
  for(;iter_i<cunt;++iter_i) 
  {
        for(iter_j = 0;iter_j < cunt - iter_j - 1 ;++iter_j)//use cunt -1 or there is an bug of out of the boundary of arry;
        {
            if(ptr[iter_j]>ptr[iter_j+1] )  
            {
                    temp = ptr[iter_j] ;
                    ptr[iter_j] = ptr[iter_j+1];
                    ptr[iter_j+1] = temp;
            }      
        }    
  }
*/
//***************************************************//

        int iter_i = 0, iter_j = 0, temp = 0;
        for(;iter_i<cunt;++iter_i)
        {
            for(iter_j = iter_i + 1 ;iter_j < cunt; ++iter_j) 
            {
                    if (ptr[iter_i]<ptr[iter_j])
                    {
                        temp = ptr[iter_i];
                        ptr[iter_i] = ptr[iter_j];
                        ptr[iter_j] = temp;
                    }    
            }
        
        
        }


}


//******three types of methord to swap to data********//
int swap(int *a, int *b)
{
    int temp = 0;
    temp = *a;
    *a = *b;
    *b = temp;
/*
    *a += *b;
    *b = *a -*b;
    *a = *a -*b;
////////////////////////
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
*/
    return 0; 
}

