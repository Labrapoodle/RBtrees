#include <stdlib.h>
#include "rbtree.h"

struct rbtree *rbtree_create_node(int key, char *value)
{
    struct rbtree *var = (struct rbtree *)malloc(sizeof(struct rbtree));
    var->root = NULL;
    var->parent = NULL;
    var->left = NULL;
    var->right = NULL;
    var->key = key;
    var->color = 'r';
    var->value = value;
    return var;
}
struct rbtree *rbtree_add(struct rbtree *root, int key, char *value)
{
    struct rbtree *tree = root;
    while (tree != NULL)
    {
        if (key < tree->key)
        {
            tree = tree->left;
        }
        else if (key > tree->key)
        {
            tree = tree->right;
        }
        else
            return tree;
    }

    struct rbtree *node = rbtree_create_node(root, key, value);
    if (root == NULL)
    {
        root = node;
    }
    else if (key < tree->parent->key)
    {
        tree->parent->left = node;
    }
    else
    {
        tree->parent->right = node;
    }
    node->color = 'r';
    return node;
}
