#include <stdlib.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
    const int NUM_HEIGHTS = 10;
    int *heights = malloc(NUM_HEIGHTS * sizeof(*heights));
    for (int i = 0; i < NUM_HEIGHTS; i++)
    {
        if (heights == NULL)
        {
            heights = malloc(NUM_HEIGHTS * sizeof(*heights));
        }
    }
    free(heights);
}
