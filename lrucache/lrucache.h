#ifndef LRUCACHE_H
#define LRUCACHE_H

#include <stddef.h>

typedef struct Node {
    int key;
    int value;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct Entry {
    int key;
    Node *node;
    struct Entry *next;
} Entry;

#define TABLE_SIZE 1031

typedef struct HashTable {
    Entry *buckets[TABLE_SIZE];
} HashTable;

typedef struct LRUCache {
    int capacity;
    size_t size;
    Node *head;
    Node *tail;
    HashTable *map;
} LRUCache;

Node *createNode(int key, int value);
LRUCache *lruCacheCreate(int capacity);
void addNode(struct LRUCache *cache, Node *node);
void removeNode(struct LRUCache *cache, Node *node);
void moveToHead(struct LRUCache *cache, Node *node);
Node *popTail(struct LRUCache *cache);
int lruCacheGet(struct LRUCache *cache, int key);
void lruCachePut(struct LRUCache *cache, int key, int value);
void lruCacheFree(struct LRUCache *cache);

#endif
