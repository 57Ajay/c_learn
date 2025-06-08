#include "tree.h"
#include "queue.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

BTreeNode *create_BT_node(void *data, uint8_t element_size) {
    if (!data) {
        return NULL;
    }
    BTreeNode *node = (BTreeNode *)malloc(sizeof(BTreeNode));
    if (!node) {
        perror("Failed to allocate memory for binary tree node");
        return NULL;
    }
    node->data = malloc(element_size);
    memcpy(node->data, data, element_size);
    node->left = node->right = NULL;
    return node;
}

BTreeNode *create_Simple_BTree(void *arr, int count, uint8_t element_size) {
    if (count == 0)
        return NULL;
    BTreeNode *root = create_BT_node(&arr[0], element_size);
    Queue *queue = createQueue(count, sizeof(BTreeNode *));
    enqueue(queue, &root);
    int i = 1;
    while (i < count) {
        BTreeNode *current = NULL;

        dequeue(queue, &current);

        if (i < count) {
            // left child;
            BTreeNode *left =
                create_BT_node((char *)arr + i * element_size, element_size);
            current->left = left;
            enqueue(queue, &left);
            i++;
        }

        if (i < count) {
            BTreeNode *right =
                create_BT_node((char *)arr + i * element_size, element_size);
            current->right = right;
            enqueue(queue, &right);
            i++;
        }
    }
    destroy_queue(queue);
    return root;
}

void printPreorder(BTreeNode *root) {
    if (!root)
        return;
    printf("%d ", *(int *)root->data);
    printPreorder(root->left);
    printPreorder(root->right);
}

void printInorder(BTreeNode *root) {
    if (!root)
        return;
    printInorder(root->left);
    printf("%d ", *(int *)root->data);
    printInorder(root->right);
}

void printPostorder(BTreeNode *root) {
    if (!root)
        return;
    printPostorder(root->left);
    printPostorder(root->right);
    printf("%d ", *(int *)root->data);
}

void printLevelOrder(BTreeNode *root) {
    if (!root)
        return;
    Queue *q = createQueue(100, sizeof(BTreeNode *));
    enqueue(q, &root);

    while (!isEmpty_Q(q)) {
        BTreeNode *curr = NULL;
        dequeue(q, &curr);
        printf("%d ", *(int *)curr->data);

        if (curr->left)
            enqueue(q, &curr->left);
        if (curr->right)
            enqueue(q, &curr->right);
    }

    destroy_queue(q);
}

void printTreeVisual(BTreeNode *root, int space) {
    if (!root)
        return;

    const int INDENT = 5;
    space += INDENT;

    // Right child first
    printTreeVisual(root->right, space);

    // Current node
    printf("\n");
    for (int i = INDENT; i < space; i++)
        printf(" ");
    printf("%d\n", *(int *)root->data);

    // Left child
    printTreeVisual(root->left, space);
}

int BTMain() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    BTreeNode *root = create_Simple_BTree(arr, n, sizeof(int));

    printf("\n🧾 Preorder: ");
    printPreorder(root);

    printf("\n🧾 Inorder: ");
    printInorder(root);

    printf("\n🧾 Postorder: ");
    printPostorder(root);

    printf("\n🧾 Level Order: ");
    printLevelOrder(root);

    printf("\n\n📈 Tree Visual:\n");
    printTreeVisual(root, 0);

    return 0;
}
