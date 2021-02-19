/*******************************************************************
 *
 *     File Name    :      list.c
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Sat 07 Nov 2020 01:48:15 PM CST
 *
 ******************************************************************/
#include "list.h"
link_list_t * list_Head_Init()
{
    link_list_t * ptr_list_head = NULL;
    ptr_list_head  = (link_list_t *)malloc(sizeof (link_list_t));
    ptr_list_head->data = 0;
    ptr_list_head->next = NULL;
    return ptr_list_head;
}

void list_Insert_end(link_list_t * ptr_list_head ,data_t data)
{

    link_list_t * Iterator = ptr_list_head;
    link_list_t * ptr_new_node = (link_list_t *)malloc(sizeof (link_list_t));

    for(  ;  Iterator->next ; Iterator = Iterator->next ) 
                ;

    ptr_new_node->next = NULL;
    Iterator->next = ptr_new_node;
    ptr_new_node->data = data;
}

void print_linklist( link_list_t * ptr_list_head)
{
    link_list_t * Iterator = ptr_list_head->next;
    putchar('\n');
    putchar('\n');
    if(IS_LIST_EMPTY(ptr_list_head))
        for(int i = 1  ;  Iterator ; Iterator = Iterator->next ,i++) 
             //printf("the %d element int list is %s\n",\
                 i,Iterator->data);
             printf("\t the %d cmd is : %s\n",\
                 i,Iterator->data);
    else 
        printf(" no cmd history !\n");
//    printf("\n");
}

void free_list(link_list_t * ptr_list_head)
{

    link_list_t * Iterator = ptr_list_head;
    link_list_t * ptr2free = NULL; 

    if(IS_LIST_EMPTY(ptr_list_head))
        while( Iterator->next )  
        {
            ptr2free = Iterator; 
            Iterator = Iterator->next;
            free(ptr2free->data);
            free(ptr2free);
            //printf("free link list\n");
            //print_linklist( Iterator );
        }
    //printf("history list free\n");
}
