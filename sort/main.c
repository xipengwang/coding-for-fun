#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

#include "sort.h"

//#define SORT g_qsort
//#define SORT g_shell_sort
//#define SORT g_bubble_sort
#define SORT g_heap_sort

struct person {
    char* name;
    int ID;
};
typedef struct person person_t;


static int icomp(const void *a, const void *b)
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

static int scomp(const void *a, const void *b)
{
    char **a_s = (char**)a;
    char **b_s = (char**)b;
    //printf("%s:\n", *a_s,*b_s);
    return strcmp(*a_s, *b_s);
}

static int person_comp(const void *a, const void *b)
{
    person_t *a_p = (person_t*)a;
    person_t *b_p = (person_t*)b;
    if(a_p->ID == b_p->ID)
        return 0;
    else if(a_p->ID < b_p->ID)
        return -1;
    else
        return 1;
}

int main(int argc, char** argv)
{
    int v[] = {1,4,3,2,5};
    int n = sizeof(v)/sizeof(int);
    printf("Array size:%d \n", n);
    SORT(v, n, sizeof(int), icomp);
    for(int i=0; i<n; i++){
        printf("Int Array:%d \n", v[i]);
    }
    printf(("\n"));

    char *s[] = {
        "Hello_World",
        "Hello_UofM",
        "b",
        "a",
        "c",
        "d"
    };
    n = sizeof(s)/sizeof(char*);
    SORT(s, n, sizeof(char*), scomp);
    for(int i=0; i<n; i++){
        printf("String Array:%s \n", s[i]);
    }
    printf(("\n"));

    person_t persons[3]={
        {"Jonh", 3},
        {"Mary", 2},
        {"Ryan", 1}
    };
    n = sizeof(persons)/sizeof(person_t);
    SORT(persons, n, sizeof(person_t), person_comp);
    for(int i=0; i<n; i++){
        printf("Person Array:%s: %d \n", persons[i].name, persons[i].ID);
    }
    printf(("\n"));
    return 0;
}
