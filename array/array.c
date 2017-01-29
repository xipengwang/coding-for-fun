#include "array.h"

garray_t* garray_create(size_t el_sz)
{
    garray_t *garray = calloc(1, sizeof(garray_t));
    garray->buf = (char*)calloc(DEFAULT_GARRAY_CAPACITY, el_sz);
    if(garray->buf == NULL)
        return NULL;
    garray->capacity = DEFAULT_GARRAY_CAPACITY;
    garray->used = 0;
    garray->el_sz = el_sz;
    return garray;

}

int garray_add(garray_t *garray, void* elem)
{
    if(garray->used == garray->capacity) {
        garray->capacity *= 2;
        garray->buf = (char*)realloc(garray->buf, garray->capacity);
        if(garray->buf == NULL)
            return 0;
    }
    memcpy((char*)garray->buf + garray->used*garray->el_sz,
           (char*)elem, garray->el_sz);
    garray->used++;
    return 1;
}

int garray_get(garray_t *garray, int idx, void* elem)
{
    if(idx >= garray->used)
        return 0;

    memcpy((char*)elem,
           (char*)garray->buf + idx*garray->el_sz,
           garray->el_sz);
    return 1;
}

void garray_destroy(garray_t *garray)
{
    free(garray->buf);
    free(garray);
}
