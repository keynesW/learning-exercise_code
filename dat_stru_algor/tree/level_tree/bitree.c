#include "head.h"
//为data这个数据分配内存空间，创建一个新的结点。
btree_t *malloc_node(datatype_t data)
{
	btree_t *tree = NULL;
	tree = (btree_t *)malloc(sizeof(btree_t));


	memset(tree,0,sizeof(btree_t));
	tree->data = data;
	tree->lchild = NULL;
	tree->rchild = NULL;

	return tree;
}

//功能:创建一颗二叉树
//参数:  a----数据存储的数组首地址
//       b----需要取的数据的编号
//       n----元素的总个数               2     6
btree_t *create_binary_tree(datatype_t a[],int num,int n)
{
	btree_t *root = NULL;

	//A
	root = malloc_node(a[num]);

	//1.说明左孩子存在
	if(2 * num <= n)
	{
		root->lchild =  create_binary_tree(a,num * 2,n);
	}

	//2.说明右孩子存在
	if(2 * num + 1 <= n) 
	{
		root->rchild = create_binary_tree(a,num * 2 + 1,n); 	
	}

	return root;
}

//前序遍历:根左右
void preorder(btree_t *root)
{
	//说明当前结点为空,直接返回
	if(root == NULL)
		return ;

	printf("%c ",root->data);
	preorder(root->lchild);
	preorder(root->rchild);

	return;
}

//中序遍历:左根右
void inorder(btree_t *root)
{
	//说明当前结点为空,直接返回
	if(root == NULL)
		return ;

	inorder(root->lchild);
	printf("%c ",root->data);
	inorder(root->rchild);

	return;
}

//后序遍历:左右根
void postorder(btree_t *root)
{
	//说明当前结点为空,直接返回
	if(root == NULL)
		return ;

	postorder(root->lchild);
	postorder(root->rchild);
	printf("%c ",root->data);
}

//层次遍历
void level_travel(btree_t *root)
{

//		(1)创建一个队列
		linkqueue_t *q = create_empty_linkqueue();	

//		(2)然后把根结点入队。
		enter_data_linkqueue(q,root);	

//		(3)循环判断队列是否为空。
        while(!is_empty_linkqueue (q))
        {

//		3.1输出该结点对应的数据
//
            printf("%c ",q->front->next->data->data);

//		3.2然后判断该结点是否有左孩子，若是有让左孩子入队.

            if(q->front->next->data->lchild != NULL)
                enter_data_linkqueue (q,q->front->next->data->lchild);

//		3.3然后判断i亥结点是否有右孩子，若是有让右孩子入队.

            if(q->front->next->data->rchild != NULL)
                enter_data_linkqueue (q,q->front->next->data->rchild);

//		3.4出队该结点，

            delete_data_linkqueue (q);
        }
//		(4)当循环结束后,释放队列的空间--队列头和头节点的空间
        free(q->front);
        free(q);
        q = NULL;
		return ;
}


int main()
{
	//注:为了让数组的下标和二叉数的编号对应,这里默认
	//   下标为0的元素不适用。
	char a[] = {-1,'A','B','C','D','E','F'};
	int n = sizeof(a)/sizeof(a[0]) - 1;

	btree_t *root = NULL;	

	root = create_binary_tree(a,1,n);

	printf("前序遍历 : ");
	preorder(root);
	putchar('\n');

	printf("中序遍历 : ");
	inorder(root);
	putchar('\n');

	printf("后序遍历 : ");
	postorder(root);
	putchar('\n');

	printf("层次遍历 : ");
    level_travel(root);
	putchar('\n');

	return 0;
}









