#include "quene.h"

void quene_Init(quene_st ** p_quene,int max_que)
{
    *p_quene = (quene_st *) malloc( sizeof (quene_st));
    
    memset(*p_quene,0,sizeof (quene_st));
    (*p_quene)->front = 0;
    (*p_quene)->rear = 0;
    (*p_quene)->max_que = max_que +1 ;
    (*p_quene)->que_arry = (data_t *)malloc(max_que*sizeof (data_t));

}

void add2quene(quene_st * p_quene,data_t data)
{
    if(!IS_QUENE_FULL(p_quene))
    {
        p_quene->que_arry[p_quene->rear] = data;
        p_quene->rear = (p_quene->rear + 1)%p_quene->max_que; 
    }
    else
        printf("quene is full\n");

}

data_t get_from_quene(quene_st * p_quene)
{
    if(!IS_QUENE_EMPTY(p_quene))
    {
        data_t data ;
        data = p_quene->que_arry[p_quene->front] ;
        p_quene->front = (p_quene->front + 1)%p_quene->max_que; 
       
        return data;
    }
    else
        printf("quene is full\n");
}
