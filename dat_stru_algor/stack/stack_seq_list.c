#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#define MAX 5

#define IS_STACK_EMPTY(p_seqlist)  (((p_seqlist)->top < 0)) 
#define IS_STACK_FULL(p_seqlist)  ((p_seqlist)->top == MAX-1) 
#define GET_TOP_ELEM(p_seqlist)  ((p_seqlist)->data[(p_seqlist)->top])

typedef int data_t;

typedef struct stack{

    data_t  data[MAX];
    int top;
    
}stack_seqlist;


void  stack_seqlist_Init(stack_seqlist ** p_seqlist);
void  push_stack( stack_seqlist * p_seqlist ,data_t data);
data_t pop_stack( stack_seqlist * p_seqlist );

int main()
{
    
    stack_seqlist * ptr_seqlist = NULL; 
    data_t dat;
    stack_seqlist_Init(&ptr_seqlist);
    //printf("!0 = %d\n",!0);
    //printf("!3 = %d\n",!3);
    while(!IS_STACK_FULL(ptr_seqlist))
    {
        printf("please enter a num to push\n");
        scanf("%d",&dat);
        push_stack(ptr_seqlist,dat);
    }

    printf("top elem of stack is %d\n",GET_TOP_ELEM(ptr_seqlist));

    while(!IS_STACK_EMPTY(ptr_seqlist))
    {
        dat = pop_stack(ptr_seqlist);
        printf("%d\n",dat);
    }

    return 0;
}

void  stack_seqlist_Init(stack_seqlist ** p_seqlist)
{
    *p_seqlist = ( stack_seqlist * ) malloc( sizeof (stack_seqlist));
    if(!(*p_seqlist))
        printf("malloc failed\n");
    else
    {
        memset((void *)(*p_seqlist),0,sizeof (stack_seqlist));
        (*p_seqlist)->top = -1;
    }
}

void push_stack( stack_seqlist * p_seqlist ,data_t data)
{
        p_seqlist->top ++;
        p_seqlist->data[p_seqlist->top] = data;
}

data_t pop_stack( stack_seqlist * p_seqlist )
{
        data_t data = 0;
        data = p_seqlist->data[p_seqlist->top] ;
        p_seqlist->top --;

        return data;
}
