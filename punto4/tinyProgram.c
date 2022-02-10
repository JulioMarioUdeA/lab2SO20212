#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char* palabra = (char*)malloc(10);
    strcpy(palabra,"hola");
    printf("\n%s\n",palabra);
}