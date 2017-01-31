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

ghash_t* ghash_create_capacity(size_t key_sz, size_t value_sz,
                               uint32_t hash(const void*),
                               int equals(const void*, const void*),
                               int size)
{
    ghash_t *ghash = (ghash_t*)calloc(1, sizeof(ghash_t));
    ghash->key_sz = key_sz;
    ghash->value_sz = value_sz;
    ghash->entry_sz = 1 + key_sz + value_sz; //first byte used as indicator.
    ghash->used = 0;
    if(ghash->capacity <= DEFAULT_GHASH_CAPACITY)
        ghash->capacity = DEFAULT_GHASH_CAPACITY;
    else {
        if(size & 0x01)
            ghash->capacity = size + 1;
        else
            ghash->capacity = size;
    }
    ghash->hash = hash;
    ghash->equals = equals;
    ghash->buf = (char*)calloc(ghash->capacity, sizeof(char));
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

int ghash_put(ghash_t *ghash, void *key, void *value, void *old_key, void *old_value)
{
    uint32_t hash_value = ghash->hash(key);
    uint32_t idx = hash_value & (ghash->capacity - 1);
    while(ghash->buf[idx*ghash->entry_sz]) {
        void *this_key = &ghash->buf[idx*ghash->entry_sz+1];
        void *this_value = &ghash->buf[idx*ghash->entry_sz+1+ghash->key_sz];
        if(ghash->equals(key, this_key)) { //find same key entry
            if(old_key)
                memcpy(old_key, this_key, ghash->key_sz);
            if(old_value)
                memcpy(old_value, this_value, ghash->value_sz);
            memcpy(this_value, value, ghash->value_sz);
            return 0;
        }
        idx = (idx + 1) & (ghash->capacity - 1);
    }

    ghash->buf[idx*ghash->entry_sz] = 1;
    memcpy(&ghash->buf[idx*ghash->entry_sz + 1], key, ghash->key_sz);
    memcpy(&ghash->buf[idx*ghash->entry_sz + 1 + ghash->key_sz], value, ghash->value_sz);
    ghash->used++;
    //resize zhash if needed
    if(ghash->used * GHASH_FACTOR > ghash->capacity) {
        ghash_t *new_ghash = ghash_create_capacity(ghash->key_sz, ghash->value_sz,
                                                   ghash->hash,
                                                   ghash->equals,
                                                   ghash->capacity * GHASH_FACTOR);
        for(int i = 0; i < ghash->capacity; i++) {
            if(ghash->buf[i*ghash->entry_sz]){
                void *this_key = &ghash->buf[i*ghash->entry_sz + 1];
                void *this_value = &ghash->buf[i*ghash->entry_sz + 1 + ghash->key_sz];
                if (!ghash_put(new_ghash, this_key, this_value, NULL, NULL))
                    assert(0); // shouldn't already be present.
            }
        }

        ghash_t tmp;
        memcpy(&tmp, new_ghash, sizeof(ghash_t));
        memcpy(ghash, new_ghash, sizeof(ghash_t));
        memcpy(new_ghash, &tmp, sizeof(ghash_t));
        ghash_destroy(new_ghash);
    }

    return 1;
}


int ghash_get(ghash_t *ghash, void *key, void *out_value)
{
    uint32_t hash_value = ghash->hash(key);
    uint32_t idx = hash_value & ghash->capacity;
    while(ghash->buf[idx*ghash->entry_sz]) {
        void *this_key = &ghash->buf[idx*ghash->entry_sz+1];
        if(ghash->equals(key, this_key)) { //find same key entry
            memcpy(out_value, this_value, ghash->value_sz);
            return 1;
        }
        idx = (idx + 1) & (ghash->capacity - 1);
    }
    return 0;
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
int zhash_str_equals(const void *_a, const void *_b)
{
    assert(_a != NULL);
    assert(_b != NULL);

    char *a = * (char**)_a;
    char *b = * (char**)_b;

    return !strcmp(a, b);
}
