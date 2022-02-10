#include <stdlib.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
    const int NUM_HEIGHTS = 3;
    int *heights = malloc(NUM_HEIGHTS);
    for (int i = 0; i < NUM_HEIGHTS; i++)
    {
        heights[i] = i * i;
        printf("%d: %d\n", i, heights[i]);
        free(heights);
    }
}