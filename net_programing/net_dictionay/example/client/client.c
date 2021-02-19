#include "head.h"
#include "list.h"

//用户输入指令，供大家选择
enum menue{/*{{{*/
	REGISTER = 1,  //注册
	LOGIN    = 2,  //登陆
    LOGOFF   = 3,  //注销
	QUIT     = 4,  //退出

	QUERY    = 1,  //查询单词
	MODIFY   = 2,  //查询历史 
    HISTORY  = 3,  //查询历史
    EXIT     = 4,  //退出查询

    ADD      = 1,
    DELETE   = 2,
};
/*}}}*/

//用户提示界面1 
void help_info1()
{/*{{{*/
	printf("\t-----------------------------------------------\n");
	printf("\t|                      在线辞典                |\n");
	printf("\t|版本:0.0.1                                    |\n");
	printf("\t|作者:Keynes                                   |\n");
	printf("\t|功能:                                         |\n");
	printf("\t|    [1] 注册                                  |\n");
	printf("\t|    [2] 登录                                  |\n");
	printf("\t|    [3] 注销                                  |\n");
	printf("\t|    [4] 退出                                  |\n");
	printf("\t|注意:用户只有登录成功后才能进入查单词界面     |\n");
	printf("\t------------------------------------------------\n");
	return;
}/*}}}*/

int init_tcp(char *ip,char *port)
{/*{{{*/  //config server to connect
	int sockfd;
	struct sockaddr_in server_addr;

	if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
		perror("Fail to socket");	
		exit(EXIT_FAILURE);
	}

	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(atoi(port));
	server_addr.sin_addr.s_addr = inet_addr(ip);

	if(connect(sockfd,(struct sockaddr *)&server_addr,sizeof(server_addr)) < 0)
	{
		perror("Fail to bind");	
		exit(EXIT_FAILURE);
	}

	return sockfd;
}/*}}}*/

int add2his_list(link_list_t * history_list,char * str)
{
    list_Insert_end(history_list,strncpy((char *)malloc(strlen(str)+1),str,strlen(str)+1));
}
int history(link_list_t * history_list)
{
    print_linklist( history_list );
}

int words_query(link_list_t * history_list,int sockfd)
{
/*{{{*/ //input word to query and send to server
    int n = 0;
    int count = 0;
    char buf[1024] = {0};
    //定义发送的协议头
    mhead_t *head = (mhead_t *)buf;

    while(1)
    {

        head->type = USER_WORD; 
        head->size = sizeof(mhead_t);

        printf("\n请输入需要查询的单词,q to quit\n");
        fgets(head->word,sizeof(head->word),stdin);
        head->word[strlen(head->word) - 1] = '\0';

        
        system("clear");
        putchar('\n');
        putchar('\n');
        printf("查询结果:\n");
        putchar('\n');
        putchar('\n');
        //printf("in buf : %s\n",head->word);
        //发给服务器端
        if( strncmp(head->word,"q\0",2) == 0 )
            return 0;
        
        add2his_list(history_list,head->word);

        if(send(sockfd,buf,sizeof(mhead_t),0) < 0)
        {
            perror("Fail to send");
            exit(EXIT_FAILURE);
        }
        bzero(&buf,sizeof(buf));
        //printf("request has been sent\n");
/*{{{*/  // deal with recived msg 

        while(1)
        {
            //接收数据，TCP是可靠的连接，若是数据
            //未完全接收的话，可以在接收
            n = recv(sockfd,buf + count,sizeof(mhead_t) - count,0);

            if(n <= 0){
                perror("Fail to recv");
                exit(EXIT_FAILURE);
            }
            //若是数据未发送完成，再次接收的时候可补充
            count += n;
            if(count == sizeof(mhead_t))
            {
                count = 0;
                break;
            }
        }

        if(head->type == USER_SUCCESS)
        {
            printf("%s\n",head->word);
            //            return 0;
        }else{
            printf("failed to find the word\n");
//            return -1;
        }
        //printf("end of one cycle\n");
        /*}}}*/
        
    }
    /*}}}*/
}
void delete_confirm()
{/*{{{*/

    int n = 0;
    int count = 0;
    char buf[1024] = {0};
    mhead_t *head = (mhead_t *)buf;

    printf(" enter the c to confirm to delete,q to quit \n");
    fgets(head->word,sizeof(head->word),stdin);
    head->word[strlen(head->word) - 1] = '\0';


    if( strncmp(head->word,"c\0",2) == 0 )
    {
        if(send(sockfd,buf,sizeof(mhead_t),0) < 0)
        {
            perror("Fail to send");
            exit(EXIT_FAILURE);
        }
        bzero(&buf,sizeof(buf));
    }
    else
    {
        strcpy(head->word,"cancel");
        if(send(sockfd,buf,sizeof(mhead_t),0) < 0)
        {
            perror("Fail to send");
            exit(EXIT_FAILURE);
        }
        return 0;
    }

    return 1;

}/*}}}*/

int words_modify_dict(int  sockfd, int cmd) 
{/*{{{*/

    int n = 0;
    int count = 0;
    char buf[1024] = {0};
    mhead_t *head = (mhead_t *)buf;

    while(1)
    {

        head->type = (cmd==ADD ? USER_ADD : USER_DELETE); 
        head->size = sizeof(mhead_t);
        cmd == ADD ?\
             printf("\n请输入需要添加的单词\n"):\
             printf("\n请输入需要删除的单词\n");

        fgets(head->word,sizeof(head->word),stdin);
        head->word[strlen(head->word) - 1] = '\0';

        if(send(sockfd,buf,sizeof(mhead_t),0) < 0)
        {
            perror("Fail to send");
            exit(EXIT_FAILURE);
        }
        bzero(&buf,sizeof(buf));

        while(1)
        {
            //接收数据，TCP是可靠的连接，若是数据
            //未完全接收的话，可以在接收
            n = recv(sockfd,buf + count,sizeof(mhead_t) - count,0);

            if(n <= 0){
                perror("Fail to recv");
                exit(EXIT_FAILURE);
            }
            //若是数据未发送完成，再次接收的时候可补充
            count += n;
            if(count == sizeof(mhead_t))
            {
                count = 0;
                break;
            }
        }
        printf("head->type %d\n",head->type);
        if(head->type == USER_SUCCESS)
        {
            printf(" word already exits: \n");
            cmd == DELETE ?  \
                printf(" delet sucess\n"),delete_confirm():\
                printf("%s\n",head->word),\
                printf(" enter the explain to modify and update,q to quit \n");
                goto explain ;
        
            //            return 0;
        }else{
            printf(" word not exits ,enter the explain to add, q to quit\n");
            cmd == DELETE ?  \
                printf("delete failed ") : 1 ;
            goto explain ;

        }
explain:
        fgets(head->word,sizeof(head->word),stdin);
        head->word[strlen(head->word) - 1] = '\0';
        //printf("in buf : %s\n",head->word);
        head->type = USER_WORD; 
        head->size = sizeof(mhead_t);

        if( strncmp(head->word,"q\0",2) == 0 )
        {
            strcpy(head->word,"cancel");
            if(send(sockfd,buf,sizeof(mhead_t),0) < 0)
            {
                perror("Fail to send");
                exit(EXIT_FAILURE);
            }
            return 0;
        }

        if(send(sockfd,buf,sizeof(mhead_t),0) < 0)
        {
            perror("Fail to send");
            exit(EXIT_FAILURE);
        }
        bzero(&buf,sizeof(buf));

    }

}/*}}}*/

int  words_add2dict_menu(int sockfd)
{/*{{{*/

    int cmd = 0;
    system("clear");
    putchar('\n');
    putchar('\n');
    
    while(1)
    {
        printf("\t-----------------------------------------------\n");
        printf("\t|    [1] 添加单词                             |\n");
        printf("\t|    [2] 删除单词                             |\n");
        printf("\t|    [3] 退出修改                             |\n");
        printf("\t-----------------------------------------------\n");
        printf("\n\n请选择>");

        scanf("%d",&cmd);
        //吃掉回车键
        getchar();
        system("clear");

        switch (cmd)
        {
        case ADD: 
            if( words_modify_dict( sockfd,ADD) == 0 )
                ;
            system("clear");
            break;

        case DELETE: 
            if( words_modify_dict( sockfd,DELETE) == 0 )
                ;
            system("clear");
            break;

        case  3  :
        case EXIT: 
            system("clear");
            return 0;
            //break;

        default :
            printf("invalid cmd\n");
            continue;
        }
    }
}/*}}}*/

int words_query_menu(int sockfd)	
{
/*{{{*/
    link_list_t * history_list = NULL;
    history_list = list_Head_Init();
    int cmd = 0;
    system("clear");
    printf("\n恭喜您，登陆成功!\n");
    putchar('\n');
    while(1)
    {
        printf("\t-----------------------------------------------\n");
        printf("\t|    [1] 单词查询                             |\n");
        printf("\t|    [2] 修改单词                             |\n");
        printf("\t|    [3] 查询历史                             |\n");
        printf("\t|    [4] 退出查询                             |\n");
        printf("\t-----------------------------------------------\n");
        printf("\n\n请选择>");
        scanf("%d",&cmd);
        //吃掉回车键
        getchar();
        system("clear");
        switch (cmd)
        {
        case QUERY: 
            if( words_query(history_list,sockfd) == 0 )
                ;
            break;

        case MODIFY: 
            if( words_add2dict_menu(sockfd) == 0 )
                ;
            break;

        case HISTORY: 
            history(history_list);
            printf("\npress any key to continue\n");
            getchar();
            system("clear");
            break;

        case EXIT: 
            free_list(history_list);
            //getchar();
            system("clear");
            return 0;
            //break;

        default :
            printf("invalid cmd\n");
            continue;

        }
    }/*}}}*/
}

int do_register_log(int sockfd,enum menue select)
{
/*{{{*/ // get user name passwd from stdin and send to server

	int n = 0;
    int count = 0;
	char buf[1024] = {0};
	//定义发送的协议头
	mhead_t *head = (mhead_t *)buf;
	printf("\n请输入用户名和密码\n");
    //head->type = (select == REGISTER ? USER_REGISTER :  USER_LOGIN);
    int msgtyparry[] = {USER_REGISTER,USER_LOGIN,USER_LOGOFF,};

    head->type = msgtyparry[select-1] ;
    //printf("select : %d\n",select);
    //printf("head->type R10 L20 %d\n",head->type);

    head->size = sizeof(mhead_t);

	printf("Input username : ");
	fgets(head->username,sizeof(head->username),stdin);
	head->username[strlen(head->username) - 1] = '\0';

	printf("Input password : ");
	fgets(head->password,sizeof(head->password),stdin);
	head->password[strlen(head->password) - 1] = '\0';
    
    system("clear");
	//发给服务器端
    //printf("request sending\n");
	if(send(sockfd,buf,sizeof(mhead_t),0) < 0)
	{
		perror("Fail to send");
		exit(EXIT_FAILURE);
	}
	bzero(&buf,sizeof(buf));

/*}}}*/

/*{{{*/ // deal with the response from server 
	while(1)
	{
		//接收数据，TCP是可靠的连接，若是数据
		//未完全接收的话，可以在接收
        //printf("waiting for response\n");
		n = recv(sockfd,buf + count,sizeof(mhead_t) - count,0);

		if(n <= 0){
			perror("Fail to recv");
			exit(EXIT_FAILURE);
		}
		//若是数据未发送完成，再次接收的时候可补充
        //printf("msg recvd\n");
		count += n;
		if(count == sizeof(mhead_t))
			break;
	}

	if(head->type == USER_SUCCESS)
	{
        switch (msgtyparry[select-1])
        {
        case USER_REGISTER:
               printf("\n恭喜您，注册成功!\n");
               return 0;
               //break

        case USER_LOGIN:
               printf("\n恭喜您，登陆成功!\n");
               if( words_query_menu(sockfd) == -1)	
                   return -1;
               break;

        case USER_LOGOFF:
            printf("\n注销成功!\n");
            return 0;
            //break;
        default :
            return 0;
            //break;
        }

		return 0;
	}else{
        switch (msgtyparry[select-1])
        {
        case USER_REGISTER:
               printf("\n很遗憾，这个用户名已经被其它用户注册过了，请重新注册\n");
               return 0;
               //break

        case USER_LOGIN:
        case USER_LOGOFF:
		    printf("\n用户名或密码错误，请重新登陆\n");	
            return 0;
            //break;

        default :
            return 0;
            //break;
        }

		return -1;
	}

    /*}}}*/
}

int do_task(int sockfd)
{/*{{{*/
	int cmd;
	while(1)
	{
		//提示界面帮助，用户选择
		help_info1();	

		printf("\n\n请选择>");
		scanf("%d",&cmd);
		//吃掉回车键
		getchar();
        system("clear");
        if( cmd >= 5 || cmd <= 0 )
        {
            printf("invalid cmd\n");
            continue;
        }

		switch(cmd)
		{
			//用户注册，我们先来写注册的函数
			case REGISTER:
		        help_info1();	
				if(do_register_log(sockfd,REGISTER) < 0)
                    ;
					break;
			//用户登陆
			case LOGIN:	
		        help_info1();	
				if(do_register_log(sockfd,LOGIN) < 0)
                    ;
				break;
			case LOGOFF:
		        help_info1();	
                if(do_register_log(sockfd,LOGOFF) < 0)
                    ;
                break;

			case QUIT:
				exit(EXIT_SUCCESS);
                
			default:
				printf("Unknow cmd.\n");
				continue;
		}
	}
	return 0;
}/*}}}*/

//./client ip port 
//由于后面要传递参数，故这里的const省略


int main(int argc, char *argv[])
{
/*{{{*/
    int sockfd;	
	int addr_len = sizeof(struct sockaddr);
	struct sockaddr_in peer_addr;

	if(argc < 3)
	{
		fprintf(stderr,"Usage : %s argv[1].\n",argv[0]);	
		exit(EXIT_FAILURE);
	}

	sockfd = init_tcp(argv[1],argv[2]);/*}}}*/
	do_task(sockfd);

	return 0;
}
