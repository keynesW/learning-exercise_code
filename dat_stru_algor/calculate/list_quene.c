#include "list_quene.h"



void list_quene_Init(list_quene_mk_st ** p_list_quene)
{
    *p_list_quene = (list_quene_mk_st *) malloc( sizeof (list_quene_mk_st));
    (*p_list_quene)->front = (list_quene_st * ) malloc(sizeof (list_quene_st));
    (*p_list_quene)->front->next = NULL;    
    (*p_list_quene)->rear =  (*p_list_quene)->front;
    (*p_list_quene)->cunt = 0;

}

void add2_list_quene(list_quene_mk_st * p_list_quene,INT_DATA_T data) {

        list_quene_st * temp = NULL;
        temp = (list_quene_st *)malloc(sizeof (list_quene_st));
        temp->data = data;
        //printf("addr of front p2 = %p\n",p_list_quene->front);
        temp->next = p_list_quene->rear->next;
        //printf("addr of rear p2 = %p\n",p_list_quene->rear); p_list_quene->rear->next = temp;
        //printf("addr of temp->next = %p\n",temp->next);
        p_list_quene->rear = temp;    /////
        p_list_quene->cunt ++;
}

INT_DATA_T get_from_list_quene(list_quene_mk_st * p_list_quene)
{
    if(!IS_LIST_QUENE_EMPTY(p_list_quene))
    {
        INT_DATA_T data;
        data = p_list_quene->front->next->data;  
    
        list_quene_st *temp = p_list_quene->front->next;
        
        p_list_quene->front->next = temp->next;


        if(!(temp->next))
            p_list_quene->rear = p_list_quene->front;

        free(temp);

        return data;
    }
    else 
        printf("list quene is empty\n");
}
void print_quene(list_quene_mk_st* p_list_quene)
{
    list_quene_st *iter = p_list_quene->front->next;

    for(  ;iter  ; iter = iter->next)
        printf("%c 1 ",iter->data);

    putchar('\n');
}

