#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#define MAX 5

#define IS_STACK_EMPTY(plk_stk_head)  ((plk_stk_head->plk_stk_top == NULL)) 
#define IS_STACK_FULL(plk_stk_head)  ((plk_stk_head->cunt == max_lk_stack))
#define GET_TOP_ELEM(plk_stk_head)  ((plk_stk_head)->plk_stk_top->data)

typedef char data_t;

typedef struct lk_stack_node{
            data_t data;
            struct  lk_stack_node * next ; 
    }lk_list_stk;

typedef struct stack{

    int cunt;
    lk_list_stk * plk_stk_top;
    
}lk_stk_head;


void  lk_stk_head_Init(lk_stk_head ** plk_stk_head,int num);
void  push_stack( lk_stk_head * plk_stk_head ,data_t data);
data_t pop_stack( lk_stk_head * plk_stk_head );

int max_lk_stack = 0;

int main()
{
    
    lk_stk_head * plk_stk_head = NULL; 
    data_t dat;

    //extern int num ;
    printf("please enter a num to mark stack full\n");
    scanf("%d",&max_lk_stack);
    getchar();

    lk_stk_head_Init(&plk_stk_head,max_lk_stack);

    //printf("!0 = %d\n",!0);
    //printf("!3 = %d\n",!3);
  
    while(!IS_STACK_FULL(plk_stk_head))
    {
        printf("please enter a num to push\n");
        scanf("%c",&dat);
        getchar();

        push_stack(plk_stk_head,dat);
    }

    printf("------------ get top ------------\n");


    printf("top elem of stack is %c\n",GET_TOP_ELEM(plk_stk_head));


    printf("-------------- pop ---------------\n");

    while(!IS_STACK_EMPTY(plk_stk_head))
    {
        dat = pop_stack(plk_stk_head);
        printf("%c\n",dat);
    }

    return 0;
}

void  lk_stk_head_Init(lk_stk_head ** plk_stk_head,int num)
{
    *plk_stk_head = ( lk_stk_head * ) malloc( sizeof (lk_stk_head));
    if(!(*plk_stk_head))
        printf("malloc failed\n");
    else
    {
        memset((void *)(*plk_stk_head),0,sizeof (lk_stk_head));
        (*plk_stk_head)->plk_stk_top = NULL;
        (*plk_stk_head)->cunt = 0;
    }
}

void push_stack( lk_stk_head * plk_stk_head ,data_t data)
{
        lk_list_stk * temp = plk_stk_head->plk_stk_top;
        plk_stk_head->plk_stk_top = ( lk_list_stk * ) malloc(\
                                             sizeof (lk_list_stk));
        plk_stk_head->plk_stk_top->next = temp;

        plk_stk_head->plk_stk_top->data = data;
        plk_stk_head->cunt ++;
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
