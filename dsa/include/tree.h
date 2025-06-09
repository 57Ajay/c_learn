#ifndef TREE
#define TREE

#include <stdint.h>
typedef struct BTreeNode {
    void *data;
    struct BTreeNode *left;
    struct BTreeNode *right;
    int height;
} BTreeNode;

int BTMain();

BTreeNode *create_BT_node(void *data, uint8_t element_size);
BTreeNode *create_Simple_BTree(void *arr, int count, uint8_t element_size);
void printPreorder(BTreeNode *root);
void printInorder(BTreeNode *root);
void printPostorder(BTreeNode *root);
void printLevelOrder(BTreeNode *root);
void printTreeVisual(BTreeNode *root, int space);
void destroy_simple_BTree(BTreeNode *root);
BTreeNode *insert_BST(BTreeNode *root, void *data, uint8_t elem_size,
                      int (*cmp)(void *, void *));
BTreeNode *create_BST(void *arr, int count, uint8_t elem_size,
                      int (*cmp)(void *, void *));
int compare_int(void *a, void *b);
BTreeNode *search_BST(BTreeNode *root, void *key, int (*cmp)(void *, void *));
int height_BST(BTreeNode *root);
int count_nodes(BTreeNode *root);
int count_leaves(BTreeNode *root);
BTreeNode *find_min(BTreeNode *root);
BTreeNode *delete_BST(BTreeNode *root, void *key, uint8_t elem_size,
                      int (*cmp)(void *, void *));
void test_search(BTreeNode *root, int key);
int get_height(BTreeNode *node);
int get_balance(BTreeNode *node);
int maxVal(int a, int b);
BTreeNode *right_rotate(BTreeNode *y);
BTreeNode *left_rotate(BTreeNode *x);
BTreeNode *insert_AVL(BTreeNode *root, void *data, uint8_t elem_size,
                      int (*cmp)(void *, void *));
BTreeNode *create_AVL(void *arr, int count, uint8_t elem_size,
                      int (*cmp)(void *, void *));

#endif
