#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "linkedlist.h"
/*
cuando se usa 'getline' con la entrada estandar el salto de linea queda registrado.
esta funcion reemplaza el salto de linea por un fin de linea siempre que la linea
('line') tenga mas que un salto de linea.
retorna 0 si la linea ('line') solo tiene un salto de linea. Retorna 1 si la 
linea registrada tiene mas que un salto de linea y limpia esa linea. 
*/
int limpiarSaltoln(char *line)
{
    char *p = line;
    if (*line == '\n' || *line == 13)
    {
        return 0; //no limpia, linea vacía
    }
    while (*p != '\0')
    {
        if (*p == '\n' || *p == 13)
        {
            *p = '\0';
            break;
        }
        p++; //limpia
    }
    return 1;
}

int main(int argc, char *argv[])
{
    list_t lista;
    list_init(&lista);

    do
    {
        printf("Seleccione una opcion:\n");
        printf("1: Agregar elementos.\n");
        printf("2: Desplegar la lista completa.\n");

        size_t len = 0;
        char *entradaOp = NULL;
        FILE *archivo = stdin;

        if (getline(&entradaOp, &len, archivo) != -1)
        {
            int opcion = atoi(entradaOp);
            if (opcion != 0)
            {
                if (opcion == 1)
                {
                    printf("Ingrese el dato:\n");
                    fflush(stdin);
                    size_t len1 = 0;
                    char *dato = NULL;
                    FILE *archivo1 = stdin;

                    if (getline(&dato, &len1, archivo1) != -1)
                    {
                        if (limpiarSaltoln(dato) != 0)
                        {
                            //printf("debug0->len:%d-%s--\n", (int)strlen(dato), dato);
                            int len = strlen(dato);
                            if (len > 20)
                            {
                                printf("El texto ingresado no debe ser mayor a 20 caracteres.\n");
                                continue;
                            }
                            list_nondup_end_insert(&lista, dato);
                        }
                    }
                    else
                    {
                        printf("Error en la lectura de la entrada estandar.\n");
                    }
                    fflush(archivo1);
                }
                else if (opcion == 2)
                {
                    display(&lista);
                }
                else
                {
                    printf("opcion invalida.\n");
                }
            }
            else
            {
                printf("opcion invalida.\n");
            }
        }
        fflush(archivo);
    } while (1);
}