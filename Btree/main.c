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
static int icomp(int *a, int *b)
{
    int a_v = *(a);
    int b_v = *(b);
    if(a_v == b_v)
        return 0;
    else if(a_v < b_v)
        return -1;
    else
        return 1;
}

static void iprint(ibtree_t* node)
{
    printf("val:%d,cnt:%d\n", *(node->data), node->cnt);
}

int main(int argc, char** argv)
{
    {
        int i_v[] = {1,4,7,3,2,1,5,6,8,8,8,8,8};
        int n = sizeof(i_v)/sizeof(int);
        ibtree_t *ibtree = ibtree_create(icomp);
        for(int i=0; i<n; i++) {
            ibtree_add_node(ibtree, &i_v[i]);
        }
        int v = 8;
        ibtree_t* node = ibtree_find_node(ibtree, &v) ;
        if(node != NULL)
            printf("Cnt:%d\n", node->cnt);
        else
            printf("No!\n");
        ibtree_print_tree(ibtree, iprint);
        ibtree_destroy_tree(ibtree);
        /************************************************************************/
        /* This is very interesting. You can still de-reference pointer even    */
        /* after free it. So a good practice is to set freed pointer to be NULL */
        /************************************************************************/
        ibtree = NULL;
    }

    return 0;
}
