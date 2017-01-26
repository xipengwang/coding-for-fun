#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

void iswap(int v[], int a, int b)
{
    int tmp = 0;
    tmp = v[a];
    v[a] = v[b];
    v[b] = tmp;
}

void g_swap(void *v, int a, int b, size_t size)
{
    char *temp = calloc(1, size);
    memcpy(temp, (char*)v+a*size, size);
    memcpy((char*)v+a*size, (char*)v+b*size, size);
    memcpy((char*)v+b*size, temp, size);
    free(temp);
}

void iqsort(int v[], int left, int right)
{

    if(left >= right)
        return;
    int last = left;
    for(int i=left+1; i<=right; i++) {
        if(v[i] < v[left]) {
            iswap(v,i,++last);
        }
    }
    iswap(v, left, last);
    iqsort(v, left, last-1);
    iqsort(v, last+1, right);
}

void g_qsort(void *v, int left, int right, size_t size, int (*comp)(void*, void*))
{

    if(left >= right)
        return;
    int last = left;
    for(int i=left+1; i<=right; i++) {
        if(comp((char*)v+i*size,(char*)v+left*size)==-1) {
            g_swap(v,i,++last,size);
        }
    }
    g_swap(v, left, last, size);
    g_qsort(v, left, last-1, size, comp);
    g_qsort(v, last+1, right, size, comp);
}

static int icomp(void *a, void *b)
{
    int a_v = *((int*)a);
    int b_v = *((int*)b);
    if(a_v == b_v)
        return 0;
    else if(a_v < b_v)
        return -1;
    else
        return 1;
}

int main(int argc, char** argv)
{
    int v[] = {1,4,3,2,5};
    int n = sizeof(v)/sizeof(int);
    printf("Array size:%d \n", n);
    //iqsort(v, 0, n-1);
    g_qsort(v, 0, n-1, sizeof(int), icomp);
    for(int i=0; i<n; i++){
        printf("Array:%d \n", v[i]);
    }
    printf(("\n"));
    return 0;
}
