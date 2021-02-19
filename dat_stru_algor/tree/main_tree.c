#include<stdio.h>
//#include"tree.h"
#include<string.h>
#include<stdlib.h>

typedef char data_t;
typedef struct btree{

    struct btree *lchild;
    data_t data;
    struct btree *rchild;

}btree_t;

btree_t * create_tree_node(data_t data)
{
    btree_t * tree = NULL;
    tree = (btree_t *) malloc (sizeof (btree_t));
    memset(tree,0,sizeof (btree_t));

    tree->data = data;
    tree->lchild = NULL;   
    tree->rchild = NULL;

    return tree;
}


btree_t * create_tree(data_t *a ,int num,int n)
{
     btree_t *root = NULL; 
     root = create_tree_node(a[num]);

     if( 2 * num <= n)
     {
          root->lchild =   create_tree(a,2*num,n);
     }
     if( 2*num +1 <= n)
     {
          root->rchild = create_tree(a,2*num+1,n);
     }
        return root;
}

void preorder(btree_t *root)
{
    if( root == NULL )
        return ;
    printf("%c",root->data);
    preorder(root->lchild);
    preorder(root->rchild);

}
void inorder(btree_t *root)
{
    if( root == NULL )
        return ;
    inorder(root->lchild);
    printf("%c",root->data);
    inorder(root->rchild);

}
void postorder(btree_t *root)
{
    if( root == NULL )
        return ;
    postorder(root->lchild);
    postorder(root->rchild);
    printf("%c",root->data);
}
int main()
{
    
    char a[] = {-1,'a','b','c','d','e','f'};
    btree_t * root = NULL;
    root = create_tree(a,1,6); 

    printf("preorder : \n");
    preorder(root);
    putchar('\n');

    printf("inorder : \n");
    inorder(root);
    putchar('\n');

    printf("postorder : \n");
    postorder(root);
    putchar('\n');

    return 0;
}
