#ifndef __CLIENT_LINKLIST_H_
#define __CLIENT_LINKLIST_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define IP_MAX_LEN 32 
extern int cunt ;

typedef struct client{
	char cli_ip[IP_MAX_LEN];
	unsigned short cli_port;	
	struct client *next;
}client_t;

extern void client_list_init(client_t *phead);
extern void client_list_add(client_t *phead,char *ipaddr,unsigned short port);
extern void client_list_del(client_t *phead,char *ipaddr,unsigned short port);
extern bool client_list_get_by_id(client_t *phead,int id,char *ipaddr,unsigned short *port);
extern void print_list(client_t *phead);

#endif
