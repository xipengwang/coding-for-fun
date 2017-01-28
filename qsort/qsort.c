#include "qsort.h"


void g_swap(void *v, int a, int b, size_t size)
{
    char *temp = calloc(1, size);
    memcpy(temp, (char*)v+a*size, size);
    memcpy((char*)v+a*size, (char*)v+b*size, size);
    memcpy((char*)v+b*size, temp, size);
    free(temp);
}

void g_qsort(void *v, int left, int right, size_t size, int (*comp)(void*, void*))
{

    if(left >= right)
        return;
    int last = left;
    for(int i=left+1; i<=right; i++) {
        if(comp((char*)v+i*size,(char*)v+left*size)<0) {
            g_swap(v,i,++last,size);
        }
    }
    g_swap(v, left, last, size);
    g_qsort(v, left, last-1, size, comp);
    g_qsort(v, last+1, right, size, comp);
}
