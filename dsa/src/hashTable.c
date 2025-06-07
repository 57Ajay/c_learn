#include "all.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct HashSetNode {
  void *data;
  struct HashSetNode *next;
} HashSetNode;

typedef struct {
  HashSetNode **buckets;
  size_t bucket_count;
  size_t size;
  size_t data_size;

  unsigned int (*hash_func)(const void *data);
  bool (*equals_func)(const void *a, const void *b);
  void (*print_func)(const void *data);
} HashSet;

HashSet *hashset_create(size_t bucket_count, size_t data_size,
                        unsigned int (*hash_func)(const void *),
                        bool (*equals_func)(const void *, const void *),
                        void (*print_func)(const void *));

bool hashset_insert(HashSet *set, const void *data);
bool hashset_contains(HashSet *set, const void *data);
bool hashset_remove(HashSet *set, const void *data);
void hashset_print(HashSet *set);
void hashset_destroy(HashSet *set);
size_t hashset_size(HashSet *set);

// Generic hash functions
unsigned int hash_int(const void *data);
unsigned int hash_string(const void *data);
unsigned int hash_djb2(const void *data, size_t len);

// Generic comparison functions
bool equals_int(const void *a, const void *b);
bool equals_string(const void *a, const void *b);

// Generic print functions
void print_int(const void *data);
void print_string(const void *data);

// Implementation
HashSet *hashset_create(size_t bucket_count, size_t data_size,
                        unsigned int (*hash_func)(const void *),
                        bool (*equals_func)(const void *, const void *),
                        void (*print_func)(const void *)) {
  HashSet *set = malloc(sizeof(HashSet));
  if (!set)
    return NULL;

  set->buckets = calloc(bucket_count, sizeof(HashSetNode *));
  if (!set->buckets) {
    free(set);
    return NULL;
  }

  set->bucket_count = bucket_count;
  set->size = 0;
  set->data_size = data_size;
  set->hash_func = hash_func;
  set->equals_func = equals_func;
  set->print_func = print_func;

  return set;
}

bool hashset_insert(HashSet *set, const void *data) {
  if (!set || !data)
    return false;

  unsigned int hash = set->hash_func(data) % set->bucket_count;

  // if element already exists
  HashSetNode *current = set->buckets[hash];
  while (current) {
    if (set->equals_func(current->data, data)) {
      return false;
    }
    current = current->next;
  }

  // Create new node
  HashSetNode *node = malloc(sizeof(HashSetNode));
  if (!node)
    return false;

  node->data = malloc(set->data_size);
  if (!node->data) {
    free(node);
    return false;
  }

  memcpy(node->data, data, set->data_size);
  node->next = set->buckets[hash];
  set->buckets[hash] = node;
  set->size++;

  return true;
}

bool hashset_contains(HashSet *set, const void *data) {
  if (!set || !data)
    return false;

  unsigned int hash = set->hash_func(data) % set->bucket_count;
  HashSetNode *current = set->buckets[hash];

  while (current) {
    if (set->equals_func(current->data, data)) {
      return true;
    }
    current = current->next;
  }

  return false;
}

bool hashset_remove(HashSet *set, const void *data) {
  if (!set || !data)
    return false;

  unsigned int hash = set->hash_func(data) % set->bucket_count;
  HashSetNode *current = set->buckets[hash];
  HashSetNode *prev = NULL;

  while (current) {
    if (set->equals_func(current->data, data)) {
      if (prev) {
        prev->next = current->next;
      } else {
        set->buckets[hash] = current->next;
      }

      free(current->data);
      free(current);
      set->size--;
      return true;
    }
    prev = current;
    current = current->next;
  }

  return false;
}

void hashset_print(HashSet *set) {
  if (!set || !set->print_func)
    return;

  printf("HashSet (size: %zu):\n", set->size);
  for (size_t i = 0; i < set->bucket_count; i++) {
    HashSetNode *current = set->buckets[i];
    if (current) {
      printf("Bucket %zu: ", i);
      while (current) {
        set->print_func(current->data);
        printf(" ");
        current = current->next;
      }
      printf("\n");
    }
  }
}

void hashset_destroy(HashSet *set) {
  if (!set)
    return;

  for (size_t i = 0; i < set->bucket_count; i++) {
    HashSetNode *current = set->buckets[i];
    while (current) {
      HashSetNode *temp = current;
      current = current->next;
      free(temp->data);
      free(temp);
    }
  }

  free(set->buckets);
  free(set);
}

size_t hashset_size(HashSet *set) { return set ? set->size : 0; }

// Hash function implementations
unsigned int hash_int(const void *data) {
  int val = *(const int *)data;
  return (unsigned int)val;
}

unsigned int hash_string(const void *data) {
  const char *str = *(const char **)data;
  return hash_djb2(str, strlen(str));
}

unsigned int hash_djb2(const void *data, size_t len) {
  const unsigned char *bytes = (const unsigned char *)data;
  unsigned int hash = 5381;

  for (size_t i = 0; i < len; i++) {
    hash = ((hash << 5) + hash) + bytes[i];
  }

  return hash;
}

// Comparison function implementations
bool equals_int(const void *a, const void *b) {
  return *(const int *)a == *(const int *)b;
}

bool equals_string(const void *a, const void *b) {
  const char *str1 = *(const char **)a;
  const char *str2 = *(const char **)b;
  return strcmp(str1, str2) == 0;
}

// Print function implementations
void print_int(const void *data) { printf("%d", *(const int *)data); }

void print_string(const void *data) { printf("\"%s\"", *(const char **)data); }

// Example usage
int hashTable() {
  printf("=== Generic Hash Set Demo ===\n\n");

  // Example 1: Integer hash set
  printf("1. Integer Hash Set:\n");
  HashSet *int_set =
      hashset_create(10, sizeof(int), hash_int, equals_int, print_int);

  int nums[] = {42, 15, 23, 42, 7, 15, 99};
  for (int i = 0; i < 7; i++) {
    if (hashset_insert(int_set, &nums[i])) {
      printf("Inserted: %d\n", nums[i]);
    } else {
      printf("Already exists: %d\n", nums[i]);
    }
  }

  printf("\nContains 23: %s\n",
         hashset_contains(int_set, &(int){23}) ? "true" : "false");
  printf("Contains 100: %s\n",
         hashset_contains(int_set, &(int){100}) ? "true" : "false");

  hashset_print(int_set);

  // Example 2: String hash set
  printf("\n2. String Hash Set:\n");
  HashSet *str_set = hashset_create(10, sizeof(char *), hash_string,
                                    equals_string, print_string);

  char *words[] = {"hello", "world", "hash", "set", "hello", "generic"};
  for (int i = 0; i < 6; i++) {
    if (hashset_insert(str_set, &words[i])) {
      printf("Inserted: \"%s\"\n", words[i]);
    } else {
      printf("Already exists: \"%s\"\n", words[i]);
    }
  }

  char *search = "hash";
  printf("\nContains \"hash\": %s\n",
         hashset_contains(str_set, &search) ? "true" : "false");
  search = "missing";
  printf("Contains \"missing\": %s\n",
         hashset_contains(str_set, &search) ? "true" : "false");

  hashset_print(str_set);

  // Remove operations
  printf("\n3. Remove Operations:\n");
  int remove_val = 23;
  if (hashset_remove(int_set, &remove_val)) {
    printf("Removed: %d\n", remove_val);
  }

  char *remove_str = "world";
  if (hashset_remove(str_set, &remove_str)) {
    printf("Removed: \"%s\"\n", remove_str);
  }

  printf("\nAfter removals:\n");
  printf("Int set size: %zu\n", hashset_size(int_set));
  printf("String set size: %zu\n", hashset_size(str_set));

  // Cleanup
  hashset_destroy(int_set);
  hashset_destroy(str_set);

  return 0;
}
