#ifndef _QUENE_HEAD_
#define _QUENE_HEAD_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IS_QUENE_EMPTY(p_quene) \
((p_quene)->front == (p_quene)->rear)

#define IS_QUENE_FULL(p_quene) \
    ( (p_quene)->front == ( ((p_quene)->rear + 1)%p_quene->max_que) )


typedef int data_t; 
typedef struct quene{
    
    int front ;
    data_t * que_arry;
    int rear ;
    int max_que;

}quene_st;

//extern int MAX_QUE; 
extern void quene_Init(quene_st ** p_quene,int max_que);
extern void add2quene(quene_st *p_quene,data_t data);
extern data_t get_from_quene(quene_st *p_quene);

#endif
