/*******************************************************************
 *
 *     File Name    :      main_bool.c
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Tue 20 Oct 2020 07:33:07 PM CST
 *
 ******************************************************************/

#include <stdio.h>
#include "lquene.h"
#include "lstack.h"

#define M_QUENE 1
#define QUENE 2
#define H_QUENE 2

#define IS_mSTACK_FULL(plstack_head)\
    ((plstack_head->stk_membcunt == 5)) 
#define IS_hSTACK_FULL(plstack_head)\
    ((plstack_head->stk_membcunt == 11)) 


void Create_ball_quene(lq_head_st * plq_head);
void pop_stk2quen(lq_head_st * plq_head,lstack_head_st * plstack_head);
void add_qelem2stk(lq_head_st * plq_head,lstack_head_st * plstack_head,int stk_typ);
void outq2stk_sel(lq_head_st * plq_head,lstack_head_st * plstk_h ,\
                        lstack_head_st * plstk_m , lstack_head_st *plstk );


    lq_head_st * plquen = NULL; 
    lstack_head_st * plstk_m = NULL; 
    lstack_head_st * plstk = NULL;
    lstack_head_st * plstk_h = NULL;

int main(int argc, char *argv[])
{

    plquen = lquene_Init();

    plstk_m = lstack_Init(); 
    plstk = lstack_Init();
    plstk_h = lstack_Init();

    Create_ball_quene(plquen);

    printf("-----------add data into stack-----------\n");
    add_qelem2stk(plquen,plstk_h,H_QUENE);
    add_qelem2stk(plquen,plstk_h,H_QUENE);

    printf("---------------end of adding-------------------\n");

    printf("-----------stack checking-----------\n");
    print_stack( plstk_h );

    printf("-----------pop stack add into quene-----------\n");

//    while(plstk_m->stk_membcunt)
    pop_stk2quen(plquen,plstk_h);

    printf("-----------print quene-----------\n");
    print_quene(plquen);

    printf("-----------stack checking-----------\n");
    print_stack( plstk_h );

    printf("-----------operation ended print quene-----------\n");
    return 0;

}

//print_stack( lstack_head_st * plstack_head);

void Create_ball_quene(lq_head_st * plq_head)
{
    for(int i = 1; i <= 26 ; i++)
    {
        add2lquene(plq_head,i);
    }
    printf("quene member added\n");

    print_quene(plq_head);
}


void pop_stk2quen(lq_head_st * plq_head,lstack_head_st * plstack_head)
{
    data_t stk_data = 0 ;

    while( plstack_head->stk_membcunt )
    {
        stk_data = pop_stack(plstack_head);
        add2lquene(plq_head,stk_data);
    }

}


void add_qelem2stk(lq_head_st * plq_head,lstack_head_st * plstack_head,int stk_typ)
{
        INT_DATA_T q_data = 0 ;

        switch(stk_typ)
        {
        case M_QUENE :
            if(!IS_mSTACK_FULL(plstack_head))
                goto push;
            goto full;
        case H_QUENE :
            if(!IS_hSTACK_FULL(plstack_head))
                goto push;
            goto full;
        default :
            return ;
        }

push :      
        {
            q_data = get_from_list_quene(plq_head);
            push_stack(plstack_head,q_data);
            printf("pushing\n");
            return;
        }

full :
        switch(stk_typ)
        {
        case M_QUENE :
            if(IS_mSTACK_FULL(plstack_head))
                goto pop;
            break;
        case H_QUENE :
            if(IS_hSTACK_FULL(plstack_head))
                goto pop;
            break;
        default :
            return ;
        }
pop :
        //while(plstack_head->stk_membcunt)
        {
            printf("popping\n");
            print_quene(plq_head);
            print_stack( plstack_head );

            pop_stk2quen(plq_head,plstack_head);

            print_stack( plstack_head );
            print_quene(plq_head);
            printf("pop ended\n");
        }

        return;

}

void outq2stk_sel(lq_head_st * plq_head,lstack_head_st * plstk_h ,\
                        lstack_head_st * plstk_m , lstack_head_st *plstk )
{
    if(!IS_LIST_QUENE_EMPTY(plquen))
    {
        switch (que_typ)
    case M_QUENE:
            add_qelem2stk(plq_head,plstk_m,M_QUENE);
            break;
    case QUENE:
            add_qelem2stk(plq_head,plstk,QUENE);
            break;
    case H_QUENE:
            add_qelem2stk(plq_head,plstk_h,H_QUENE);
            break;
    default :
            return ;
    }
    else
    {
        print_quene(plq_head);

        pop_stk2quen(plq_head,plstack_head);
        pop_stk2quen(plq_head,plstk);
        pop_stk2quen(plq_head,plstk_m);

        print_quene(plq_head);
    }
}
