#ifndef __list_t_H_
#define __list_t_H_

#include <stdio.h> 
#include <stdlib.h>



#define  IS_LIST_EMPTY(ptr_list_head)  ((ptr_list_head)->next)  

typedef char * data_t;

typedef struct node{

        data_t data;
        struct node * next;

    }link_list_t;


extern link_list_t * list_Head_Init();
extern void list_Insert_end(link_list_t * ptr_list_head ,data_t data);
extern void print_linklist( link_list_t * ptr_list_head);
extern void free_list(link_list_t * ptr_list_head);

#endif
