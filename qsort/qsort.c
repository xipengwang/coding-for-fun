#include "qsort.h"


void g_swap(void *v, int a, int b, size_t size)
{
    char *temp = calloc(1, size);
    memcpy(temp, (char*)v+a*size, size);
    memcpy((char*)v+a*size, (char*)v+b*size, size);
    memcpy((char*)v+b*size, temp, size);
    free(temp);
}

/* deprecated
void g_qsort(void *v, int left, int right, size_t size, int (*comp)(void*, void*))
{

    if(left >= right)
        return;
    int last = left;
    for(int i = left + 1; i <= right; i++) {
        if(comp((char*)v+i*size,(char*)v+left*size)<0) {
            g_swap(v,i,++last,size);
        }
    }
    g_swap(v, left, last, size);
    g_qsort(v, left, last-1, size, comp);
    g_qsort(v, last+1, right, size, comp);
}
*/

void g_qsort(void *v, int n, size_t size, int (*comp)(void*, void*))
{

    if(n <= 0)
        return;
    int last = 0;
    for(int i = 1; i < n; i++) {
        if(comp((char*)v+i*size,(char*)v)<0) {
            g_swap(v,i,++last,size);
        }
    }
    g_swap(v, 0, last, size);
    g_qsort(v, last, size, comp);
    g_qsort((void*)((char*)v+(last+1)*size), n - last -1,size, comp);
}

void g_shell_sort(void *v, int n, size_t size, int (*comp)(void*, void*))
{
    for(int gap = n/2; gap > 0; gap /= 2) {
        for(int i = gap; i < n; i++) {
            for (int j = i - gap;
                 j >= 0 && comp(&v[j], &v[i]) < 0;
                 j -= gap) {
                g_swap(v, j, i, size);
            }
        }
    }
}
