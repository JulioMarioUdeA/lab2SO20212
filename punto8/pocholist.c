#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

int main(int argc, char *argv[])
{
    list_t lista;
    list_init(&lista);

    for(int i = 0; i<81;i++){
        list_nondup_end_insert(&lista, i);
    }
}