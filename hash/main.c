#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

#include "hash.h"
struct person {
    char* name;
    int ID;
};
typedef struct person person_t;

void print_strings(void *s) {
    char** p = (char**)s;
    printf("%s\n", *p);
}

void print_persons(void *person) {
    person_t* p = (person_t*)person;
    printf("%s:%d\n", p->name, p->ID);
}


int scomp(const void *a, const void *b)
{
    char **a_s = (char**)a;
    char **b_s = (char**)b;
    //printf("%s:\n", *a_s,*b_s);
    return strcmp(*a_s, *b_s);
}

int main(int argc, char** argv)
{
    int v[] = {1,4,3,2,5};
    int n = sizeof(v)/sizeof(int);
    ghash_t *ghash = ghash_create(sizeof(uint32_t), sizeof(char*), ghash_uint32_hash, ghash_uint32_equals);
    char *s[] = {
        "Hello_World",
        "Hello_UofM",
        "b",
        "a",
        "c",
        "d"
    };
    n = sizeof(s)/sizeof(char*);
    for(int i = 0; i < n; i++) {
        ghash_put(ghash, &i, &s[i], NULL, NULL);
    }

    ghash_iter_t *ghash_iter = ghash_iter_create(ghash);
    char *out_s;
    uint32_t key;
    while(ghash_iter_next(ghash_iter, &key, &out_s)) {
        printf("%d:%s \n", key, out_s);
    }

    /* for(int i = 0; i < n; i++) { */
    /*     char *s; */
    /*     ghash_get(ghash, &i, &s); */
    /*     printf("%s \n", s); */
    /* } */
    ghash_destroy(ghash);

    person_t persons[4]={
        {"Jonh", 3},
        {"Mary", 2},
        {"Ryan", 1},
        {"Eric", 0}
    };
    n = sizeof(persons)/sizeof(person_t);
    printf(("\n"));
    return 0;
}
