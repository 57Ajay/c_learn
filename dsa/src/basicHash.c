#include "all.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct hashEntry {
    char *key;
    char *value;
} hashEntry;

typedef struct hashTbl {
    hashEntry **entries;
    int size;
} hashTbl;

unsigned long hashFunction(const char *key, size_t tableSize) {
    unsigned long hash = 5381;
    int c;

    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash % tableSize;
}

hashTbl *createHashTbl(size_t size) {
    hashTbl *tbl = (hashTbl *)malloc(sizeof(hashTbl));
    if (!tbl) {
        perror("Can not allocate memory for hashTable");
        return NULL;
    }
    tbl->entries = (hashEntry **)calloc(size, sizeof(hashEntry *));
    if (!tbl->entries) {
        free(tbl);
        perror("failed to allocate memory to table entries");
        return NULL;
    }

    tbl->size = size;

    return tbl;
}

bool ht_insert(hashTbl *hstbl, char *key, char *val) {
    if (!hstbl || !key || !val)
        return false;
    unsigned long index = hashFunction(key, hstbl->size);

    if (hstbl->entries[index]) {
        free(hstbl->entries[index]->key);
        free(hstbl->entries[index]->value);
        free(hstbl->entries[index]);
    }

    hashEntry *entry = (hashEntry *)malloc(sizeof(hashEntry));
    if (!entry) {
        perror("failed to allocate the memory for new entry");
        return false;
    }
    entry->key = strdup(key);
    entry->value = strdup(val);
    hstbl->entries[index] = entry;
    return true;
}

char *ht_search(hashTbl *hstbl, const char *key) {
    if (!hstbl || !key) {
        return NULL;
    }

    unsigned long index = hashFunction(key, hstbl->size);
    hashEntry *entry = hstbl->entries[index];

    if (entry && strcmp(entry->key, key) == 0) {
        return entry->value;
    }
    return NULL;
}

bool ht_delete(hashTbl *hstbl, char *key) {
    if (!hstbl || !key) {
        return false;
    }
    unsigned long index = hashFunction(key, hstbl->size);
    printf("index: %lu\n", index);
    hashEntry *entry = hstbl->entries[index];
    printf("ENTRY: %s\n", entry->key);
    if (entry && strcmp(entry->key, key) == 0) {

        free(entry->key);
        free(entry->value);
        free(entry);
        hstbl->entries[index] = NULL;
        return true;
    }

    return false;
}

void destroy_hstbl(hashTbl *hstbl) {
    if (!hstbl) {
        return;
    }
    for (int i = 0; i < hstbl->size; i++) {
        if (hstbl->entries[i] != NULL) {
            free(hstbl->entries[i]->key);
            hstbl->entries[i]->key = NULL;
            free(hstbl->entries[i]->value);
            hstbl->entries[i]->value = NULL;
            free(hstbl->entries[i]);
            hstbl->entries[i] = NULL;
        }
    }
    free(hstbl->entries);
    hstbl->entries = NULL;
    free(hstbl);
    hstbl = NULL;
}

int testhash() {
    hashTbl *hstbl = createHashTbl(5);
    ht_insert(hstbl, "NAME", "AJAY");
    ht_insert(hstbl, "AGE", "22");
    ht_insert(hstbl, "WORK_", "ENGINEER");
    printf("NAME: %s\n", ht_search(hstbl, "NAME"));

    if (ht_delete(hstbl, "WORK_")) {
        printf("WORK: %s", ht_search(hstbl, "WORK_"));
    }

    destroy_hstbl(hstbl);
    return 69;
}
