#include <stdio.h>
#include "quene.h"


int main()
{
    int num = 0;
    quene_st * p_quene = NULL;
    data_t data;

    printf("please enter a num to indecate the quene full\n");
    scanf("%d",&num);

    quene_Init( &p_quene,num);

    while(!IS_QUENE_FULL(p_quene))
    {
        printf("please enter a num to add\n");
        scanf("%d",&data);
        add2quene(p_quene,data);
    }

    printf("--------------out of quene---------\n");

    while(!IS_QUENE_EMPTY(p_quene))
    {
        
       data = get_from_quene(p_quene);
       printf("%d\n",data);
    }


    return 0;

}
