#ifndef _TREE_NODE_H
#define _TREE_NODE_H

typedef struct _tree_node {
    struct _tree_node* parent;
    struct _tree_node* first_child;
    struct _tree_node* next_sibling;
    struct _tree_node* prev_sibling;
    unsigned nchild;
    void *data;
}t_tree_node;

t_tree_node* create_tree_node(void*);
void free_tree_node(t_tree_node*);

void tn_add_child(t_tree_node*, t_tree_node*);
int tn_del_child(t_tree_node*, t_tree_node*);

#endif

/* end of file tree_node.h */
