#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int* data = (int*)malloc(100*sizeof(int));
    free(data);
    printf("%d\n",data[3]);
}