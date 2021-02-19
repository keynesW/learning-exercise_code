#include <stdio.h>
#include "list_quene.h"


int main()
{
    int num = 0;
    list_quene_mk_st * p_list_quene = NULL;

    data_t data;
    printf("please enter a num to indicate the quene full\n");
    scanf("%d",&num);

    list_quene_Init( &p_list_quene,num);


    while(!IS_LIST_QUENE_FULL(p_list_quene)) 
    {
        printf("please enter a num to add\n");
        scanf("%d",&data);
        add2_list_quene(p_list_quene,data);
    }

    printf("--------------print quene---------\n");

    print_quene(p_list_quene);

    printf("--------------out of quene---------\n");

    while(!IS_LIST_QUENE_EMPTY(p_list_quene))
    {
       data = get_from_list_quene(p_list_quene);
       printf("%d\n",data);
    }


    return 0;

}
