#pragma once

extern struct rbtree NIL;

struct rbtree
{
    struct rbtree *root;
    struct rbtree *parent;
    struct rbtree *left;
    struct rbtree *right;
    char color;
    int key;
    char value;
};

// struct rbtree NIL = {NULL, NULL, NULL, NULL, 'b', 0, 'k'};

void rbtree_transplant(struct rbtree *root, struct rbtree *old_node, struct rbtree *new_node);
void rbtree_left_rotate(struct rbtree *node);
void rbtree_right_rotate(struct rbtree *node);
void rbtree_add_fixup(struct rbtree *root, struct rbtree *node);
void rbtree_delete_fixup(struct rbtree *root, struct rbtree *node);
void tree_traverse_in_order(struct rbtree *root);
int rbtree_height(struct rbtree *root);

struct rbtree *rbtree_add(struct rbtree *root, int key, char value);
struct rbtree *rbtree_create_node(int key, char value);
struct rbtree *rbtree_lookup(struct rbtree *root, int key);
void rbtree_delete(struct rbtree *root, int key);
struct rbtree *rbtree_min(struct rbtree *root);
struct rbtree *rbtree_max(struct rbtree *root);
void rbtree_free(struct rbtree *root);
int rbtree_print_dfs(struct rbtree *root, int level);

struct rbtree *find_root(struct rbtree *node);
int check_for_color(struct rbtree *root);
int rbtree_black_height(struct rbtree *root);
