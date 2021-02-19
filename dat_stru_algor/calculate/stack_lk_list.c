#include "stack_lk_list.h"

lk_stk_head * lk_stk_head_Init(  )
{
    lk_stk_head * plk_stk_head;
    plk_stk_head = ( lk_stk_head * ) malloc( sizeof (lk_stk_head));
    if(!(plk_stk_head))
        printf("malloc failed\n");
    else
    {
        memset((void *)(plk_stk_head),0,sizeof (lk_stk_head));
        plk_stk_head->plk_stk_top = NULL;
    }
    return plk_stk_head;
}

void push_stack( lk_stk_head * plk_stk_head ,data_t data)
{
        lk_list_stk * temp = plk_stk_head->plk_stk_top;
        plk_stk_head->plk_stk_top = ( lk_list_stk * ) malloc(\
                                             sizeof (lk_list_stk));
        plk_stk_head->plk_stk_top->next = temp;

        plk_stk_head->plk_stk_top->data = data;
}

data_t pop_stack( lk_stk_head * plk_stk_head )
{

        data_t data ;
        lk_list_stk * node2free = NULL; 
        data = plk_stk_head->plk_stk_top->data ;
        node2free = plk_stk_head->plk_stk_top;
        plk_stk_head->plk_stk_top = plk_stk_head->plk_stk_top->next;
        free(node2free);

        return data;
}
