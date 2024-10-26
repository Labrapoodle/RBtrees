#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "rbtree.h"
#define MAX_AMOUNT 50000

int main()
{

    FILE *f = fopen("data2.txt", "w");
    int level_height;
    double expected;
    struct rbtree *T = rbtree_create_node(1, 'k');
    struct rbtree *root = find_root(T);
    for (int i = 2; i < MAX_AMOUNT; i++)
    {
        root = find_root(T);
        rbtree_add(root, i, 'a');
        root = find_root(T);

        level_height = rbtree_height(root);
        printf("%d\n", i);
        expected = 2 * log(i + 1) / log(2);
        fprintf(f, "%d\t%d\t%f\n", i, level_height, expected);
    }

    root = find_root(T);

    /*
    for (int i = 1; i < MAX_AMOUNT; i++)
    {
        level_height = rbtree_print_dfs(root, i);
        expected = 2 * log(i + 1) / log(2);
        printf("%d\t%d\t%f\n", i, level_height, expected);
    }
    */

    // double val = 2 * log(MAX_AMOUNT + 1) / log(2);

    rbtree_free(T);
    fclose(f);
    printf("new\n");
    return 0;
}
