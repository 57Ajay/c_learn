#ifndef TREE
#define TREE

#include <stdint.h>
typedef struct BTreeNode {
    void *data;
    struct BTreeNode *left;
    struct BTreeNode *right;
} BTreeNode;

int BTMain();

BTreeNode *create_BT_node(void *data, uint8_t element_size);
BTreeNode *create_Simple_BTree(void *arr, int count, uint8_t element_size);

#endif
