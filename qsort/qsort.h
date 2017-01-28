#ifndef _QSORT_H
#define _QSORT_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

    struct person {
        char* name;
        int ID;
    };
    typedef struct person person_t;

    void g_swap(void *v, int a, int b, size_t size);
    void g_qsort(void *v, int total_elements, size_t size, int (*comp)(void*, void*));
    void g_shell_sort(void *v, int total_elements, size_t size, int (*comp)(void*, void*));

#ifdef __cplusplus
}
#endif

#endif
