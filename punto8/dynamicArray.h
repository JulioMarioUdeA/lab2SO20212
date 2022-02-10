#ifndef __ARRAYSTRUCT_H_
#define __ARRAYSTRUCT_H_
#include <stdlib.h>

typedef struct dynamicArray
{
    int *array;
    size_t used;
    size_t size;
} Array;

void initArray(Array *a, size_t initialSize);
void insertArray(Array *a, int element);
void freeArray(Array *a);
#endif