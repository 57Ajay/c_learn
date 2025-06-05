#include "all.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *createNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Node *createLinkedList(int arr[], int size) {
    Node *head = createNode(arr[0]);
    Node *currentNode = head;
    for (int i = 1; i < size; i++) {
        currentNode->next = createNode(arr[i]);
        currentNode = currentNode->next;
    }
    return head;
}

// Need stdarg
Node *createLinkedListAdvanced(int count, ...) {
    if (count == 0)
        return NULL;

    va_list args;
    va_start(args, count);

    Node *head = createNode(va_arg(args, int));
    Node *current = head;

    for (int i = 1; i < count; i++) {
        current->next = createNode(va_arg(args, int));
        current = current->next;
    }

    va_end(args);
    return head;
}

void printList(Node *node) {
    while (node) {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("null\n");
}

Node *deleteNode(Node *head, Node *nodeToDelete) {
    if (head == NULL || nodeToDelete == NULL)
        return head;
    if (head == nodeToDelete) {
        Node *newHead = head->next;
        free(head);
        return newHead;
    }

    Node *currentNode = head;
    while (currentNode) {
        if (currentNode->next == nodeToDelete) {
            currentNode->next = currentNode->next->next;
            free(nodeToDelete);
            break;
        }
        currentNode = currentNode->next;
    }
    return head;
}

// Add node into a linked_list

Node *addNode(Node *head, Node *nodeToAdd, int position) {
    if (position <= 0 || nodeToAdd == NULL) {
        nodeToAdd->next = head;
        return nodeToAdd;
    }
    Node *currentNode = head;
    int index = 0;

    while (currentNode != NULL && index < position - 1) {
        currentNode = currentNode->next;
        index++;
    }

    if (currentNode == NULL) {
        return head;
    }

    nodeToAdd->next = currentNode->next;
    currentNode->next = nodeToAdd;

    return head;
}

// free the memory;

void freeList(Node *head) {
    while (head) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
}

int min_val(Node *head) {
    if (head == NULL) {
        return -1;
    }
    int min = head->data;
    Node *currentNode = head->next;
    while (currentNode) {
        if (currentNode->data < min) {
            min = currentNode->data;
        }
        currentNode = currentNode->next;
    }
    return min;
}

int linked_list() {
    Node *node1 = createNode(3);
    Node *node2 = createNode(5);
    Node *node3 = createNode(13);
    Node *node4 = createNode(2);

    node1->next = node2;
    node2->next = node3;
    node3->next = node4;

    printList(node1);
    printf("Min Value: %d\n", min_val(node1));

    // Free the memory

    int arr[] = {2, 3, 1, 6, 8, 32, 12, 69};

    int len = sizeof(arr) / sizeof(arr[0]);

    Node *one = createLinkedList(arr, len);
    deleteNode(one, one->next->next);
    addNode(one, createNode(69), 2);
    printf("linked_list one: ");
    printList(one);

    Node *two = createLinkedListAdvanced(6, 2, 98, 3, 1, 43, 3);
    printf("linked_list two: ");
    printList(two);

    printf("Min one: %d\nMin two: %d\n", min_val(one), min_val(two));
    free(node1);
    free(node2);
    free(node3);
    free(node4);
    freeList(one);
    freeList(two);

    return 69;
}
