#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define UP2DOWN  '1'
#define DOWN2UP  '2'
#define SIZE  20 


struct student {
        char  name[20];
        char  id[19];
        int   age;
        float score;
        };


void tips_disp();
int  menu_select();
void del_student_inf_menu(char * select);
void add_student_inf();
int  del_student_inf(char *inf2del,char * select);
void scan_stud(struct student * stu);
void print_stud(struct student * stu);
void printa_stud();
void lookfor_print_menu(char * select);
struct student *  stud_inf_looking(char * inf2find,char *select);
void stud_inf_edit_menu(char *select);
void stud_inf_edit(struct student * stu);
void stud_inf_sort_menu(char *select);
void stud_inf_sort(char * select,int direct);

void sort_by_name_up2down();
void sort_by_name_down2up();
void sort_by_id_up2down();
void sort_by_id_down2up();
void sort_by_age_up2down();
void sort_by_age_down2up();
void sort_by_score_up2down();
void sort_by_score_down2up();


static int stud_inf_cunt = 0 ;
struct student stud_inf_arry[SIZE] = {0};


int main()
{
    tips_disp();
    while(menu_select()) 
                ;
    return 0;
}

int menu_select()
{
    char select = '\0';
    select = getchar();
    printf("in first level menu select you chose is %c\n",select);
    getchar();
    switch (select)
    {
    case '1':
        add_student_inf() ;
        tips_disp();
        return 1; 
//        break;
    case '2':
        del_student_inf_menu(&select);
        tips_disp();
        return 1; 
//        break;
    case '3':
        lookfor_print_menu(&select);
        tips_disp();
        return 1; 
//        break;
    case '4':
        stud_inf_sort_menu(&select);
        tips_disp();
        return 1; 
//        break;
    case '5':
        stud_inf_edit_menu(&select);
        tips_disp();
        return 1; 
//        break;
    case '6':
        printa_stud(); 
        tips_disp();
        return 1; 
//        break;
    case 'q':
        return 0; 
    case 'Q':
        return 0; 
    default:
//        tips_disp();
        return 1;
    }
}


void tips_disp()
{

            printf("please enter the num to select an operation\n    \
            menue   :\n        \
            1 : add student information\n        \
            2 : delete student information\n        \
            3 : looking for a student\n        \
            4 : sort students' inf\n        \
            5 : to edit a student's inf\n        \
            6 : to deisplay all students' inf\n        \
            q : to quit\n");
}

void del_student_inf_menu(char * select) 
{
    *select = '\0';
    char inf2del[20] = {'\0'};

    printf("please enter a num to select  a way to delete :\n    \
        1 : delete by name\n    \
        2 : delete by ID\n    \
other keys: back to top level of the menue\n");

    scanf("%c",select);
    printf("the way you select to del is :%c\n",*select);
        getchar();
    if(*select == '1')
    {
        printf("please enter the name to delete\n");
        scanf("%s",inf2del);
        getchar();
        if(del_student_inf(inf2del,select))
            printf("the student of name %s was deleted\n",inf2del);
    }
    else
        if(*select == '2')
        {
            printf("please enter the ID to delete\n");
            scanf("%c",inf2del);
            getchar();
            if(del_student_inf(inf2del,select))
            printf("the student of ID %s was deleted\n",inf2del);
        }
}



void add_student_inf() 
{
    extern int stud_inf_cunt  ;
    extern struct student stud_inf_arry[SIZE]; 
    if(stud_inf_cunt < SIZE)
        scan_stud(&stud_inf_arry[stud_inf_cunt]);
    else
        printf("student list is full\n");

    stud_inf_cunt ++; 
}


void scan_stud(struct student * stu)
{
//    char arry[20] = {'\0'};
    printf("please enter your name :\n");
    scanf("%s",stu->name);
//    scanf("%s",arry);
//    strcpy(stu->name,arry);
    
    printf("please enter your id :\n");
    scanf("%s",stu->id);

    printf("please enter your age :\n");
    scanf("%d",&stu->age);
    
    printf("please enter your score :\n");
    scanf("%f",&stu->score);
    getchar();
}



int del_student_inf(char *inf2del,char *select)
{
    extern struct student stud_inf_arry[SIZE]; 
    extern int stud_inf_cunt;
    struct student *ptr_stud = NULL; 
    if(*select == '1')
    {

        int iter ;
        for(iter = 0; iter < stud_inf_cunt ;iter ++)
        {
            if(strcmp(  (const char *)\
                             ((stud_inf_arry[iter]).name),\
                                (const char *)inf2del) == 0   )
            {
                printf("delet stud_inf\n");

                memmove(  (void *)&stud_inf_arry[iter],\
                          (void *)&stud_inf_arry[iter+1],\
                          sizeof (struct student)*(stud_inf_cunt - iter) );

                stud_inf_cunt --;
                return 1;
            }
        }
        if (iter >= stud_inf_cunt) 
        {
            printf("there is not a student named %s\n",inf2del);
            return 0;
        }
    }
    else
        if(*select == '2')
        {   
            int iter ;
            for(iter = 0; iter < stud_inf_cunt ;iter ++)
            {
                if(strcmp(  (const char *)(stud_inf_arry[iter]).id,\
                            (const char *)inf2del) == 0 )
                {
                    memmove(  (void *)&stud_inf_arry[iter],\
                              (void *)&stud_inf_arry[iter+1],\
                              sizeof (struct student)*(stud_inf_cunt - iter));

                    stud_inf_cunt --;
                    return 1;
                }
            }
            if (iter >= stud_inf_cunt) 
            {
                printf("there is not a student id %s\n",inf2del);
                return 0;
            }
        }
}



void printa_stud()
{
    extern int stud_inf_cunt;
    extern struct student stud_inf_arry[SIZE];

    printf("stud_inf_cunt is %d\n",stud_inf_cunt);
    if(stud_inf_cunt)
    {
        for(int iter = 0 ; iter < stud_inf_cunt ; iter ++)
            print_stud(&stud_inf_arry[iter]);
    }
    else
        printf("there is no student inf to display,please add first\n");
}
void lookfor_print_menu(char * select)
{
    *select = '\0';
    char inf2find[20] = {'\0'};

    printf("please enter a num to select  a way to looking for :\n    \
        1 : looking for by name\n    \
        2 : looking for by ID\n    \
other keys: back to top level of the menue\n");

    scanf("%c",select);
    printf("the way you select to del is :%c\n",*select);
        getchar();
    if(*select == '1')
    {
        printf("please enter the name to looking\n");
        scanf("%s",inf2find);
        getchar();
        print_stud( stud_inf_looking(inf2find,select) ); 
    }
    else
        if(*select == '2')
        {
            printf("please enter the ID to looking\n");
            scanf("%c",inf2find);
            getchar();
            print_stud( stud_inf_looking(inf2find,select) );
        }
}

struct student * stud_inf_looking(char * inf2find,char *select)
{
    int iter ;
    if(*select == '1')
    {
        for(iter = 0; iter < stud_inf_cunt ;iter ++)
        {
            if(strcmp(  (const char *)\
                             ((stud_inf_arry[iter]).name),\
                                (const char *)inf2find) == 0   )
            {
              //  print_stud( &stud_inf_arry[iter] );
                return &stud_inf_arry[iter];
            }
        }
        if (iter >= stud_inf_cunt) 
        {
            printf("there is not a student named %s\n",inf2find);
            return NULL;
        } 
    }
    else
        if(*select == '1')
        {
            int iter ;
            for(iter = 0; iter < stud_inf_cunt ;iter ++)
            {
                if(strcmp(  (const char *)(stud_inf_arry[iter]).id,\
                            (const char *)inf2find) == 0 )
                {
               //     print_stud( &stud_inf_arry[iter] );
                    return &stud_inf_arry[iter];
                }
            }
            if (iter >= stud_inf_cunt) 
            {
                printf("there is not a student id %s\n",inf2find);
                return NULL;
            }
        }
}

void stud_inf_edit_menu(char *select)
{
    *select = '\0';
    char inf2edit[20] = {'\0'};
    struct student * pstud = NULL;
    
    printf("please enter a num to select  a way to edit :\n    \
        1 : looking for by name\n    \
        2 : looking for by ID\n    \
other keys: back to top level of the menue\n");

    scanf("%c",select);
    getchar();
    printf("the way you select to del is :%c\n",*select);

    if(*select == '1')
    {
        printf("please enter the name to edit\n");
        scanf("%s",inf2edit);
        getchar();
        pstud =  stud_inf_looking(inf2edit,select) ; 
        if(pstud)
            //stud_inf_edit( pstud ); 
            scan_stud(pstud);
    }
    else
        if(*select == '2')
        {
            printf("please enter the ID to edit\n");
            scanf("%c",inf2edit);
            getchar();
            pstud =  stud_inf_looking(inf2edit,select) ; 
            if(pstud)
                //stud_inf_edit( pstud ); 
                scan_stud(pstud);
        }
}

void stud_inf_edit(struct student * stu)
{
    scan_stud( stu );
}

void stud_inf_sort_menu(char *select)
{

    extern int stud_inf_cunt;
    if (stud_inf_cunt <= 1)
        printf("there are not so many stud_inf to sort,please add inf first\n");
    else{
        printf("please enter a num to select  a way to sort :\n    \
            1 : up2down\n    \
            2 : down2up\n    \
            other keys: back to top level of the menue\n");

        scanf("%c",select);
        getchar();
        printf("the way you select to del is :%c\n",*select);

        if(*select == '1')
        {
            printf("please enter a num to select  a way to sort :\n    \
                1 : sort by name\n    \
                2 : sort by id\n    \
                3 : sort by age\n    \
                4 : sort by score\n    \
                other keys: back to top level of the menue\n");
            scanf("%c",select);
            getchar();
            printf("the way you select to del is :%c\n",*select);
            stud_inf_sort(select,UP2DOWN);   
        }
        else
            if(*select == '2')
            {
                printf("please enter a num to select  a way to sort :\n    \
                    1 : sort by name\n    \
                    2 : sort by id\n    \
                    3 : sort by age\n    \
                    4 : sort by score\n    \
                    other keys: back to top level of the menue\n");
                scanf("%c",select);
                getchar();
                printf("the way you select to sort is :%c\n",*select);
                stud_inf_sort(select,DOWN2UP);   
            }
    }
}
void stud_inf_sort(char * select,int direct)
{
    if(direct == UP2DOWN) 
    {
        switch (*select)
        {
        case '1':
            sort_by_name_up2down();
            break;
        case '2':
            sort_by_id_up2down();
            break;
        case '3':
            sort_by_age_up2down();
            break;
        case '4':
            sort_by_score_up2down();
            break;
        } 
    
    } 
    else
        if(direct == DOWN2UP)
        {
        switch (*select)
            {
            case '1':
                sort_by_name_down2up();
                break;
        case '2':
            sort_by_id_down2up();
            break;
        case '3':
            sort_by_age_down2up();
            break;
        case '4':
            sort_by_score_down2up();
            break;
            } 
        
        }
}


void sort_by_name_up2down()
{
    extern int stud_inf_cunt ;
    extern struct student stud_inf_arry[SIZE];
    struct student Temp_stud;
    int iter_i ,iter_j;
    for(iter_i = 0;iter_i < stud_inf_cunt;iter_i++)    
    {
        for(iter_j = iter_i + 1; iter_j < stud_inf_cunt -1 ;iter_j++)
        {
            if( strcmp(  (const char *)(stud_inf_arry[iter_i]).name,\
                    (const char *)(stud_inf_arry[iter_j]).name) <= 0 )
            {
                Temp_stud = stud_inf_arry[iter_i];
                stud_inf_arry[iter_i] = stud_inf_arry[iter_j];
                stud_inf_arry[iter_j] = Temp_stud;
            }

        }         
    }
    printf("after sort\n");
}
void sort_by_name_down2up()
{
    extern int stud_inf_cunt ;
    extern struct student stud_inf_arry[SIZE];
    struct student Temp_stud;
    int iter_i ,iter_j;
    for(iter_i = 0;iter_i < stud_inf_cunt;iter_i++)    
    {
        for(iter_j = 0 ;iter_j < stud_inf_cunt - iter_i - 1;iter_j++)
        {
            if( strcmp(  (const char *)(stud_inf_arry[iter_j]).name,\
                    (const char *)(stud_inf_arry[iter_j + 1]).name) >= 0 )
            {
                Temp_stud = stud_inf_arry[iter_j];
                stud_inf_arry[iter_j] = stud_inf_arry[iter_j + 1];
                stud_inf_arry[iter_j + 1] = Temp_stud;
            }
        }         
    }
    printf("after sort\n");
}

void sort_by_id_up2down()
{
    extern int stud_inf_cunt ;
    extern struct student stud_inf_arry[SIZE];
    struct student Temp_stud;
    int iter_i ,iter_j;
    for(iter_i = 0;iter_i < stud_inf_cunt;iter_i++)    
    {
        for(iter_j = iter_i + 1; iter_j < stud_inf_cunt -1 ;iter_j++)
        {
            if( strcmp(  (const char *)(stud_inf_arry[iter_i]).id,\
                    (const char *)(stud_inf_arry[iter_j]).id) <= 0 )
            {
                Temp_stud = stud_inf_arry[iter_i];
                stud_inf_arry[iter_i] = stud_inf_arry[iter_j];
                stud_inf_arry[iter_j] = Temp_stud;
            }
        }         
    }
    printf("after sort\n");
}
void sort_by_id_down2up()
{
    extern int stud_inf_cunt ;
    extern struct student stud_inf_arry[SIZE];
    struct student Temp_stud;
    int iter_i ,iter_j;
    for(iter_i = 0;iter_i < stud_inf_cunt;iter_i++)    
    {
        for(iter_j = 0 ;iter_j < stud_inf_cunt - iter_i - 1;iter_j++)
        {
            if( strcmp(  (const char *)(stud_inf_arry[iter_j]).id,\
                    (const char *)(stud_inf_arry[iter_j + 1]).id) >= 0 )
            {
                Temp_stud = stud_inf_arry[iter_j];
                stud_inf_arry[iter_j] = stud_inf_arry[iter_j + 1];
                stud_inf_arry[iter_j + 1] = Temp_stud;
            }
        }         
    }
    printf("after sort\n");
}

void sort_by_age_up2down()
{
    extern int stud_inf_cunt ;
    extern struct student stud_inf_arry[SIZE]; 
    struct student Temp_stud;
    int iter_i ,iter_j;
    for(iter_i = 0;iter_i < stud_inf_cunt - 1 ;iter_i++)    
    {
        for(iter_j = iter_i + 1; iter_j < stud_inf_cunt;iter_j++)
        {
            if( (stud_inf_arry[iter_i]).age <
                (stud_inf_arry[iter_j]).age )
            {
                Temp_stud = stud_inf_arry[iter_i];
                stud_inf_arry[iter_i] = stud_inf_arry[iter_j];
                stud_inf_arry[iter_j] = Temp_stud;
            }
        }         
    }
    printf("after sort\n");
}
void sort_by_age_down2up()
{
    extern int stud_inf_cunt ;
    extern struct student stud_inf_arry[SIZE];
    struct student Temp_stud;
    int iter_i ,iter_j;
    for(iter_i = 0;iter_i < stud_inf_cunt;iter_i++)    
    {
        for(iter_j = 0 ;iter_j < stud_inf_cunt - iter_i - 1;iter_j++)
        {
            if( (stud_inf_arry[iter_j]).age >
                (stud_inf_arry[iter_j + 1]).age )
            {
                Temp_stud = stud_inf_arry[iter_j];
                stud_inf_arry[iter_j] = stud_inf_arry[iter_j + 1];
                stud_inf_arry[iter_j + 1] = Temp_stud;
            }
        }         
    }
    printf("after sort\n");
}


void sort_by_score_up2down()
{
    extern int stud_inf_cunt ;
    extern struct student stud_inf_arry[SIZE];
    struct student Temp_stud;
    int iter_i ,iter_j;
    for(iter_i = 0;iter_i < stud_inf_cunt - 1 ;iter_i++)    
    {
        for(iter_j = iter_i + 1; iter_j < stud_inf_cunt;iter_j++)
        {
            if( (stud_inf_arry[iter_i]).score <
                (stud_inf_arry[iter_j]).score )
            {
                Temp_stud = stud_inf_arry[iter_i];
                stud_inf_arry[iter_i] = stud_inf_arry[iter_j];
                stud_inf_arry[iter_j] = Temp_stud;
            }
        }         
    }
    printf("after sort\n");
}
void sort_by_score_down2up()
{
    extern int stud_inf_cunt ;
    extern struct student stud_inf_arry[SIZE]; 
    struct student Temp_stud;
    int iter_i ,iter_j;
    for(iter_i = 0;iter_i < stud_inf_cunt;iter_i++)    
    {
        for(iter_j = 0 ;iter_j < stud_inf_cunt - iter_i - 1;iter_j++)
        {
            if( (stud_inf_arry[iter_j]).score >
                 (stud_inf_arry[iter_j + 1]).score )
            {
                Temp_stud = stud_inf_arry[iter_j];
                stud_inf_arry[iter_j] = stud_inf_arry[iter_j + 1];
                stud_inf_arry[iter_j + 1] = Temp_stud;
            }
        }         
    }
    printf("after sort\n");
}
void print_stud(struct student * stu)
{
    if(stu)
    {
        printf("hello         :%s\n",stu->name);
        printf("your age  is  :%s\n",stu->id);
        printf("your high is  :%d\n",stu->age);
        printf("your score is :%f\n",stu->score);
    }
}
