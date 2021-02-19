#include <stdio.h>


long char_store();
long char2num(unsigned char *ptr_a,int size);
int add_arrbyte(void * ptr_c,int size);
unsigned int find_max_comm_factor(unsigned int m,unsigned int n);

int main()
{
//*****************************  1  ********************************//
    long sum = 0;

    printf("char you input turn to num is  %ld\n",char_store());

//*****************************  2  ********************************//
    
    //char *ptr = "inte";
    //char **ptr = NULL;
    //ptr = &"inte";
    
    unsigned char a[] = {0x11,0x22,0x33,0x44,'a','b','1','2',10,11};
    printf("adress of str %p\n","str") ;   
    add_arrbyte(a,sizeof a / sizeof a[0]);
    return 0;

}




long char2num(unsigned char *ptr_a, int size)
{
    long sum = 0;
    for(int iter = 0 ; iter < size ;  iter ++)
    
        if( ptr_a[iter] >= '0' && ptr_a[iter] <= '9')
            sum = 10*sum + ptr_a[iter] - 48;

    return sum;
}

long char_store()
{
    int cunt = 0 ;
    char arry[10] = {0};
    while(cunt < 10)
    {
        char temp = '\0';
        temp = getchar(); 

        if (temp  == '\n') 
            break;

        if( temp >= '0' && temp <= '9' )
//        if(temp != ' ')
        {
            arry[cunt] = temp;
//            printf("arry[%d] = %c  ",cunt,arry[cunt]);
//            printf("arry[%d] = %d  ",cunt,arry[cunt]-48);
            cunt++;
        }
    
    }

   return char2num(arry,cunt);

}

//************************************************************//

int add_arrbyte(void * ptr,int size)
{
    unsigned short *ptr_c = (unsigned short *)ptr;
    int sum = 0 ;

    for(int iter = 0; iter < size/2 ; iter ++)
        sum += ptr_c[iter] ;

    if(1 == size % 2 )
        sum = sum + ((char *)ptr_c)[size-1];
    printf("sum = %#x\n",sum);
    return sum;
}

unsigned int find_max_comm_factor(unsigned int m,unsigned int n)
{
    int ret = n;

    for( ; m%n ; ret = m%n,m=n,n=ret)
                ;
    return ret;
    //    int temp;    //    m > n ?    : (temp = m,m = n, n = temp);    //    printf("m = %d   n = %d\n",m ,n);
    //       while( m%n )       {       ret = m %n;       m = n;       n = ret;       }
}
