#ifndef _LK_STACK_HEAD_
#define _LK_STACK_HEAD_

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>


#define IS_STACK_EMPTY(plk_stk_head)  ((plk_stk_head->plk_stk_top == NULL)) 
#define GET_TOP_ELEM(plk_stk_head)  ((plk_stk_head)->plk_stk_top->data)

typedef char data_t; 

typedef struct lk_stack_node{
            data_t data;
            struct  lk_stack_node * next ; 
    }lk_list_stk;

typedef struct stack{

    lk_list_stk * plk_stk_top;
    
}lk_stk_head;


extern lk_stk_head *  lk_stk_head_Init( );
extern void  push_stack( lk_stk_head * plk_stk_head ,data_t data);
extern data_t pop_stack( lk_stk_head * plk_stk_head );

#endif

