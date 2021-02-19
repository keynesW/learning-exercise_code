#include <stdio.h> 
#include <stdlib.h>



#define  IS_LIST_EMPTY(ptr_list_head)  ((ptr_list_head)->next == (ptr_list_head)\
                                        && (ptr_list_head)->next->next == (ptr_list_head) ) 

typedef struct node{

        int data;
        struct node * next;

    }link_list;


void list_Init(link_list ** ptr_head );
void input_elem(link_list * ptr_list_head);
void list_Insert_head(link_list * ptr_list_head ,int data);
void list_Insert_end(link_list * ptr_list_head ,int data);
void print_linklist( link_list * ptr_list_head);
void free_list(link_list * ptr_list_head);
void list_Insert_order(link_list * ptr_list_head,int data);
void del_node(link_list * ptr_list_head,int data);
void reverse_list(link_list * ptr_list_head);

int main()
{
    int num = 0;
    link_list * list_head; 

    list_Init(&list_head); 
    

    printf("please enter how manytimes you want to input\n");
    scanf("%d",&num);
    getchar();

    while(num>0) 
    {
       input_elem(list_head);
       num--;
    }

    print_linklist(list_head);

    int data = 0;
    printf("please enter a num to del!\n");
    scanf("%d",&data);
    del_node(list_head,data);
    print_linklist(list_head);

    printf("-------------------reverse list----------------------\n");


    reverse_list(list_head);
    print_linklist(list_head);


    free_list(list_head);
    return 0;
}



void list_Init(link_list ** ptr_list_head )
{
    *ptr_list_head  = (link_list *)malloc(sizeof (link_list));
    (*ptr_list_head)->data = 0;
    (*ptr_list_head)->next = *ptr_list_head;
    //printf("ptr_list_head->next = %p\n",(*ptr_list_head)->next);
}


void input_elem(link_list * ptr_list_head)
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

void list_Insert_head(link_list * ptr_list_head ,int data)
{

    link_list * ptr_new_node = (link_list *)malloc(sizeof (link_list));

    ptr_new_node->next = ptr_list_head->next;
    ptr_list_head->next = ptr_new_node;
//    printf("ptr_list_head->next = %p\n",ptr_list_head->next);
    ptr_new_node->data = data;
}


void list_Insert_end(link_list * ptr_list_head ,int data)
{

    link_list * Iterator = ptr_list_head;
    link_list * ptr_new_node = (link_list *)malloc(sizeof (link_list));

    for(  ;  Iterator->next != ptr_list_head ; Iterator = Iterator->next ) 
                ;

    ptr_new_node->next = Iterator->next;
    Iterator->next = ptr_new_node;
    ptr_new_node->data = data;
}

void list_Insert_order(link_list * ptr_list_head,int data)
{

    link_list * Iterator = ptr_list_head;
    link_list * ptr_new_node = (link_list *)malloc(sizeof (link_list));

    //be careful with this line
    for(  ;  Iterator->next != ptr_list_head && Iterator->next->data < data; Iterator = Iterator->next ) 
                ;

    ptr_new_node->next = Iterator->next;
    Iterator->next = ptr_new_node;
    //printf("debug inf\n");
    ptr_new_node->data = data;

}

void del_node(link_list * ptr_list_head,int data)
{
    
    link_list * Iterator = ptr_list_head;
    if(!IS_LIST_EMPTY(ptr_list_head))
    {   
        while(Iterator->next != ptr_list_head)
        {
            if( Iterator->next->data == data)
            {
                link_list *temp = NULL;
                temp = Iterator->next->next;
                //printf("Iterator = %p\n",Iterator);
                //printf("Iterator->next = %p\n",temp);
                free(Iterator->next);
                Iterator->next = temp; 
            }else
            {
                //if(Iterator->next == ptr_list_head)
                //        free(ptr_list_head);
                //else
                        Iterator = Iterator->next;
            }
        }
        /*
                if(Iterator->next == ptr_list_head && 
                             Iterator->next->next == ptr_list_head)
                {
                        free(ptr_list_head);
                        printf("list is empty,head is released !\n");
                }
        */
    }
    else
        printf("list is empty,no elem to del!\n");

}


void reverse_list(link_list * ptr_list_head)
{
    link_list * Iterator = ptr_list_head->next->next;

    ptr_list_head->next->next = ptr_list_head;
    while( Iterator != ptr_list_head )
    {
        link_list * temp = NULL;

        temp = Iterator->next;
        Iterator->next = ptr_list_head->next;
        ptr_list_head->next = Iterator ;
        Iterator = temp;
    }
}


void print_linklist( link_list * ptr_list_head)
{
    link_list * Iterator = ptr_list_head->next;

    if(!IS_LIST_EMPTY(ptr_list_head))
    {
        for(int i = 1  ;  Iterator != ptr_list_head ; Iterator = Iterator->next ,i++) 
             printf("the %d element int list is %d\n",\
                 i,Iterator->data);
    }
    else 
        printf("the list is empty!\n");
//    printf("\n");
}


void free_list(link_list * ptr_list_head)
{

    link_list * Iterator = ptr_list_head;
    link_list * ptr2free = NULL; 

    if(IS_LIST_EMPTY(ptr_list_head))
        while( Iterator != ptr_list_head )  
        {
            ptr2free = Iterator; 
            Iterator = Iterator->next;
            free(ptr2free);
        }

}
