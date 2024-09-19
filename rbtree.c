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
struct rbtree *rbtree_add(struct rbtree *root, 
                             int key, char *value)
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

    struct rbtree *node = rbtree_create_node(key, value);
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

struct rbtree *rbtree_lookup(struct rbtree *root, int key){
    while(root!=NULL){
        if(key==root->key){
            return root;
        }
        else if(key<root->key){
            root = root->left;
        }
        else if(key>root->key){
            root = root->right;
        }
    }
    return root;
}

void rb_transplant(struct rbtree *root, struct rbtree *old,
                     struct rbtree *new)
{
    if(u->parent==NULL){
        root = new;
    }
    else if(old==old->parent->left){
        old->parent->left=new;
    }
    else if(old == old->parent->right){
        old->parent->right = new;
    }
    new->parent = old->parent;
}

struct rbtree *rbtree_delete(struct rbtree *root, int key)
{
    struct rbtree *node = rbtree_lookup(root,key);
    struct rbtree *newNode = node;
    struct rbtree *x;
    char new_origin_color = newNode->color;
    if(node->left==NULL)x = node->right;
    
    if(node->right==NULL)  x = node->left;
    
    else{
        newNode = rbtree_min(node->right);
        new_origin_color = newNode->color;
        x = newNode->right;

    }
}    