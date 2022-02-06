#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{

    char *b = "name: bash";
    int lenb = strlen(b);
    int dosPuntos = 0;
    int pos = 0;
    for (int i = 0; i < lenb; i++)
    {
        if (dosPuntos == 1 && b[i] != ' ')
        {
            pos = i;
            break;
        }
        if (b[i] == ':')
        {
            dosPuntos = 1;
        }
    }
    int lenDato = (lenb - pos) + 1;
    char *dato = (char *)malloc(lenDato);
    dato[lenDato - 1] = '\0';
    strcpy(dato, (b + pos));
    printf("---%s", dato);
}