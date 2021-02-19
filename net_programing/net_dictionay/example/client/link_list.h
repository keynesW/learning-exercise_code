#ifndef _link_list_t_H_
#define _link_list_t_H_

#include <stdio.h> 
#include <stdlib.h>



#define  IS_LIST_EMPTY(ptr_list_head)  ((ptr_list_head)->next)  

typedef char * data_t;

typedef struct node{

        data_t data;
        struct node * next;

    }link_list_t;


extern void list_head_Init(link_list_t ** ptr_list_head );
extern link_list_t * list_Head_Init(link_list_t * ptr_list_head );
//extern void input_elem(link_list_t * ptr_list_head);
extern void list_Insert_head(link_list_t * ptr_list_head ,data_t data);
extern void list_Insert_end(link_list_t * ptr_list_head ,data_t data);
extern void print_linklist( link_list_t * ptr_list_head);
extern void free_list(link_list_t * ptr_list_head);
extern void list_Insert_order(link_list_t * ptr_list_head,data_t data);
extern void del_node(link_list_t * ptr_list_head,data_t data);
extern void reverse_list(link_list_t * ptr_list_head);

#endif
