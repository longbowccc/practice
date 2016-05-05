#include "zlog.h"
#include "tree_node.h"
#include <string.h>

/*
 * create a tree node
 */
t_tree_node* create_tree_node(void *data) {
    t_tree_node *p = malloc(sizeof(t_tree_node));
    if (!p) {
        zlog("fail to alloc %d of memory", sizeof(t_tree_node));
        return NULL;
    }
    memset(p, 0, sizeof(t_tree_node));
    p->data = data;
    return p;
}

/*
 * free a tree node
 */
void free_tree_node(t_tree_node *node) {
    t_tree_node *child, *tmp;
    if (node) {
        // free children if exists
        child = node->first_child;
        while (child) {
            tmp = child;
            child = child->next_sibling;
            free_tree_node(tmp);
        }
        free(node);
    }
}

/*
 * add a child
 */
void tn_add_child(t_tree_node *parent, t_tree_node *node) {
    t_tree_node *sibling = parent->first_child, *prev_sibling=0;
    node->parent = parent;
    node->prev_sibling = NULL;
    node->next_sibling = NULL;
    while (sibling) {
        prev_sibling = sibling;
        sibling = sibling->next_sibling;
    }
    if (prev_sibling) {
        prev_sibling->next_sibling = node;
        node->prev_sibling = prev_sibling;
    }
    if (!parent->first_child) {
        parent->first_child = node;
    }
    parent->nchild++;
}

/*
 * remove a child
 */
int tn_del_child(t_tree_node *parent, t_tree_node *node) {
    t_tree_node *sibling = parent->first_child, *prev_sibling=0;
    int deleted = 0;
    while (sibling) {
        if (sibling == node) {
            if (node->prev_sibling) {
                node->prev_sibling->next_sibling = node->next_sibling;
            } else {
                parent->first_child = node->next_sibling;
            }
            if (node->next_sibling) {
                node->next_sibling->prev_sibling = node->next_sibling;
            }
            node->parent = NULL;
            deleted = 1;
            parent->nchild--;
            break;
        }
        prev_sibling->next_sibling = node;
        sibling = sibling->next_sibling;
    }

    return deleted;
}
