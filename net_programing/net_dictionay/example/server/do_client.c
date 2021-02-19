#include "head.h" 

int do_register(int sockfd,sqlite3 *pdb,char *_username,char *_password)
/*{{{*/
{
    printf("do register\n");
	char *errmsg;
	char buf[1024];
	char **dbresult;
	int nrow = 0,ncolumn = 0;
	char sql[1024] = {0};
	mhead_t *head = (mhead_t *)buf;	
	

	//查询用户名是否存在
	sprintf(sql,"select * from user_table where NAME='%s';",_username);
	if(sqlite3_get_table(pdb,sql,&dbresult,&nrow,&ncolumn,&errmsg) != 0)
	{
		fprintf(stderr,"sqlite3 get table error : %s.\n",errmsg);
		exit(EXIT_FAILURE);
	}

	//没有这样的用户名
	if(nrow == 0)
	{
		//录入数据库
		bzero(sql,sizeof(sql));
		sprintf(sql,"insert into user_table values('%s','%s');",_username,_password);
		EXEC_SQL(pdb,sql,errmsg);
		
		printf("ok ........\n");
		
		//封装一个应答包给客户端
		head->type = USER_SUCCESS;
		if(send(sockfd,buf,sizeof(mhead_t),0) < 0)
		{
			perror("Fail to send");
			exit(EXIT_FAILURE);
		}
	//注册失败，用户名存在
	}else{
		head->type = USER_FAILURE;
		if(send(sockfd,buf,sizeof(mhead_t),0) < 0)
		{
			perror("Fail to send");
			exit(EXIT_FAILURE);
		}
		//表示未知	
		printf("???????\n");
	}
	//插入到数据库之后，释放dbresult结果
	sqlite3_free_table(dbresult);
	return 0;
}/*}}}*/

int delete_cunt(sqlite3 *pdb,const char *_username,const char *_password)
/*{{{*/
{
	char *errmsg;
	char **dbresult;
	int nrow = 0,ncolumn = 0;
	char sql[1024] = {0};

    sprintf(sql,"delete from user_table where NAME='%s' and PASSWORD='%s';",_username,_password);
    if(sqlite3_get_table(pdb,sql,&dbresult,&nrow,&ncolumn,&errmsg) != 0)
    {
        fprintf(stderr,"sqlite3 get table error : %s.\n",errmsg);
        exit(EXIT_FAILURE);
    }

}/*}}}*/

int do_log(int sockfd,sqlite3 *pdb,const char *_username,const char *_password,int select)
{
/*{{{*/
    printf("do log\n");
	char *errmsg;
	char buf[1024];
	char **dbresult;
	int nrow = 0,ncolumn = 0;
	char sql[1024] = {0};
	mhead_t *head = (mhead_t *)buf;	

	//查询用户名是否存在
	sprintf(sql,"select * from user_table where NAME='%s' and PASSWORD='%s';",_username,_password);
	if(sqlite3_get_table(pdb,sql,&dbresult,&nrow,&ncolumn,&errmsg) != 0)
	{
		fprintf(stderr,"sqlite3 get table error : %s.\n",errmsg);
		exit(EXIT_FAILURE);
	}

    printf("row : %d, column : %d\n",nrow,ncolumn);
	//没有这样的用户名
	if(nrow == 0)
	{
		bzero(buf,sizeof(buf));
		head->type = USER_FAILURE;
        head->size = sizeof(mhead_t);
        strcpy( head->word,"用户名或密码错误");
		
		//封装一个应答包给客户端
		if(send(sockfd,buf,sizeof(mhead_t),0) < 0)
		{
			perror("Fail to send");
			exit(EXIT_FAILURE);
		}
	}else{

		bzero(buf,sizeof(buf));
		head->type = USER_SUCCESS;
        head->size = sizeof(mhead_t);
        strcpy( head->word,"成功");

        if( select == USER_LOGOFF )
            delete_cunt(pdb,_username,_password);

		if(send(sockfd,buf,sizeof(mhead_t),0) < 0)
		{
			perror("Fail to send");
			exit(EXIT_FAILURE);
		}

        printf("end of do log\n");
        if( select == USER_LOGIN )
	        return 1;

	}
	return 0;
	//插入到数据库之后，释放dbresult结果
	//sqlite3_free_table(dbresult);
/*}}}*/
}
int do_word_query(int sockfd,sqlite3 *pdb,const char *_word,int authent)
{
/*{{{*/ 
    printf(" do word query \n");
	char *errmsg;
	char buf[1024];
	char **dbresult;
	int nrow = 0,ncolumn = 0;
	char sql[1024] = {0};
	mhead_t *head = (mhead_t *)buf;	

    if (authent == 0)
    {
        printf("authent : %d\n",authent);
		bzero(buf,sizeof(buf));

		head->type = USER_FAILURE;
        head->size = sizeof(mhead_t);
        strcpy( head->word,"非法用户查询");
		
		//封装一个应答包给客户端
		if(send(sockfd,buf,sizeof(mhead_t),0) < 0)
		{
			perror("Fail to send");
			exit(EXIT_FAILURE);
		}
        return 0;
    }
    
	sprintf(sql,"select * from dict_table where word='%s' ;",_word);
	if(sqlite3_get_table(pdb,sql,&dbresult,&nrow,&ncolumn,&errmsg) != 0)
	{
		fprintf(stderr,"sqlite3 get table error : %s.\n",errmsg);
		exit(EXIT_FAILURE);
	}

	if(nrow == 0)
	{
		//录入数据库
		bzero(buf,sizeof(buf));
		head->type = USER_FAILURE;
        head->size = sizeof(mhead_t);
        strcpy( head->word,"对不起，你所查询的单词不存在，请检查拼写");
		
		//封装一个应答包给客户端
		if(send(sockfd,buf,sizeof(mhead_t),0) < 0)
		{
			perror("Fail to send");
			exit(EXIT_FAILURE);
		}
        return 0;
	}else{
		bzero(buf,sizeof(buf));
		head->type = USER_SUCCESS;
        head->size = sizeof(mhead_t);
/*{{{*/
/////////////////////////////////////////////////////////////////////////////////////
        int index = 0;
        int strlength = 0;
        //printf("row : %d, column : %d\n",nrow,ncolumn);
        for(int i = 0; i <= nrow; i++)
        {
            for(int j = 0 ; j < ncolumn; j++)
            {
                //printf("database consult result : %s\n",dbresult[index]);
                strcpy( &head->word[strlength],dbresult[index ++]);
                strlength = strlen(head->word);

                head->word[strlength] = '\t';
                strlength++;
                head->word[strlength] = '\t';
                strlength++;
                //封装一个应答包给客户端
            }
            head->word[strlength] = '\n';
            strlength++;
        }
        printf("database consult result : \n%s\n",head->word);
/////////////////////////////////////////////////////////////////////////////////////
/*}}}*/
        if(send(sockfd,buf,sizeof(mhead_t),0) < 0)
        {
            perror("Fail to send");
            exit(EXIT_FAILURE);
        }
    }

    printf("end of  do word query \n");
    return 1;
    /*}}}*/
}

int words_modify_dict(int sockfd,sqlite3 *pdb,const char * _word,\
            int authentication,int cmd)
{/*{{{*/

    if( do_word_query(sockfd,pdb,_word,authentication) )
        ;
        //单词存在
/*         
    int n = 0;
    int count = 0;
    char buf[1024] = {0};
    mhead_t *head = (mhead_t *)buf;
    while(1)
    {
        n = recv(sockfd,buf,sizeof buf);
        if( n <=0 )
        {
            perror("recv()");
            exit(EXIT_FAILURE);
        }
        count += n;
        if (count == sizeof (mhead_t))
        {
            coutn = 0;
            break;
        }
    }

*/
}/*}}}*/

int Unknow_msg_respone(int sockfd)
/*{{{*/
{
	    char buf[1024];
	    mhead_t *head = (mhead_t *)buf;	//
		head->type = USER_FAILURE;
        head->size = sizeof(mhead_t);
        strcpy( head->word,"错误");
		
		//封装一个应答包给客户端
		if(send(sockfd,buf,sizeof(mhead_t),0) < 0)
		{
			perror("Fail to send");
			exit(EXIT_FAILURE);
		}
        printf("Unknow msg response\n");
}/*}}}*/

int do_client(int sockfd,sqlite3 *pdb)
{
/*{{{*/
	int n;
	int count = 0;
	char buf[1024];
	//强制转换成结构体指针，方便访问协议内容
	mhead_t *head = (mhead_t *)buf;	//
    int authentication = 0;
	while(1)
	{
		count = 0;
		//接收协议头,保证接收的数据完整型
		while(1)
		{/*{{{*/
			n = recv(sockfd,buf + count,sizeof(mhead_t) - count,0);
			if(n <= 0){
				exit(EXIT_FAILURE);
			}

			count += n;
			printf("msg recvd count : %d mhead_t : %zd head->type : %d\n",count,sizeof(mhead_t),head->type);
			if(count == sizeof(mhead_t))
				break;
		}/*}}}*/
        printf("msg recvd, switch to process %s\n",head->word);
		
		//解析数据包
		switch(head->type)
		{
		case USER_REGISTER:
			do_register(sockfd,pdb,head->username,head->password);	
			break;
		case USER_LOGIN:
            authentication = do_log(sockfd,pdb,head->username,head->password,USER_LOGIN);
            break;
		case USER_WORD:
            do_word_query(sockfd,pdb,head->word,authentication);
			break;
		case USER_LOGOFF:
            do_log(sockfd,pdb,head->username,head->password,USER_LOGOFF);
			break;

		case USER_ADD:
            if( words_modify_dict( sockfd,pdb,head->word,authentication,USER_ADD) == 0 )
                ;
			break;
		case USER_DELETE:
            if( words_modify_dict( sockfd,pdb,head->word,authentication,USER_DELETE) == 0 )
                ;
            break;

        default :
            Unknow_msg_respone(sockfd);
            printf("Unknow msg\n");
			break;
			//exit(EXIT_SUCCESS);
		}	
	}
    return 0;
	/*}}}*/
}

