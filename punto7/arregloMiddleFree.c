#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int* data = (int*)malloc(100*sizeof(int));
    int* medio = (data+50);
    free(medio);
    printf("%d\n",data[3]);
}