#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void swap(void *a, void *b, size_t size) {
    char tmp[size];
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
}

Heap *create_heap(int capacity, uint8_t elem_size, int (*cmp)(void *, void *)) {
    Heap *heap = malloc(sizeof(Heap));
    heap->arr = malloc(capacity * elem_size);
    heap->size = 0;
    heap->capacity = capacity;
    heap->elem_size = elem_size;
    heap->cmp = cmp;
    return heap;
}

void heapify_up(Heap *heap, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        void *current = (char *)heap->arr + index * heap->elem_size;
        void *parent_ptr = (char *)heap->arr + parent * heap->elem_size;
        if (heap->cmp(current, parent_ptr) < 0) {
            swap(current, parent_ptr, heap->elem_size);
            index = parent;
        } else {
            break;
        }
    }
}

bool insert_heap(Heap *heap, void *element) {
    if (heap->size >= heap->capacity)
        return false;

    void *dest = (char *)heap->arr + heap->size * heap->elem_size;
    memcpy(dest, element, heap->elem_size);
    heapify_up(heap, heap->size);
    heap->size++;
    return true;
}

void heapify_down(Heap *heap, int index) {

    while (1) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int min = index;

        void *min_ptr = (char *)heap->arr + min * heap->elem_size;
        if (left < heap->size) {
            void *left_ptr = (char *)heap->arr + left * heap->elem_size;
            if (heap->cmp(left_ptr, min_ptr) < 0) {
                min = left;
                min_ptr = left_ptr;
            }
        }
        if (right < heap->size) {
            void *right_ptr = (char *)heap->arr + right * heap->elem_size;
            if (heap->cmp(right_ptr, min_ptr) < 0) {
                min = right;
            }
        }

        if (min != index) {
            void *a = (char *)heap->arr + index * heap->elem_size;
            void *b = (char *)heap->arr + min * heap->elem_size;
            swap(a, b, heap->elem_size);
            index = min;
        } else {
            break;
        }
    }
}

bool extract_min(Heap *heap, void *output) {
    if (heap->size == 0)
        return false;

    void *root = heap->arr;
    memcpy(output, root, heap->elem_size);

    void *last = (char *)heap->arr + (heap->size - 1) * heap->elem_size;
    memcpy(root, last, heap->elem_size);
    heap->size--;

    heapify_down(heap, 0);
    return true;
}

bool peek_min(Heap *heap, void *output) {
    if (heap->size == 0)
        return false;
    memcpy(output, heap->arr, heap->elem_size);
    return true;
}

void destroy_heap(Heap *heap) {
    if (!heap)
        return;
    free(heap->arr);
    free(heap);
}

void print_int_heap(Heap *heap) {
    printf("[ ");
    for (int i = 0; i < heap->size; i++) {
        int *val = (int *)((char *)heap->arr + i * heap->elem_size);
        printf("%d ", *val);
    }
    printf("]\n");
}

int compare_int_(void *a, void *b) {
    return (*(int *)a - *(int *)b); // Min-Heap
}

int heapMain() {
    int arr[] = {10, 4, 7, 1, 8, 9, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    Heap *minHeap = create_heap(100, sizeof(int), compare_int_);

    for (int i = 0; i < n; i++) {
        insert_heap(minHeap, &arr[i]);
    }

    printf("Min Heap after inserts:\n");
    print_int_heap(minHeap);

    int top;
    extract_min(minHeap, &top);
    printf("Extracted Min: %d\n", top);

    printf("Heap after extraction:\n");
    print_int_heap(minHeap);

    destroy_heap(minHeap);
    return 0;
}
