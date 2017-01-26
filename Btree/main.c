#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>



#define TNAME ibtree
#define TVALTYPE int
#include "btree_impl.h"
#undef TNAME
#undef TVALTYPE
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
    //int i_v[] = {1,4,7,3,2,1,5,6,8};
    int i_v[] = {2,1,5,7};
    int n = sizeof(i_v)/sizeof(int);
    ibtree_t *ibtree = ibtree_create(icomp);
    for(int i=0; i<n; i++) {
        ibtree_add_node(ibtree, &i_v[i]);
    }
    int v = 8;
    if(ibtree_find_node(ibtree, &v))
        printf("Yes\n");
    else
        printf("No!\n");
    //ibtree_destroy_tree(ibtree);
    free(ibtree->left_child->data);
    free(ibtree->left_child);
    printf("\n");
    return 0;
}
