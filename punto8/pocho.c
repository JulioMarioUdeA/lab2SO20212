#include <stdio.h>
#include <stdlib.h>
#include "dynamicArray.h"

int main(int argc, char* argv[]){
    Array a;
    int i;
    initArray(&a, 5);
    for(i = 0; i<81;i++){
        insertArray(&a,i);
    }
    printf("%d\n",(int)a.size);
    freeArray(&a);
}