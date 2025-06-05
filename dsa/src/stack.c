#include "all.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack {
    void *arr;
    int top;
    int capacity;
    size_t elem_size;
} Stack;

Stack *create(int capacity, size_t elem_size) {
    if (capacity <= 0 || elem_size == 0) {
        printf("Invalid parameters for stack creation\n");
        return NULL;
    }

    Stack *stk = malloc(sizeof(Stack));
    if (!stk) {
        perror("Failed to allocate stack");
        return NULL;
    }

    stk->arr = malloc(capacity * elem_size);
    if (!stk->arr) {
        perror("Failed to allocate stack array");
        free(stk);
        return NULL;
    }

    stk->top = -1;
    stk->capacity = capacity;
    stk->elem_size = elem_size;
    return stk;
}

bool push(Stack *stk, void *value) {
    if (!stk || !value) {
        printf("Invalid stack or value\n");
        return false;
    }

    if (stk->top >= stk->capacity - 1) {
        printf("Stack Overflow\n");
        return false;
    }

    stk->top++;
    void *target = (char *)stk->arr + stk->top * stk->elem_size;
    memcpy(target, value, stk->elem_size);
    return true;
}

bool pop(Stack *stk, void *out_value) {
    if (!stk) {
        printf("Invalid stack\n");
        return false;
    }

    if (stk->top < 0) {
        printf("Stack Underflow\n");
        return false;
    }

    if (out_value) {
        void *source = (char *)stk->arr + stk->top * stk->elem_size;
        memcpy(out_value, source, stk->elem_size);
    }
    stk->top--;
    return true;
}

bool peek(Stack *stk, void *out_value) {
    if (!stk || !out_value) {
        printf("Invalid stack or output parameter\n");
        return false;
    }

    if (stk->top < 0) {
        printf("Stack Empty\n");
        return false;
    }

    void *source = (char *)stk->arr + stk->top * stk->elem_size;
    memcpy(out_value, source, stk->elem_size);
    return true;
}

bool isEmpty(Stack *stk) { return (!stk || stk->top < 0); }

bool isFull(Stack *stk) { return (stk && stk->top >= stk->capacity - 1); }

int size(Stack *stk) {
    if (!stk)
        return -1;
    return stk->top + 1;
}

int getCapacity(Stack *stk) {
    if (!stk)
        return -1;
    return stk->capacity;
}

void clear(Stack *stk) {
    if (stk) {
        stk->top = -1;
    }
}

void destroy(Stack *stk) {
    if (stk) {
        free(stk->arr);
        free(stk);
    }
}

void printIntStack(Stack *stk) {
    if (!stk) {
        printf("Invalid stack\n");
        return;
    }

    printf("Stack (bottom to top): ");
    for (int i = 0; i <= stk->top; i++) {
        int val;
        memcpy(&val, (char *)stk->arr + i * stk->elem_size, sizeof(int));
        printf("%d ", val);
    }
    printf("\n");
}

void printStringStack(Stack *stk) {
    if (!stk) {
        printf("Invalid stack\n");
        return;
    }

    printf("Stack (bottom to top): ");
    for (int i = 0; i <= stk->top; i++) {
        char *str = (char *)stk->arr + i * stk->elem_size;
        printf("'%s' ", str);
    }
    printf("\n");
}

void printCharStack(Stack *stk) {
    if (!stk) {
        printf("Invalid stack\n");
        return;
    }

    printf("Stack (bottom to top): ");
    for (int i = 0; i <= stk->top; i++) {
        char val;
        memcpy(&val, (char *)stk->arr + i * stk->elem_size, sizeof(char));
        printf("'%c' ", val);
    }
    printf("\n");
}

void printDoubleStack(Stack *stk) {
    if (!stk) {
        printf("Invalid stack\n");
        return;
    }

    printf("Stack (bottom to top): ");
    for (int i = 0; i <= stk->top; i++) {
        double val;
        memcpy(&val, (char *)stk->arr + i * stk->elem_size, sizeof(double));
        printf("%.2f ", val);
    }
    printf("\n");
}

int stackMain() {
    printf("=== GENERIC STACK IMPLEMENTATION DEMO ===\n\n");

    // Test 1: Integer Stack
    printf("1. INTEGER STACK TEST\n");
    printf("---------------------\n");
    Stack *intStack = create(5, sizeof(int));
    if (!intStack)
        return 1;

    printf("Created integer stack with capacity: %d\n", getCapacity(intStack));
    printf("Is empty: %s\n", isEmpty(intStack) ? "Yes" : "No");
    printf("Current size: %d\n", size(intStack));

    // Push integers
    int values[] = {10, 20, 30, 40};
    for (int i = 0; i < 4; i++) {
        printf("Pushing: %d\n", values[i]);
        push(intStack, &values[i]);
        printIntStack(intStack);
    }

    printf("Is full: %s\n", isFull(intStack) ? "Yes" : "No");
    printf("Current size: %d\n", size(intStack));

    // Peek
    int peeked;
    if (peek(intStack, &peeked)) {
        printf("Peeked value: %d\n", peeked);
    }

    // Pop elements
    printf("\nPopping elements:\n");
    int popped;
    while (!isEmpty(intStack)) {
        if (pop(intStack, &popped)) {
            printf("Popped: %d\n", popped);
            printIntStack(intStack);
        }
    }

    // Try to pop from empty stack
    printf("Trying to pop from empty stack:\n");
    pop(intStack, &popped);

    destroy(intStack);

    // Test 2: Character Stack
    printf("\n2. CHARACTER STACK TEST\n");
    printf("-----------------------\n");
    Stack *charStack = create(10, sizeof(char));
    if (!charStack)
        return 1;

    char chars[] = {'H', 'e', 'l', 'l', 'o'};
    for (int i = 0; i < 5; i++) {
        push(charStack, &chars[i]);
    }
    printCharStack(charStack);

    // Reverse the string using stack
    printf("Reversing string using stack:\n");
    printf("Reversed: ");
    char c;
    while (!isEmpty(charStack)) {
        pop(charStack, &c);
        printf("%c", c);
    }
    printf("\n");

    destroy(charStack);

    // Test 3: String Stack (storing actual strings, not pointers)
    printf("\n3. STRING STACK TEST\n");
    printf("--------------------\n");
    const int MAX_STR_LEN = 20;
    Stack *strStack = create(5, MAX_STR_LEN);
    if (!strStack)
        return 1;

    char str1[] = "Hello";
    char str2[] = "World";
    char str3[] = "Stack";

    push(strStack, str1);
    push(strStack, str2);
    push(strStack, str3);

    printStringStack(strStack);

    char peekedStr[MAX_STR_LEN];
    if (peek(strStack, peekedStr)) {
        printf("Peeked string: '%s'\n", peekedStr);
    }

    char poppedStr[MAX_STR_LEN];
    while (!isEmpty(strStack)) {
        if (pop(strStack, poppedStr)) {
            printf("Popped string: '%s'\n", poppedStr);
        }
    }

    destroy(strStack);

    // Test 4: Double Stack
    printf("\n4. DOUBLE STACK TEST\n");
    printf("--------------------\n");
    Stack *doubleStack = create(4, sizeof(double));
    if (!doubleStack)
        return 1;

    double doubles[] = {3.14, 2.71, 1.41, 0.57};
    for (int i = 0; i < 4; i++) {
        push(doubleStack, &doubles[i]);
    }
    printDoubleStack(doubleStack);

    // Test overflow
    double extra = 99.99;
    printf("Testing overflow:\n");
    push(doubleStack, &extra);

    // Clear stack
    printf("Clearing stack:\n");
    clear(doubleStack);
    printf("Size after clear: %d\n", size(doubleStack));
    printf("Is empty: %s\n", isEmpty(doubleStack) ? "Yes" : "No");

    destroy(doubleStack);

    // Test 5: Edge cases
    printf("\n5. EDGE CASES TEST\n");
    printf("------------------\n");

    // Invalid stack creation
    Stack *invalidStack = create(0, sizeof(int));
    if (!invalidStack) {
        printf("Correctly handled invalid stack creation\n");
    }

    // NULL stack operations
    printf("Testing NULL stack operations:\n");
    push(NULL, &values[0]);
    pop(NULL, &popped);
    peek(NULL, &peeked);
    printf("isEmpty(NULL): %s\n", isEmpty(NULL) ? "Yes" : "No");
    printf("size(NULL): %d\n", size(NULL));

    printf("\n=== ALL TESTS COMPLETED ===\n");
    return 0;
}
