#include "stack_lk_list.h"
#include "list_quene.h"
#include <stdio.h>


#define IS_NUM(iter)  ( (iter) >= '0' && (iter) <= '9')
 // * 42  |  + 43   | -  45  |   / 47 |
#define IS_SYMBAL(iter)  ( (iter) == 42 || (iter) == 43||\
     (iter) == 45|| (iter) == 47 ||(iter == 40) || (iter) == 41  )

char * get_input();
char * skip_space(char *s);
int get_operator_priority(data_t operator);
data_t pri_operator_pop_stack( list_quene_mk_st *num_quene,\
                                lk_stk_head *plk_stk_head , data_t oper);
char * convert2suffix( list_quene_mk_st * num_quene,\
                        lk_stk_head *plk_stk_head , char *s );

//char * convert2expression(char *s);


int main()
{
    char s[50] = {'a','b',' ',' ','c','\0'};
    get_input(s);
    skip_space(s);
    printf("%s\n",s);


printf("------------convert2suffix---------------\n");

    list_quene_mk_st * num_quene = NULL;
    list_quene_Init( &num_quene ); 

    lk_stk_head * plk_stk_head = lk_stk_head_Init( );

    convert2suffix( num_quene, plk_stk_head , s );
    print_quene(num_quene);

//    convert2expression(s);

printf("------------calculating---------------\n");
    /*
    for(int i=0; i < sizeof s -1; i++)
        printf("%c ",s[i]);
    printf("end of s\n");
    */
    return 0;
}

char * get_input(char *s)
{
    char cond = '\0'; 
    int i = 0;

    printf("please enter an expression to calculate :\n");

    while((s[i] = getchar())!= '\n')
    {
        i ++;
    }
    //printf("%s\n",s);
}

char * skip_space(char *s)
{
    char * iter = s;
    char * res = s;

    for(  ; *iter != '\0'  ; iter++)
    {
        if( *iter != 32 )
        {
            *res = *iter;
            res ++;
        }
    }
    *(--res) = '\0';
    return res;
}

char * convert2expression(char *s)
{
    char * iter = s;
    for( ;*iter  ;iter ++)
    {
        if(IS_NUM(*iter))
        { 
            *iter -= '0';
            printf("%d",*iter);
           }
//  ( 40 |  )   41 | * 42  |  + 43   | -  45  |   / 47 |
        if(IS_SYMBAL(*iter))  
        {
            printf("%c",*iter);
        }
    }
    putchar('\n'); 
    return s;
}


char * convert2suffix(list_quene_mk_st * num_quene,\
                        lk_stk_head *plk_stk_head,char *s)
{
        char * iter = s;
        for(  ; *iter ; iter ++)
        {

            if(IS_NUM(*iter))
            {
                add2_list_quene(num_quene,*iter);
            }
            if( IS_SYMBAL(*iter))
            {
                //  ( 40 |  )   41 | * 42  |  + 43   | -  45  |   / 47 |

                if( IS_STACK_EMPTY(plk_stk_head) )
                    push_stack(plk_stk_head,*iter);
                else
                {
                    //priority of opreator in iter is lowwer
                    //than the opeartor in the top of the stack 
                    
                    pri_operator_pop_stack( num_quene, plk_stk_head ,*iter );

                }
            }

        }
}

data_t pri_operator_pop_stack( list_quene_mk_st *num_quene,\
                                lk_stk_head *plk_stk_head , data_t oper)
{
    //if( oper < GET_TOP_ELEM(plk_stk_head))

    if( get_operator_priority( oper ) < get_operator_priority(\
            GET_TOP_ELEM(plk_stk_head)) )
    {
        data_t top_oper =  pop_stack(plk_stk_head);
        add2_list_quene(num_quene,top_oper);
        pri_operator_pop_stack( num_quene, plk_stk_head ,oper );
    }
    else
        push_stack(plk_stk_head,oper);

}

int get_operator_priority(data_t operator)
{
    switch (operator)
    {
    case '+':

    case '-':
              return 1; 

    case '*':

    case '/':
              return 2; 

    case '(':
              return 3; 

    case ')':
              return 3; 

    default : 
              return -1;
    }

}

