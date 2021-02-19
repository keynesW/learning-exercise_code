#include "head.h"

linkqueue_t *create_empty_linkqueue()
{
	//1.为头结点在堆区分配空间
	linknode_t *head = NULL;
	head = (linknode_t *)malloc(sizeof(linknode_t));

	memset(head,0,sizeof(linknode_t));

	//2.为栈头在堆区分配空间
	linkqueue_t *q = NULL;
	q = (linkqueue_t *)malloc(sizeof(linkqueue_t));

	memset(q,0,sizeof(linkqueue_t));

	q->front = head;
	q->rear = head;

	head->next = NULL;
	return q;
}


//1.判断链式队列是否为空
int is_empty_linkqueue(linkqueue_t *q)
{
	return (q->front == q->rear ? 1 : 0);
}

//2.入队,插入数据
void enter_data_linkqueue(linkqueue_t *q,type_t data)
{
	linknode_t *temp = NULL;

	temp = (linknode_t *)malloc(sizeof(linknode_t));
	temp->data = data;

	//在q->rear结点后插入temp结点
	temp->next = q->rear->next;
	q->rear->next = temp;

	//更新q->rear的值
	q->rear = temp;

	return;
}

//3.出队
type_t delete_data_linkqueue(linkqueue_t *q)
{
	type_t data;
	linknode_t *temp = NULL;

	//1.取出数据
	data = q->front->next->data;

	//2.保存要删除结点的地址
	temp = q->front->next;	

	//3.后一个结点存放到q->front->next中,并释放内存
	q->front->next = temp->next;

	free(temp);

	//4.当所有结点所删除后，更新rear的值
	if(q->front->next == NULL)
		q->rear = q->front;

	return data;
}



