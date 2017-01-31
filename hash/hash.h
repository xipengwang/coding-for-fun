#ifndef _COMMON_HASH_H
#define _COMMON_HASH_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

#define GHASH_FACTOR 2
#define DEFAULT_GHASH_CAPACITY 16

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


    void ghash_destroy(ghash_t *ghash);
    int ghash_put(ghash_t *ghash, void *key, void *value, void *old_key, void *old_value);
    int ghash_get(ghash_t *ghash, void *key, void *out_value);
    uint32_t ghash_uint32_hash(const void *_a);
    int ghash_uint32_equals(const void *_a, const void *_b);
    uint32_t ghash_uint64_hash(const void *_a);
    int ghash_uint64_equals(const void *_a, const void *_b);
    uint32_t ghash_ptr_hash(const void *_a);
    int ghash_ptr_equals(const void *_a, const void *_b);
    int ghash_str_equals(const void *_a, const void *_b);
    uint32_t ghash_str_hash(const void *_a);

#ifdef __cplusplus
}
#endif

#endif
