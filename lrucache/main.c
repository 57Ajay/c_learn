#include "lrucache.h"
#include <stdio.h>

int main() {
    LRUCache *cache = lruCacheCreate(2);

    lruCachePut(cache, 1, 100);
    lruCachePut(cache, 2, 200);
    printf("Get 1: %d\n", lruCacheGet(cache, 1));

    lruCachePut(cache, 3, 300);
    printf("Get 2: %d\n", lruCacheGet(cache, 2));

    lruCachePut(cache, 4, 400);
    printf("Get 1: %d\n", lruCacheGet(cache, 1));
    printf("Get 3: %d\n", lruCacheGet(cache, 3));
    printf("Get 4: %d\n", lruCacheGet(cache, 4));

    lruCacheFree(cache);
    return 0;
}
