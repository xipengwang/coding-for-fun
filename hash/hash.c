#include "hash.h"

ghash_t* ghash_create(size_t key_sz, size_t value_sz,
                      uint32_t hash(const void*),
                      int equals(const void*, const void*))
{
    ghash_t *ghash = (ghash_t*)calloc(1, sizeof(ghash_t));
    ghash->key_sz = key_sz;
    ghash->value_sz = value_sz;
    ghash->entry_sz = 1 + key_sz + value_sz; //first byte used as indicator.
    ghash->used = 0;
    ghash->capacity = DEFAULT_GHASH_CAPACITY;
    ghash->hash = hash;
    ghash->equals = equals;
    ghash->buf = (char*)calloc(DEFAULT_GHASH_CAPACITY, sizeof(char));
    if(ghash->buf == NULL) {
        free(ghash);
        return NULL;
    }
    return ghash;
}
void ghash_destroy(ghash_t *ghash)
{
    if(ghash == NULL)
        return;

    free(ghash->buf);
    free(ghash);
}

/**
   Some general hash functions
*/
uint32_t zhash_uint32_hash(const void *_a)
{
    assert(_a != NULL);

    uint32_t a = *((uint32_t*) _a);
    return a;
}
int zhash_uint32_equals(const void *_a, const void *_b)
{
    assert(_a != NULL);
    assert(_b != NULL);

    uint32_t a = *((uint32_t*) _a);
    uint32_t b = *((uint32_t*) _b);

    return a==b;
}

uint32_t zhash_uint64_hash(const void *_a)
{
    assert(_a != NULL);

    uint64_t a = *((uint64_t*) _a);
    return (uint32_t) (a ^ (a >> 32));
}
int zhash_uint64_equals(const void *_a, const void *_b)
{
    assert(_a != NULL);
    assert(_b != NULL);

    uint64_t a = *((uint64_t*) _a);
    uint64_t b = *((uint64_t*) _b);

    return a==b;
}

union uintpointer
{
    const void *p;
    uint32_t i;
};
uint32_t zhash_ptr_hash(const void *_a)
{
    assert(_a != NULL);

    union uintpointer ip;
    ip.p = * (void**)_a;

    // compute a hash from the lower 32 bits of the pointer (on LE systems)
    uint32_t hash = ip.i;
    hash ^= (hash >> 7);

    return hash;
}
int zhash_ptr_equals(const void *_a, const void *_b)
{
    assert(_a != NULL);
    assert(_b != NULL);

    const void * a = * (void**)_a;
    const void * b = * (void**)_b;
    return  a == b;
}

int zhash_str_equals(const void *_a, const void *_b)
{
    assert(_a != NULL);
    assert(_b != NULL);

    char *a = * (char**)_a;
    char *b = * (char**)_b;

    return !strcmp(a, b);
}
uint32_t zhash_str_hash(const void *_a)
{
    assert(_a != NULL);

    char *a = * (char**)_a;

    int32_t hash = 0;
    while (*a != 0) {
        hash = (hash << 7) + (hash >> 23);
        hash += *a;
        a++;
    }

    return (uint32_t) hash;
}
