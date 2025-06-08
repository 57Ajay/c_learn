#ifndef QUEUE
#define QUEUE

#include <stdint.h>

typedef struct Queue {
  void *arr;
  uint64_t capacity;
  uint8_t element_size;
  int front;
  int rear;
  int size;
} Queue;

Queue *createQueue(uint64_t capacity, uint8_t element_size);
bool enqueue(Queue *que, void *value);
bool dequeue(Queue *que, void *output);
bool peek_Q(Queue *que, void *output);
bool isEmpty_Q(Queue *que);
int queue_size(Queue *que);
void print_int_queue(Queue *que);
void destroy_queue(Queue *que);
int queueMain();

#endif
