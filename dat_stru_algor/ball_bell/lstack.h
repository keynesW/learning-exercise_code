#ifndef _LK_STACK_HEAD_
#define _LK_STACK_HEAD_

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>


#define IS_STACK_EMPTY(plstack_head_st)  ((plstack_head->plk_stk_top == NULL)) 
#define GET_TOP_ELEM(plstack_head_st)  ((plstack_head)->plk_stk_top->data)

typedef int data_t; 

typedef struct lstack_node{
            data_t data;
            struct  lstack_node * next ; 
    }lstack_memb;

typedef struct stack{
     
    int stk_membcunt;
    lstack_memb * plk_stk_top;
    
}lstack_head_st;


extern lstack_head_st *  lstack_Init( );
extern void   push_stack( lstack_head_st * plstack_head ,data_t data);
extern data_t pop_stack( lstack_head_st * plstack_head );
extern void   print_stack( lstack_head_st * plstack_head);

#endif

