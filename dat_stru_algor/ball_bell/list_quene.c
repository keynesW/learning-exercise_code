#include "lquene.h"

lq_head_st * lquene_Init( )
{
    lq_head_st * p_lq = NULL;
    p_lq = (lq_head_st *) malloc( sizeof (lq_head_st));
    p_lq->front = (lq_memb_st * ) malloc(sizeof (lq_memb_st));
    p_lq->front->next = NULL;    
    p_lq->rear =  p_lq->front;
    p_lq->cunt = 0;
    return p_lq;
}

void add2lquene(lq_head_st * p_lq,INT_DATA_T data) 
{
        lq_memb_st * temp = NULL;
        temp = (lq_memb_st *)malloc(sizeof (lq_memb_st));
        temp->data = data;
        //printf("addr of front p2 = %p\n",p_lq->front);
        temp->next = p_lq->rear->next;
        //printf("addr of rear p2 = %p\n",p_lq->rear);
        p_lq->rear->next = temp;
        //printf("addr of temp->next = %p\n",temp->next);
        p_lq->rear = temp;    /////
        p_lq->cunt ++;
        //printf("%d ining quene\n",data);
}

INT_DATA_T get_from_list_quene(lq_head_st * p_lq)
{
    if(!IS_LIST_QUENE_EMPTY(p_lq))
    {
        INT_DATA_T data;
        data = p_lq->front->next->data;
        //printf("outing of quene %d\n",data);

        lq_memb_st *temp = p_lq->front->next;
        p_lq->front->next = temp->next;

        if(!(temp->next))
            p_lq->rear = p_lq->front;

        free(temp);

        return data;
    }
    else 
    {
        printf("list quene is empty\n");
        return -1;
    }
}
void print_quene(lq_head_st* p_lq)
{
    lq_memb_st *iter = p_lq->front->next;
    if(!IS_LIST_QUENE_EMPTY(p_lq))
    {
        //printf("addr of iter = %p",iter);
        for(  ;iter  ; iter = iter->next)
        {
            //printf("addr of iter = %p",iter);
            printf("%d  ",iter->data);
        }

        putchar('\n');
    }
    else
    {
        printf("\nquene is empty\n\n");
        return ;
    }
}

