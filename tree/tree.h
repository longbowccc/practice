#ifndef _TREE_H
#define _TREE_H

#include "tree_node.h"

typedef struct _tree {
    struct _tree_node *root;
} t_tree;

t_tree* create_tree();

void free_tree(t_tree*);

void print_tree(t_tree*);

void tree_init(t_tree_node*);

#endif

/* end of file tree.h */
