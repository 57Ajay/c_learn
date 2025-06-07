#include "all.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Queue {
    void *arr;
    uint64_t capacity;
    uint8_t element_size;
    int front;
    int rear;
    int size;
} Queue;

Queue *createQueue(uint64_t capacity, uint8_t element_size) {
    if (capacity == 0 || element_size == 0) {
        fprintf(stderr, "Invalid parameters for Queue creation\n");
        return NULL;
    }

    Queue *que = (Queue *)malloc(sizeof(Queue));
    if (!que) {
        perror("Failed to allocate memory for Queue");
        return NULL;
    }

    que->arr = malloc(capacity * element_size);
    if (!que->arr) {
        perror("Failed to allocate memory for Queue array");
        free(que);
        return NULL;
    }

    que->capacity = capacity;
    que->element_size = element_size;
    que->front = 0;
    que->rear = 0;
    que->size = 0;
    return que;
}

bool enqueue(Queue *que, void *value) {
    if (!que || !value)
        return false;

    if (que->size == (int)que->capacity) {
        fprintf(stderr, "Queue overflow\n");
        return false;
    }

    void *target = (char *)que->arr + que->rear * que->element_size;
    memcpy(target, value, que->element_size);
    que->rear = (que->rear + 1) % que->capacity;
    que->size++;
    return true;
}

bool dequeue(Queue *que, void *output) {
    if (!que || !output)
        return false;

    if (que->size == 0) {
        fprintf(stderr, "Queue underflow\n");
        return false;
    }

    void *source = (char *)que->arr + que->front * que->element_size;
    memcpy(output, source, que->element_size);
    que->front = (que->front + 1) % que->capacity;
    que->size--;
    return true;
}

bool peek_Q(Queue *que, void *output) {
    if (!que || !output)
        return false;

    if (que->size == 0) {
        fprintf(stderr, "Queue is empty\n");
        return false;
    }

    void *source = (char *)que->arr + que->front * que->element_size;
    memcpy(output, source, que->element_size);
    return true;
}

bool isEmpty_Q(Queue *que) { return que && que->size == 0; }

int queue_size(Queue *que) { return que ? que->size : -1; }

void print_int_queue(Queue *que) {
    if (!que || que->size == 0) {
        printf("Queue is empty\n");
        return;
    }

    printf("Queue contents: ");
    for (int i = 0; i < que->size; i++) {
        int val;
        int index = (que->front + i) % que->capacity;
        memcpy(&val, (char *)que->arr + index * que->element_size,
               que->element_size);
        printf("%d ", val);
    }
    printf("\n");
}

void destroy_queue(Queue *que) {
    if (que) {
        free(que->arr);
        free(que);
    }
}

int queueMain() {
    Queue *que = createQueue(5, sizeof(int));
    if (!que)
        return 1;

    int vals[] = {10, 20, 30, 40, 50};

    printf("Enqueuing elements...\n");
    for (int i = 0; i < 5; i++) {
        enqueue(que, &vals[i]);
    }

    print_int_queue(que);

    printf("Queue size: %d\n", queue_size(que));
    printf("Is empty? %s\n", isEmpty_Q(que) ? "Yes" : "No");

    int frontVal;
    if (peek_Q(que, &frontVal)) {
        printf("Peeked front element: %d\n", frontVal);
    }

    int removed;
    dequeue(que, &removed);
    printf("Dequeued: %d\n", removed);

    enqueue(que, &(int){60});
    print_int_queue(que);

    printf("Queue size after operations: %d\n", queue_size(que)); // 5

    destroy_queue(que);
    return 69;
}
