#include "zlog.h"
#include "tree.h"

void fill_tree(t_tree *tree);

int main(int argc, char *argv[]) {
    zlog("HElLO");
    t_tree_node *root = create_tree_node((void*)1);
    t_tree *tree = create_tree(root);
    fill_tree(tree);
    print_tree(tree);
    free_tree(tree);
    return 0;
}

/*
 * fill tree with some elements
 */
void fill_tree(t_tree *tree) {
    t_tree_node *root = tree->root;
    t_tree_node *c1, *c2, *c3;
    tn_add_child(root, (c1=create_tree_node((void*)11)));
    tn_add_child(root, (c2=create_tree_node((void*)12)));
    tn_add_child(root, (c3=create_tree_node((void*)13)));
    tn_add_child(c1, create_tree_node((void*)111));
    tn_add_child(c1, create_tree_node((void*)112));
    tn_add_child(c1, create_tree_node((void*)113));
    tn_add_child(c2, create_tree_node((void*)121));
    tn_add_child(c3, create_tree_node((void*)131));
}
