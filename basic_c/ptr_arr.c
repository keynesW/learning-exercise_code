#include <stdio.h>


const char * get_max_str(char ** ptr_c_a,int size );
const char * str_cmp(const char * ptr_t,const char *ptr_s);
void get_min_str(char ** ptr_c_a,const char **ptr_ret,int size );
const char * str_cmmp(const char * ptr_t,const char *ptr_s);



int main()
{
    char * ptr_c_arry[] = {"aa","abc","ab","abcd","abce","abc"};

    int (*ptr_f)(int,double) = &main;

    printf("%s\n", get_max_str(ptr_c_arry,6));

    printf("addr of main ; %p\n",*main);
    printf("addr of main ; %p\n",main);
    printf("addr of main ; %p\n",&main);
    
    printf("-----------------------\n");   

//    ptr_f(24,2.4);
   
////////////////////////////////////////////////////////////////////

    char *ptr_ret = NULL;

    get_min_str(ptr_c_arry,(const char **)&ptr_ret,6 );
//    printf("min str addr is %p\n",ptr_ret);
    printf("min str is %s\n",ptr_ret);

    return 0;
}


///////////////////////////////////////////////////////////////////
const char * get_max_str(char ** ptr_c_a,int size )
{
  const  char *ptr_max = *ptr_c_a; 
   
    for(int iter = 0;iter<size -1 ;iter++) 
        ptr_max =  str_cmp(ptr_max,ptr_c_a[iter + 1]);

    return ptr_max;
}

const char * str_cmp(const char * ptr_t,const char *ptr_s)
{
    const char *ptr_t_h = ptr_t;
    const char *ptr_s_h = ptr_s;
    for(;*ptr_t == *ptr_s && *ptr_s;ptr_t++,ptr_s++)
                ;
    if(*ptr_t > *ptr_s)
        return ptr_t_h;
    else if(*ptr_t<*ptr_s)
        return ptr_s_h;
    return ptr_s_h;
}

//////////////////////////////////////////////////////////////////
//
void  get_min_str(char ** ptr_c_a,const char **ptr_min,int size )
{
    *ptr_min = *ptr_c_a; 
   
    for(int iter = 0;iter<size -1 ;iter++) 
        *ptr_min =  str_cmmp(*ptr_min,ptr_c_a[iter + 1]); 

}

const char * str_cmmp(const char * ptr_t,const char *ptr_s)
{

    const char *ptr_t_h = ptr_t;
    const char *ptr_s_h = ptr_s;
    for(;*ptr_t == *ptr_s && *ptr_s;ptr_t++,ptr_s++)
                ;

    if(*ptr_t > *ptr_s)
        return ptr_s_h;
    else if(*ptr_t<*ptr_s)
        return ptr_t_h;
    return ptr_s_h;
}


