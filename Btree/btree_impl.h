#include<string.h>
#include <stdlib.h>

#ifndef NULL
#define NULL ((void*)0)
#endif
/**
   Define TNAME and TVALTYPE;
   Such as:
   #define TNAME string_btree
   #define TVALTYPE char
   Then:
   TTYPENAME_T = string_btree_t
   TTYPENAME_T = char
*/


#define S_CONCAT(root, suffix) root ## _ ## suffix
#define CONCAT(root, suffix) S_CONCAT(root, suffix)
#define APPEND(suffix) CONCAT(TNAME, suffix)

#define TTYPENAME_T APPEND(t)
typedef struct TNAME TTYPENAME_T;

struct TNAME
{
    TVALTYPE *data;
    TTYPENAME_T *left_child;
    TTYPENAME_T *right_child;
    int (*comp)(void*, void*);
    int cnt;
};

TTYPENAME_T* APPEND(create)(int (*comp)(void*, void*)){
    TTYPENAME_T* root = calloc(1, sizeof(TTYPENAME_T));
    root->data = NULL;
    root->left_child = NULL;
    root->right_child = NULL;
    root->comp = comp;
    return root;
}

void APPEND(add_node)(TTYPENAME_T *root, TVALTYPE *data)
{
    assert(root != NULL);
    if(root->data == NULL) {
        root->data = calloc(1, sizeof(TVALTYPE));
        memcpy(root->data, data, sizeof(TVALTYPE));
        return;
    }
    TTYPENAME_T *node = root;
    while(1) {
        if(root->comp(node->data, data) > 0) { //go left
            if(node->left_child == NULL) {
                TTYPENAME_T* new_node = calloc(1, sizeof(TTYPENAME_T));
                new_node->data = calloc(1, sizeof(TVALTYPE));
                memcpy(new_node->data, data, sizeof(TVALTYPE));
                new_node->left_child = NULL;
                new_node->right_child = NULL;
                new_node->comp = NULL;
                new_node->cnt = 0;
                node->left_child = new_node;
                return;
            }
            node = node->left_child;
        } else if(root->comp(node->data, data) == 0) {
            node->cnt++;
            return;
        } else { //go right
            if(node->right_child == NULL) {
                TTYPENAME_T* new_node = calloc(1, sizeof(TTYPENAME_T));
                new_node->data = calloc(1, sizeof(TVALTYPE));
                memcpy(new_node->data, data, sizeof(TVALTYPE));
                new_node->left_child = NULL;
                new_node->right_child = NULL;
                new_node->comp = NULL;
                new_node->cnt = 0;
                node->right_child = new_node;
                return;
            }
            node = node->right_child;
        }
    }

}

int APPEND(find_node)(TTYPENAME_T *root, TVALTYPE *data){
    TTYPENAME_T *node = root;
    while(node != NULL) {
        if(root->comp(node->data, data) == 0) {
            return 1;
        } else if(root->comp(node->data, data) > 0) {
            node = node->left_child;
        } else { //go right
            node = node->right_child;
        }
    }
    return 0;
}


//user need to release return data memory
int APPEND(remove_node)(TTYPENAME_T *root, TVALTYPE *data){
    TTYPENAME_T *node = root;
    while(node != NULL) {
        if(root->comp(node->data, data) == 0) {
            free(node->data);
            free(node);
            node = NULL;
            return 1;
        } else if(root->comp(node->data, data) > 0) {
            node = node->left_child;
        } else { //go right
            node = node->right_child;
        }
    }
    return 0;
}

void APPEND(destroy_tree)(TTYPENAME_T *root){
    if(root == NULL)
        return;
    APPEND(destroy_tree)(root->left_child);
    APPEND(destroy_tree)(root->right_child);
    free(root->data);
    free(root);
    root = NULL;
    return;
}
