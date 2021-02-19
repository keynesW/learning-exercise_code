#ifndef _QUENE_HEAD_
#define _QUENE_HEAD_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IS_LIST_QUENE_EMPTY(p_lq)\
    ((p_lq->front) == (p_lq)->rear)

//#define IS_LIST_QUENE_FULL(p_lq) \
    ((p_lq)->cunt == (p_lq)->max_que)


typedef int INT_DATA_T; 

typedef struct list_quene{
    INT_DATA_T data;
    struct list_quene * next; 
}lq_memb_st; 

typedef struct lquene_head{
    lq_memb_st * front;
    lq_memb_st * rear;
    int cunt;
}lq_head_st;

//extern int MAX_QUE; 
extern lq_head_st * lquene_Init( );
extern void add2lquene(lq_head_st *p_lq,INT_DATA_T data);
extern INT_DATA_T get_from_list_quene(lq_head_st *p_lq);
extern void print_quene(lq_head_st* p_lq);

#endif
