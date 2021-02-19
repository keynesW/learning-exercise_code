#ifndef _HEAD_H_
#define _HEAD_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//====================
//二叉树节点的信息

typedef char datatype_t; //二叉树的数据类型

typedef struct bnode{
	datatype_t data; //二叉树的数据
	struct bnode *lchild; //左孩子的地址
	struct bnode *rchild; //右孩子的地址
}btree_t;


//===============
//队列的信息
//1.用户自定义数据类型
typedef btree_t * type_t;

//2.结点的类型
typedef struct node{
	type_t data;
	struct node *next;
}linknode_t;

//3.栈头的类型
typedef struct{
	linknode_t *front;
	linknode_t *rear;
}linkqueue_t;

extern linkqueue_t *create_empty_linkqueue();
extern int is_empty_linkqueue(linkqueue_t *q);
extern void enter_data_linkqueue(linkqueue_t *q,type_t data);
extern type_t delete_data_linkqueue(linkqueue_t *q);



#endif
