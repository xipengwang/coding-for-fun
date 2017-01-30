#ifndef _COMMON_HASH_H
#define _COMMON_HASH_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

#define GHASH_FACTOR 2
#define DEFAULT_GHASH_CAPACITY 8

#ifdef __cplusplus
extern "C" {
#endif

    struct ghash {
        size_t key_sz;
        size_t value_sz;
        int entry_sz; //1+key_sz+value_sz;

        int used;
        int capacity;
        char *buf;

        uint32_t(*hash)(const void*);
        int (*equals)(const void*, const void*);
    };
    typedef struct ghash ghash_t;

    ghash_t* ghash_create(size_t key_sz, size_t value_sz,
                          uint32_t hash(const void*),
                          int equals(const void*, const void*));


    uint32_t zhash_uint32_hash(const void *_a);
    int zhash_uint32_equals(const void *_a, const void *_b);
    uint32_t zhash_uint64_hash(const void *_a);
    int zhash_uint64_equals(const void *_a, const void *_b);
    uint32_t zhash_ptr_hash(const void *_a);
    int zhash_ptr_equals(const void *_a, const void *_b);
    int zhash_str_equals(const void *_a, const void *_b);
    uint32_t zhash_str_hash(const void *_a);

#ifdef __cplusplus
}
#endif

#endif