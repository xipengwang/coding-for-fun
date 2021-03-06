#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

#include "array.h"
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


static int scomp(const void *a, const void *b)
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
    char *s[] = {
        "Hello_World",
        "Hello_UofM",
        "b",
        "a",
        "c",
        "d"
    };
    n = sizeof(s)/sizeof(char*);
    {
        garray_t *garray = garray_create(sizeof(char*));
        for(int i = 0; i < n; i++) {
            garray_add(garray, &s[i]);
        }
        garray_sort(garray, scomp);
        /* for(int i = 0; i < n; i++) { */
        /*     char* msg; */
        /*     if(garray_get(garray, i, &msg)) */
        /*         printf("%s\n", msg); */
        /* } */
        garray_map(garray, print_strings);
        garray_destroy(garray);
    }
    person_t persons[4]={
        {"Jonh", 3},
        {"Mary", 2},
        {"Ryan", 1},
        {"Eric", 0}
    };
    n = sizeof(persons)/sizeof(person_t);
    {
        garray_t *garray = garray_create(sizeof(person_t));
        for(int i = 0; i < n; i++) {
            garray_add(garray, &persons[i]);
        }

        garray_remove(garray, 1, NULL);
        garray_pop(garray, NULL);
        /* for(int i = 0; i < n; i++) { */
        /*     person_t dup_persons; */
        /*     if(garray_get(garray, i, &dup_persons)) */
        /*         printf("%s: %d\n", dup_persons.name, dup_persons.ID); */
        /* } */
        garray_map(garray, print_persons);
        garray_destroy(garray);
    }
    printf(("\n"));
    return 0;
}
