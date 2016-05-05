#include "zlog.h"
#include "tree_node.h"
#include "tree.h"
#include <string.h>
#include <stdio.h>

void print_tree_node(t_tree_node *tree, int depth);

t_tree* create_tree(t_tree_node *root) {
    t_tree *p = malloc(sizeof(t_tree));
    if (!p) {
        zlog("fail to malloc %d bytes", sizeof(t_tree));
        return NULL;
    }
    memset(p, 0, sizeof(t_tree));
    p->root = root;
    return p;
}

void free_tree(t_tree *tree) {
    if (tree) {
        if (tree->root) {
            free_tree_node(tree->root);
        }
        memset(tree, 0, sizeof(t_tree));
        free(tree);
    }
}

void print_tree(t_tree *tree) {
    t_tree_node *root = tree->root;
    if (!root) {
        zlog("empty tree");
        return;
    }
    print_tree_node(root, 0);
}

void print_tree_node(t_tree_node *node, int depth) {
    int i;
    t_tree_node *child;
    for (i=0;i<depth;i++) {
        printf("  ");
    }
    printf("%d\n", (long)node->data);
    child = node->first_child;
    while (child) {
        print_tree_node(child, depth+1);
        child = child->next_sibling;
    }
    
}
