#ifndef _QUENE_HEAD_
#define _QUENE_HEAD_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IS_LIST_QUENE_EMPTY(p_list_quene)\
    ((p_list_quene->front) == (p_list_quene)->rear)
//#define IS_LIST_QUENE_FULL(p_list_quene) \
    ((p_list_quene)->cunt == (p_list_quene)->max_que)


typedef char INT_DATA_T; 

typedef struct list_quene{

    INT_DATA_T data;
    struct list_quene * next; 

}list_quene_st; 

typedef struct quene{
    list_quene_st * front;
    list_quene_st * rear;
    int cunt;

}list_quene_mk_st;

//extern int MAX_QUE; 
extern void list_quene_Init(list_quene_mk_st ** p_list_quene);
extern void add2_list_quene(list_quene_mk_st *p_list_quene,INT_DATA_T data);
extern INT_DATA_T get_from_list_quene(list_quene_mk_st *p_list_quene);
extern void print_quene(list_quene_mk_st* p_list_quene);

#endif
