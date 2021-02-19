#include "linklist.h"

int cunt = 0;

void client_list_init(client_t *phead)
{
    if(phead != NULL){
        memset(phead->cli_ip,0,sizeof(phead->cli_ip));
        phead->cli_port = 0;
        phead->next = NULL;
    }
}

void client_list_add(client_t *phead, char *ipaddr,unsigned short port)
{
    client_t *cur = phead;
    client_t *prev = NULL;	

    //查看客户端链表中是否已经存在
    while(cur != NULL){
        if(strcmp(cur->cli_ip,ipaddr) == 0 && cur->cli_port == port)	
            return;
        prev = cur;
        cur = cur->next;
    }

    //如果没有找到,cur 指向 NULL, prev 指向 最后一个节点

    //创建新的节点
    cur = (client_t *)malloc(sizeof(client_t));
    memset(cur,0,sizeof (client_t));
    if(cur != NULL){
        //初始化节点
        strcpy(cur->cli_ip,ipaddr);
        cur->cli_port = port;

        //将 cur 节点插入到链表尾
        prev->next = cur;
    }

    printf("==============================================\n");
    printf("add client(%s:%d)\n",cur->cli_ip,cur->cli_port);
    printf("==============================================\n");
    putchar('\n');
    cunt ++;
}

void client_list_del(client_t *phead,char *ipaddr,unsigned short port)
{
    client_t *cur = phead;	
    client_t *prev = NULL;

    //遍历客户端链表,找到对应的节点
    while(cur != NULL){
        if(strcmp(cur->cli_ip,ipaddr) == 0 && 
            cur->cli_port == port)
            break;

        prev = cur;
        cur = cur->next;
    }

    //表示没有找到
    if(cur == NULL)
        return;

    //删除节点
    prev->next = cur->next;
    free(cur);

    printf("==============================================\n");
    printf("del client(%s:%d)\n",ipaddr,port);
    printf("==============================================\n");
    cunt --;
}

bool client_list_get_by_id(client_t *phead,int id,char *ipaddr,unsigned short *port)
{
    int cur_id = 0;
    client_t *cur = phead->next;

    //遍历客户端链表,根据id进行匹配
    while(cur != NULL){
        if(cur_id == id){
            strcpy(ipaddr,cur->cli_ip);
            *port = cur->cli_port;
            return true;
        }

        cur = cur->next;
        cur_id++;
    }

    return false;
}

void print_list(client_t *phead)
{
    client_t * iter = phead;
    printf("-------------------client list print------------------\n");
    printf("cunt : %d\n",cunt);

    for( ; iter ;iter = iter->next)
    {
        printf("in client list : %s\n",iter->cli_ip);
    }
    printf("-------------------client list print------------------\n");
    //printf("in client list : %hd\n",iter->cli_port);

}
