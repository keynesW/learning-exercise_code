#include "lstack.h"

lstack_head_st * lstack_Init(  )
{
    lstack_head_st * plstack_head;
    plstack_head = ( lstack_head_st * ) malloc( sizeof (lstack_head_st));
    if(!(plstack_head))
        printf("malloc failed\n");
    else
    {
        memset((void *)(plstack_head),0,sizeof (lstack_head_st));
        plstack_head->plk_stk_top = NULL;
        plstack_head->stk_membcunt = 0;
    }
    return plstack_head;
}

void push_stack( lstack_head_st * plstack_head ,data_t data)
{
        lstack_memb * temp = plstack_head->plk_stk_top;
        plstack_head->plk_stk_top = ( lstack_memb * ) malloc(\
                                        sizeof (lstack_memb));
        plstack_head->plk_stk_top->next = temp;

        plstack_head->plk_stk_top->data = data;

        plstack_head->stk_membcunt ++ ;

        //printf("after push plk_stk_top %p\n",plstack_head->plk_stk_top);
        //printf("%d ining stack\n",data);
}

data_t pop_stack( lstack_head_st * plstack_head )
{
    if(plstack_head != NULL && plstack_head->plk_stk_top != NULL)
    {
        data_t data ;
        lstack_memb * node2free = NULL; 

        data = plstack_head->plk_stk_top->data ;
        node2free = plstack_head->plk_stk_top;
        plstack_head->plk_stk_top = plstack_head->plk_stk_top->next;
        //printf("%d outing of stack\n",data);
        free(node2free);
        //printf("after pop plk_stk_top %p\n",plstack_head->plk_stk_top);
        plstack_head->stk_membcunt -- ;
        return data;
    }
    else
        return -1;
}


void print_stack( lstack_head_st * plstack_head)
{
    lstack_memb * iter = plstack_head->plk_stk_top;
//    printf("addr of stack top :%p\n",plstack_head->plk_stk_top);
    for( ; iter ;iter = iter->next )
    {
        printf("in stack : %d\n",iter->data);
    }
    putchar('\n');
}
