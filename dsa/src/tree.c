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
    node->height = 1;
    node->data = malloc(element_size);
    memcpy(node->data, data, element_size);
    node->left = node->right = NULL;
    return node;
}

BTreeNode *create_Simple_BTree(void *arr, int count, uint8_t element_size) {
    if (count == 0)
        return NULL;
    BTreeNode *root =
        create_BT_node((char *)arr + 0 * element_size, element_size);
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

void destroy_simple_BTree(BTreeNode *root) {
    if (!root)
        return;
    destroy_simple_BTree(root->left);
    destroy_simple_BTree(root->right);
    free(root->data);
    root->data = NULL;
    free(root);
    root = NULL;
}

// Binary search tree;

BTreeNode *insert_BST(BTreeNode *root, void *data, uint8_t elem_size,
                      int (*cmp)(void *, void *)) {
    if (!root)
        return create_BT_node(data, elem_size);

    int result = cmp(data, root->data);

    if (result < 0) {
        root->left = insert_BST(root->left, data, elem_size, cmp);
    } else if (result > 0) {
        root->right = insert_BST(root->right, data, elem_size, cmp);
    }
    // ignorung the duplicates

    return root;
}

BTreeNode *create_BST(void *arr, int count, uint8_t elem_size,
                      int (*cmp)(void *, void *)) {
    if (count == 0)
        return NULL;

    BTreeNode *root = NULL;

    for (int i = 0; i < count; i++) {
        void *element_ptr = (char *)arr + i * elem_size;
        root = insert_BST(root, element_ptr, elem_size, cmp);
    }

    return root;
}

int compare_int(void *a, void *b) {
    int x = *(int *)a;
    int y = *(int *)b;
    return x - y;
}

BTreeNode *search_BST(BTreeNode *root, void *key, int (*cmp)(void *, void *)) {
    if (!root)
        return NULL;

    int result = cmp(key, root->data);
    if (result == 0) {
        return root;
    } else if (result < 0) {
        return search_BST(root->left, key, cmp);
    } else {
        return search_BST(root->right, key, cmp);
    }
}

int height_BST(BTreeNode *root) {
    if (!root)
        return 0;
    int left_height = height_BST(root->left);
    int right_height = height_BST(root->right);
    return 1 + (left_height > right_height ? left_height : right_height);
}

int count_nodes(BTreeNode *root) {
    if (!root)
        return 0;
    return 1 + count_nodes(root->left) + count_nodes(root->right);
}

int count_leaves(BTreeNode *root) {
    if (!root)
        return 0;
    if (!root->left && !root->right)
        return 1;
    return count_leaves(root->left) + count_leaves(root->right);
}

BTreeNode *find_min(BTreeNode *root) {
    while (root && root->left)
        root = root->left;
    return root;
}

BTreeNode *delete_BST(BTreeNode *root, void *key, uint8_t elem_size,
                      int (*cmp)(void *, void *)) {
    if (!root)
        return NULL;

    int res = cmp(key, root->data);

    if (res < 0) {
        root->left = delete_BST(root->left, key, elem_size, cmp);
    } else if (res > 0) {
        root->right = delete_BST(root->right, key, elem_size, cmp);
    } else {
        // Match found
        if (!root->left && !root->right) {
            free(root->data);
            free(root);
            return NULL;
        } else if (!root->left) {
            BTreeNode *temp = root->right;
            free(root->data);
            free(root);
            return temp;
        } else if (!root->right) {
            BTreeNode *temp = root->left;
            free(root->data);
            free(root);
            return temp;
        } else {
            BTreeNode *successor = find_min(root->right);
            memcpy(root->data, successor->data, elem_size);
            root->right =
                delete_BST(root->right, successor->data, elem_size, cmp);
        }
    }
    return root;
}

void test_search(BTreeNode *root, int key) {
    BTreeNode *found = search_BST(root, &key, compare_int);
    if (found)
        printf("✅ Found: %d\n", *(int *)found->data);
    else
        printf("❌ Not Found: %d\n", key);
}

// AVL BTree;

int get_height(BTreeNode *node) { return node ? node->height : 0; }

int get_balance(BTreeNode *node) {
    return node ? get_height(node->left) - get_height(node->right) : 0;
}

int maxVal(int a, int b) { return a > b ? a : b; }

BTreeNode *right_rotate(BTreeNode *y) {
    BTreeNode *x = y->left;
    BTreeNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + maxVal(get_height(y->left), get_height(y->right));
    x->height = 1 + maxVal(get_height(x->left), get_height(x->right));

    return x;
}

BTreeNode *left_rotate(BTreeNode *x) {
    BTreeNode *y = x->right;
    BTreeNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + maxVal(get_height(x->left), get_height(x->right));
    y->height = 1 + maxVal(get_height(y->left), get_height(y->right));

    return y;
}

BTreeNode *insert_AVL(BTreeNode *root, void *data, uint8_t elem_size,
                      int (*cmp)(void *, void *)) {
    if (!root)
        return create_BT_node(data, elem_size); // height becomes 1

    int res = cmp(data, root->data);

    if (res < 0)
        root->left = insert_AVL(root->left, data, elem_size, cmp);
    else if (res > 0)
        root->right = insert_AVL(root->right, data, elem_size, cmp);
    else
        return root; // no duplicates

    root->height = 1 + maxVal(get_height(root->left), get_height(root->right));
    int balance = get_balance(root);

    // Left Left
    if (balance > 1 && cmp(data, root->left->data) < 0)
        return right_rotate(root);

    // Right Right
    if (balance < -1 && cmp(data, root->right->data) > 0)
        return left_rotate(root);

    // Left Right
    if (balance > 1 && cmp(data, root->left->data) > 0) {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }

    // Right Left
    if (balance < -1 && cmp(data, root->right->data) < 0) {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }

    return root;
}

BTreeNode *create_AVL(void *arr, int count, uint8_t elem_size,
                      int (*cmp)(void *, void *)) {
    BTreeNode *root = NULL;
    for (int i = 0; i < count; i++) {
        void *element_ptr = (char *)arr + i * elem_size;
        root = insert_AVL(root, element_ptr, elem_size, cmp);
    }
    return root;
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

    destroy_simple_BTree(root);

    printf("\n---------------------------BST-----------------------------\n");
    int arr_bst[] = {5, 1, 8, 69, 9, 3, 2};
    int len_arr_bst = sizeof(arr_bst) / sizeof(int);
    BTreeNode *bst = create_BST(arr_bst, len_arr_bst, sizeof(int), compare_int);

    printf("\n✅ BST Created!\n");

    printf("\n🧾 Inorder (should be sorted): ");
    printInorder(bst);

    printf("\n🧾 Preorder: ");
    printPreorder(bst);

    printf("\n\n📈 BST Visual:\n");
    printTreeVisual(bst, 0);

    test_search(bst, 2);
    test_search(bst, 6969);

    printf("Height: %d\n", height_BST(bst));
    printf("Total Nodes: %d\n", count_nodes(bst));
    printf("Leaf Nodes: %d\n", count_leaves(bst));

    int key_to_delete = 3;
    printf("Deleting: %d\n", key_to_delete);
    bst = delete_BST(bst, &key_to_delete, sizeof(int), compare_int);

    printf("Inorder After Deletion: ");
    printInorder(bst);
    printf("\n");

    printf("\nVisual Tree After Deletion:\n");
    printTreeVisual(bst, 0);

    destroy_simple_BTree(bst);

    printf("\n---------------AVL BTree------------------------\n");
    int arr_avl[] = {10, 20, 30, 40, 50, 25};
    int len_arr_avl = sizeof(arr) / sizeof(arr[0]);

    BTreeNode *avl = create_AVL(arr_avl, len_arr_avl, sizeof(int), compare_int);

    printf("\n✅ AVL Tree Created (Balanced)\n");

    printf("Inorder (should be sorted): ");
    printInorder(avl);

    printf("\nPreorder (shows structure): ");
    printPreorder(avl);

    printf("\n\nVisual AVL Tree:\n");
    printTreeVisual(avl, 0);

    destroy_simple_BTree(avl);
    return 0;
}
