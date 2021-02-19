#ifndef _TREE_HEAD_
#define _TREE_HEAD_


typedef int data_t;

typedef struct tree_node{

    struct tree_node * L_child;
    data_t data;
    struct tree_node * R_child;

    }tree_node_stl;

extern InsertChild();
extern DeleteChild();
extern recursive_ergodic();
#endif

