/*******************************************************************
 *
 *     File Name    :      link_list_cpy.c
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Mon 02 Nov 2020 08:32:31 AM CST
 *
 ******************************************************************/

/* 
#include <stdio.h> 
#include <stdlib.h>



#define  IS_LIST_EMPTY(ptr_list_head)  ((ptr_list_head)->next)  

typedef struct node{

        int data;
        struct node * next;

    }link_list_t;


void list_Init(link_list_t ** ptr_head );
link_list_t * list_Head_Init(link_list_t * ptr_list_head );
void input_elem(link_list_t * ptr_list_head);
void list_Insert_head(link_list_t * ptr_list_head ,int data);
void list_Insert_end(link_list_t * ptr_list_head ,int data);
void print_linklist( link_list_t * ptr_list_head);
void free_list(link_list_t * ptr_list_head);
void list_Insert_order(link_list_t * ptr_list_head,int data);
void del_node(link_list_t * ptr_list_head,int data);
void reverse_list(link_list_t * ptr_list_head);


int main()
{
    int num = 0;
//    link_head_list_t * list_head; 
//    list_head_Init(&list_head); 
    link_list_t list_head; 
    list_Head_Init(&list_head); 
    

    printf("please enter how manytimes you want to input\n");
    scanf("%d",&num);
    getchar();

    while(num>0) 
    {
       input_elem(&list_head);
       num--;
    }

    print_linklist(&list_head);

        int data = 0;
        printf("please enter a num to del!\n");
        scanf("%d",&data);

    del_node(&list_head,data);
    print_linklist(&list_head);

    printf("-------------------reverse list----------------------\n");

    reverse_list(&list_head);
    print_linklist(&list_head);

    free_list(&list_head);

    return 0;
}
*/

#include "link_list.h"

void list_head_Init(link_list_t ** ptr_list_head )
{
    *ptr_list_head  = (link_list_t *)malloc(sizeof (link_list_t));
    (*ptr_list_head)->data = 0;
    (*ptr_list_head)->next = NULL;
}


link_list_t * list_Head_Init(link_list_t * ptr_list_head )
{
//      *ptr_list_head  = (link_list_t *)malloc(sizeof (link_list_t));
//    (*ptr_list_head)->data = 0;
//    (*ptr_list_head)->next = NULL;
    ptr_list_head->data = 0;
    ptr_list_head->next = NULL;
    return ptr_list_head;
}


/*
void input_elem(link_list_t * ptr_list_head)
{

    int data = 0;

    printf("please enter the num you want to add into the list\n");
    scanf("%d",&data);
//    getchar();

    list_Insert_head(ptr_list_head ,data);
//    list_Insert_end(ptr_list_head,data);
//
//    list_Insert_order(ptr_list_head,data);
}
*/

void list_Insert_head(link_list_t * ptr_list_head ,int data)
{

    link_list_t * ptr_new_node = (link_list_t *)malloc(sizeof (link_list_t));
    ptr_new_node->next = ptr_list_head->next;
    ptr_list_head->next = ptr_new_node;
    ptr_new_node->data = data;
}


void list_Insert_end(link_list_t * ptr_list_head ,int data)
{

    link_list_t * Iterator = ptr_list_head;
    link_list_t * ptr_new_node = (link_list_t *)malloc(sizeof (link_list_t));

    for(  ;  Iterator->next ; Iterator = Iterator->next ) 
                ;

    ptr_new_node->next = NULL;
    Iterator->next = ptr_new_node;
    ptr_new_node->data = data;
}

void list_Insert_order(link_list_t * ptr_list_head,int data)
{

    link_list_t * Iterator = ptr_list_head;
    link_list_t * ptr_new_node = (link_list_t *)malloc(sizeof (link_list_t));

    //be careful with this line
    for(  ;  Iterator->next && Iterator->next->data < data; Iterator = Iterator->next ) 
                ;

    ptr_new_node->next = Iterator->next;
    Iterator->next = ptr_new_node;

    ptr_new_node->data = data;

}

void del_node(link_list_t * ptr_list_head,int data)
{
    
    link_list_t * Iterator = ptr_list_head;
    if(IS_LIST_EMPTY(ptr_list_head))
    {   
        while(Iterator->next)
        {
            if( Iterator->next->data == data)
            {
                link_list_t *temp = NULL;
                temp = Iterator->next->next;
                free(Iterator->next);
                Iterator->next = temp;

            }else
            {
//                if(!Iterator->next)
//                    Iterator->next = NULL; 
//               else
                    Iterator = Iterator->next;
            }
        }
        printf("node of data %d was deleted\n",data);
    }
    else
        printf("list is empty,no elem to del!\n");

}


void reverse_list(link_list_t * ptr_list_head)
{
    link_list_t * Iterator = ptr_list_head->next->next;

    ptr_list_head->next->next = NULL;
    while( Iterator )
    {
        link_list_t * temp = NULL;

        temp = Iterator->next;
        Iterator->next = ptr_list_head->next;
        ptr_list_head->next = Iterator ;
        Iterator = temp;
    }

}


void print_linklist( link_list_t * ptr_list_head)
{
    link_list_t * Iterator = ptr_list_head->next;

    if(IS_LIST_EMPTY(ptr_list_head))
        for(int i = 1  ;  Iterator ; Iterator = Iterator->next ,i++) 
             printf("the %d element int list is %d\n",\
                 i,Iterator->data);
    else 
        printf("the list is empty!\n");
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
            free(ptr2free);
            //printf("free link list\n");
            //print_linklist( Iterator );
        }
}
