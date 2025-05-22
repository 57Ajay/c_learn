#include "lrucache.h"
#include <stdio.h>
#include <stdlib.h>

Node *createNode(int key, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) {
        perror("Failed to allocate memory for new node");
        return NULL;
    }
    newNode->key = key;
    newNode->value = value;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

LRUCache *lruCacheCreate(int capacity) {
    struct LRUCache *cache = (struct LRUCache *)malloc(sizeof(struct LRUCache));
    if (!cache) {
        perror("Failed to allocate memory for LRUCache");
        return NULL;
    }

    cache->capacity = capacity;
    cache->size = 0;
    cache->head = NULL;
    cache->tail = NULL;

    cache->map = (struct HashTable *)malloc(sizeof(struct HashTable));
    if (!cache->map) {
        perror("Failed to allocate memory for HashTable");
        free(cache);
        return NULL;
    }

    for (int i = 0; i < TABLE_SIZE; i++) {
        cache->map->buckets[i] = NULL;
    }

    return cache;
}

unsigned long hash(int key) { return key % TABLE_SIZE; }

void addNode(LRUCache *cache, Node *node) {
    if (!cache->head) {
        cache->head = node;
        cache->tail = node;
    } else {
        node->next = cache->head;
        cache->head->prev = node;
        cache->head = node;
    }
}

void removeNode(LRUCache *cache, Node *node) {
    if (node->prev) {
        node->prev->next = node->next;
    } else {
        cache->head = node->next;
    }

    if (node->next) {
        node->next->prev = node->prev;
    } else {
        cache->tail = node->prev;
    }
}

void moveToHead(LRUCache *cache, Node *node) {
    removeNode(cache, node);
    addNode(cache, node);
}

Node *popTail(struct LRUCache *cache) {
    Node *tailNode = cache->tail;
    removeNode(cache, tailNode);
    return tailNode;
}

int lruCacheGet(LRUCache *cache, int key) {
    unsigned long index = hash(key);
    struct Entry *current = cache->map->buckets[index];

    while (current) {
        if (current->key == key) {
            moveToHead(cache, current->node);
            return current->node->value;
        }
        current = current->next;
    }

    return -1; // Key not found
}

void lruCachePut(LRUCache *cache, int key, int value) {
    unsigned long index = hash(key);
    struct Entry *current = cache->map->buckets[index];

    while (current) {
        if (current->key == key) {
            current->node->value = value;
            moveToHead(cache, current->node);
            return;
        }
        current = current->next;
    }

    Node *newNode = createNode(key, value);
    if (!newNode)
        return;

    struct Entry *newEntry = (struct Entry *)malloc(sizeof(struct Entry));
    if (!newEntry) {
        free(newNode);
        perror("Failed to allocate memory for new entry");
        return;
    }
    newEntry->key = key;
    newEntry->node = newNode;
    newEntry->next = cache->map->buckets[index];
    cache->map->buckets[index] = newEntry;

    addNode(cache, newNode);
    cache->size++;

    if (cache->size > cache->capacity) {
        Node *tailNode = popTail(cache);
        if (!tailNode)
            return;

        unsigned long tailIndex = hash(tailNode->key);
        struct Entry *prev = NULL;
        struct Entry *curr = cache->map->buckets[tailIndex];

        while (curr) {
            if (curr->key == tailNode->key) {
                if (prev) {
                    prev->next = curr->next;
                } else {
                    cache->map->buckets[tailIndex] = curr->next;
                }

                free(curr);
                break;
            }
            prev = curr;
            curr = curr->next;
        }

        free(tailNode);
        cache->size--;
    }
}

void lruCacheFree(LRUCache *cache) {
    if (!cache)
        return;

    Node *current = cache->head;
    while (current) {
        Node *next = current->next;
        free(current);
        current = next;
    }

    for (int i = 0; i < TABLE_SIZE; i++) {
        struct Entry *currentEntry = cache->map->buckets[i];
        while (currentEntry) {
            struct Entry *nextEntry = currentEntry->next;
            free(currentEntry);
            currentEntry = nextEntry;
        }
    }

    free(cache->map);
    free(cache);
}
