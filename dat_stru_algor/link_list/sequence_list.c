#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IS_LIST_EMPTY() (stud->n == 0) 

typedef char typed_data;

struct student{

        typed_data *ID; 
        int n; 

    };

void get_size();
void sequence_list_init(struct student *stud,int num_id);
void insert_ID2sequence(struct student *stud );
void insert_ID2_pos(struct student *stud );
void print_sequence_list(struct student *stud);
void sort_ID(struct student *stud);
void del_elelm(struct student * stud);


int size = 0;


int main()
{
    struct student  sequence_list;

    get_size();
    sequence_list_init(&sequence_list,size);
    insert_ID2sequence(&sequence_list);
    print_sequence_list(&sequence_list);

    printf("-------------insert to position--------------\n");
    insert_ID2_pos(&sequence_list);
    print_sequence_list(&sequence_list);
    
    printf("------------------sort----------------------\n");
    sort_ID(&sequence_list);
    print_sequence_list(&sequence_list);


    printf("------------------delete----------------------\n");
    del_elelm(&sequence_list);
    print_sequence_list(&sequence_list);


    free(sequence_list.ID);
    sequence_list.ID = NULL;
    return 0;
}


void get_size()
{
    extern int size;
    printf("please enter the num of ID you want to input :\n");
    scanf("%d",&size);
    getchar();
}


void sequence_list_init(struct student *stud,int num_id)
{

    stud->ID = (typed_data *)malloc(num_id);
    memset(stud->ID,0,num_id*sizeof *stud->ID);
    stud->n = 0;

}


void insert_ID2sequence(struct student *stud )
{
    extern int size;

    for(int i = 0 ; i < size ; i++)
    {
        printf("please enter an ID\n");
        scanf("%c",&stud->ID[stud->n]);
        getchar();
        stud->n ++;
    }

}

void insert_ID2_pos(struct student *stud )
{
    extern int size;
    int position;
    char ID = '\0';

    printf("please enter the position to insert\n");
    scanf("%d",&position);
    getchar();

    if(position<size)
    {
        printf("please enter an ID to insert\n");
        scanf("%c",&ID);
        getchar();
        strcpy(&stud->ID[position],&stud->ID[position-1]);
        stud->ID[position-1] = ID;
        stud->n ++;
    }
    else 
        printf("illegal position\n");

}


void sort_ID(struct student *stud)
{
    char temp;
    for(int i = 0 ; i < stud->n ; i++)
        for (int j = i+1 ; j < stud->n ; j++)
        {
           if(stud->ID[i] > stud->ID[j])
           {
                temp = stud->ID[j];
                stud->ID[j] = stud->ID[i];
                stud->ID[i] = temp;
           }

        }
}




void del_elelm(struct student * stud)
{
    char * ptr_iter = stud->ID;
    char * ptr_res = stud->ID;
    int i = 0;
    char dat_del;

    if(IS_LIST_EMPTY())
        printf("there is no elem,please add first!\n");
    else
    {
        printf("please enter a num to del\n");
        scanf("%c",&dat_del);
        getchar();

        for( ; i <= size ; i++)
        {
            /*
             *if(*ptr_iter != dat_del)
             *{
             *    *ptr_res = *ptr_iter;
             *    ptr_res ++; 
             *}
             *ptr_iter ++;
             */
             
             if( *ptr_iter != dat_del )
                  ptr_res ++;
             ptr_iter++;
             *ptr_res = *ptr_iter;
             
        }

        stud->n = ptr_res - stud->ID;

        if(ptr_res == ptr_iter)
            printf("there is no element as you input,no element deleted\n");
    }


}

void print_sequence_list(struct student *stud)
{
/*
    char * iter = stud->ID;
    while( *iter )
    {
        printf("ID[%d] = %c\n",(int)(iter-stud->ID),stud->ID[iter-stud->ID]);
        iter++;
    }
*/
    for(int iter = 0 ; iter < stud->n; iter++)
        printf("ID[%d] = %c\n",iter,stud->ID[iter]);
}


