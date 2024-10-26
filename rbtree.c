#include <stdlib.h>
#include <stdio.h>
#include "rbtree.h"

struct rbtree NIL = {NULL, NULL, NULL, NULL, 'b', 0, 'k'};

void rbtree_left_rotate(struct rbtree *node)
{
    struct rbtree *rightAccesor = node->right;
    node->right = rightAccesor->left;
    if (rightAccesor->left != &NIL)
    {
        rightAccesor->left->parent = node;
    }
    rightAccesor->parent = node->parent;
    if (node == node->parent->left)
    {
        node->parent->left = rightAccesor;
    }
    else
    {
        node->parent->right = rightAccesor;
    }
    rightAccesor->left = node;
    node->parent = rightAccesor;
}
void rbtree_right_rotate(struct rbtree *node)
{
    struct rbtree *leftAccesor = node->left;
    node->left = leftAccesor->right;
    if (leftAccesor->right != &NIL)
    {
        leftAccesor->right->parent = node;
    }
    leftAccesor->parent = node->parent;
    if (node == node->parent->left)
    {
        node->parent->left = leftAccesor;
    }
    else
    {
        node->parent->right = leftAccesor;
    }
    leftAccesor->right = node;
    node->parent = leftAccesor;
}

struct rbtree *rbtree_create_node(int key, char value)
{
    struct rbtree *var = (struct rbtree *)malloc(sizeof(struct rbtree));

    var->root = &NIL;
    var->parent = &NIL;
    var->left = &NIL;
    var->right = &NIL;
    var->key = key;
    var->color = 'r';
    var->value = value;
    /*
    var->root = NULL;
    var->parent = NULL;
    var->left = NULL;
    var->right = NULL;
    var->key = key;
    var->color = 'r';
    var->value = value;
    */
    return var;
}
void rbtree_add_fixup(struct rbtree *root, struct rbtree *node)
{
    struct rbtree *uncle;

    while (node->parent->color == 'r')
    {

        if (node->parent == node->parent->parent->left)
        {

            uncle = node->parent->parent->right;

            // Case 1
            if (uncle->color == 'r')
            {
                node->parent->color = 'b';
                uncle->color = 'b';
                node->parent->parent->color = 'r';
                node = node->parent->parent;
            }
            else
            {
                // Case 2
                if (node == node->parent->right)
                {
                    node = node->parent;
                    rbtree_left_rotate(node);
                }
                // Case 3
                node->parent->color = 'b';
                node->parent->parent->color = 'r';
                rbtree_right_rotate(node->parent->parent);
            }
        }
        else if (node->parent == node->parent->parent->right)
        {
            uncle = node->parent->parent->left;
            if (uncle->color == 'r')
            {
                node->parent->color = 'b';
                uncle->color = 'b';
                node->parent->parent->color = 'r';
                node = node->parent->parent;
            }
            else
            {
                if (node == node->parent->left)
                {
                    node = node->parent;
                    rbtree_right_rotate(node);
                }
                node->parent->color = 'b';
                node->parent->parent->color = 'r';
                rbtree_left_rotate(node->parent->parent);
            }
        }
        else
        {
            node->parent->color = 'b';
        }
    }
    node = find_root(node);
    if (node != NULL)
    {
        node->color = 'b';
    }
}
struct rbtree *rbtree_add(struct rbtree *root, int key, char value)
{
    struct rbtree *tree = root;
    struct rbtree *p = NULL;
    while (tree != &NIL)
    {
        p = tree;
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
    else if (key < p->key)
    {

        p->left = node;
    }
    else
    {

        p->right = node;
    }
    node->parent = p;
    node->color = 'r';

    rbtree_add_fixup(root, node);

    return node;
}

struct rbtree *rbtree_lookup(struct rbtree *root, int key)
{
    while (root != &NIL)
    {
        if (key == root->key)
        {

            return root;
        }
        else if (key < root->key)
        {
            root = root->left;
        }
        else if (key > root->key)
        {
            root = root->right;
        }
    }
    return root;
}

void rbtree_transplant(struct rbtree *root, struct rbtree *old_node, struct rbtree *new_node)
{
    if (old_node->parent == &NIL)
    {
        root = new_node;
    }
    else if (old_node == old_node->parent->left)
    {
        old_node->parent->left = new_node;
    }
    else
    {
        old_node->parent->right = new_node;
    }
    new_node->parent = old_node->parent;
}
void rbtree_delete(struct rbtree *root, int key)
{
    struct rbtree *node = rbtree_lookup(root, key);
    struct rbtree *copyNode = node;
    // struct rbtree *copyNode = rbtree_create_node(key, node->value);
    struct rbtree *accessor;
    char copyNode_origin_color = copyNode->color;
    if (node->left == &NIL)
    {

        accessor = node->right;
        rbtree_transplant(root, node, node->right);
    }
    else if (node->right == &NIL)
    {
        accessor = node->left;
        rbtree_transplant(root, node, node->left);
    }

    else
    {

        copyNode = rbtree_min(node->right);

        copyNode_origin_color = copyNode->color;

        accessor = copyNode->right;

        if (copyNode->parent == node)
        {
            accessor->parent = copyNode;
        }

        else
        {
            rbtree_transplant(root, copyNode, copyNode->right);
            copyNode->right = node->right;
            copyNode->right->parent = copyNode;
        }

        rbtree_transplant(root, node, copyNode);
        copyNode->left = node->left;
        copyNode->left->parent = copyNode;
        copyNode->color = node->color;
        if (copyNode_origin_color == 'b')
        {
            rbtree_delete_fixup(root, node);
        }
    }

    free(node);
}
void rbtree_delete_fixup(struct rbtree *root, struct rbtree *node)
{
    struct rbtree *sibling;
    while (node != root && node->color == 'b')
    {

        if (node == node->parent->left)
        {
            sibling = node->parent->right;
            if (sibling->color == 'r')
            {
                sibling->color = 'b';
                node->parent->color = 'r';
                rbtree_left_rotate(node->parent);
                sibling = node->parent->right;
            }
            if (sibling->left->color == 'b' && sibling->right->color == 'b')
            {
                sibling->color = 'r';
                node = node->parent;
            }
            else
            {
                if (sibling->right->color == 'b')
                {
                    sibling->left->color = 'b';
                    sibling->color = 'r';
                    rbtree_right_rotate(sibling);
                    sibling = node->parent->right;
                }
                sibling->color = node->parent->color;
                node->parent->color = 'b';
                sibling->right->color = 'b';
                rbtree_left_rotate(node->parent);
                node = root;
            }
        }
        else
        {
            sibling = node->parent->left;
            if (sibling->color == 'r')
            {
                sibling->color = 'b';
                node->parent->color = 'r';
                rbtree_right_rotate(node->parent);
                sibling = node->parent->left;
            }
            if (sibling->left->color == 'b' && sibling->right->color == 'b')
            {
                sibling->color = 'r';
                node = node->parent;
            }
            else
            {
                if (sibling->left->color == 'b')
                {
                    sibling->right->color = 'b';
                    sibling->color = 'r';
                    rbtree_left_rotate(sibling);
                    sibling = node->parent->left;
                }
                sibling->color = node->parent->color;
                node->parent->color = 'b';
                sibling->left->color = 'b';
                rbtree_right_rotate(node->parent);
                node = root;
            }
        }
    }
    node->color = 'b';
}

int rbtree_print_dfs(struct rbtree *root, int level)
{
    struct rbtree *node = rbtree_lookup(root, level);
    struct rbtree *origin_node = node;
    struct rbtree *origin_node_right = node->right;
    node->right = &NIL;

    while (node == node->parent->right)
    {
        node = node->parent;
    }

    int node_height = rbtree_height(node);

    // here
    origin_node->right = origin_node_right;

    return node_height;
    /*
    if (node == &NIL || node == NULL)
    {
        printf("NILorNULL\n");
        return -1;
    }
    if (level <= root->key)
    {
        if (node->left != &NIL)
        {
            node = node->left;

        }
        else
        {
            printf("NILv2\n");
            return -2;
        }
    }
    return -3;
    */
}

void tree_traverse_in_order(struct rbtree *root)
{
    if (root != &NIL)
    {
        tree_traverse_in_order(root->left);
        tree_traverse_in_order(root->right);
    }
}
void rbtree_free(struct rbtree *root)
{
    if (root != &NIL)
    {
        rbtree_free(root->left);
        rbtree_free(root->right);
        free(root);
    }
}

int rbtree_height(struct rbtree *root)
{
    if (root == &NIL)
    {
        return 0;
    }
    int leftHeight = rbtree_height(root->left);
    int rightHeight = rbtree_height(root->right);
    int height = (leftHeight > rightHeight) ? leftHeight : rightHeight;
    return height + 1;
}

struct rbtree *rbtree_min(struct rbtree *root)
{
    while (root->left != &NIL)
    {
        root = root->left;
    }
    return root;
}
struct rbtree *rbtree_max(struct rbtree *root)
{
    while (root->right != &NIL)
    {
        root = root->right;
    }
    return root;
}

struct rbtree *find_root(struct rbtree *node)
{
    if (node == NULL)
    {
        return NULL;
    }
    while (node->parent != &NIL)
    {
        node = node->parent;
    }
    return node;
}

int check_for_color(struct rbtree *root)
{
    if (root->left == &NIL && root->right == &NIL)
    {
        return 0;
    }
    int counter = 0;
    if (root->color == 'r')
    {
        if (root->left->color == 'r' || root->right->color == 'r')
        {
            counter++;
        }
    }
    if (root->left != &NIL)
    {
        if (check_for_color(root->left))
        {
            counter++;
        }
    }
    if (root->right != &NIL)
    {
        if (check_for_color(root->right))
        {
            counter++;
        }
    }
    return counter;
}
int rbtree_black_height(struct rbtree *root)
{
    if (root == &NIL)
    {
        return 0;
    }
    int leftHeight = rbtree_black_height(root->left);
    int rightHeight = rbtree_black_height(root->right);
    int height = (leftHeight > rightHeight) ? leftHeight : rightHeight;
    if (root->color == 'b')
    {
        height++;
    }
    return height;
}
