#ifndef HEAP_H
#define HEAP_H

#include <stdbool.h>
#include <stdint.h>

typedef struct Heap {

  void *arr;
  int size;
  int capacity;
  uint8_t elem_size;
  int (*cmp)(void *, void *);
} Heap;

int heapMain();
Heap *create_heap(int capacity, uint8_t elem_size, int (*cmp)(void *, void *));
bool insert_heap(Heap *heap, void *element);
bool extract_min(Heap *heap, void *output);
bool peek_min(Heap *heap, void *output);
void destroy_heap(Heap *heap);
void print_int_heap(Heap *heap);

#endif
