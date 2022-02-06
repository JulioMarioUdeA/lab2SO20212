#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "metodoslab.h"


int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("Psinfo necesita argumentos\n"); //error
        exit(1);
    }
    else
    {
        if (strstr(argv[1], "-l"))
        {
            if (argc < 3)
            {
                printf("Psinfo -l necesita uno o mas argumentos\n"); //error
                exit(1);
            }
            printf("--INFORMACION RECOLECTADA!!!\n");
            int estat = getInfoProcesos(argc, argv, NULL);
            if (estat != 0)
            {
                printf("Error al abrir el archivo %s\n", argv[estat]); //error
                exit(1);
            }
            exit(0);
        }
        else if (strstr(argv[1], "-r"))
        {
            if (argc < 3)
            {
                printf("Psinfo -r necesita uno o mas argumentos\n"); //error
                exit(1);
            }
            int lenNombres = numeroLetras(argv, argc); //psinfo-report-10898-1342.info
            char nombreArchivo[13 + argc + lenNombres + 5 + 1];
            getNombreReporte(argv, argc, nombreArchivo);
            FILE *reporte = fopen(nombreArchivo, "w+");
            if (reporte == NULL)
            {
                printf("El reporte %s no existe\n", nombreArchivo); //error
                exit(1);
            }
            printf("Archivo de salida generado: %s\n",nombreArchivo);
            int estat = getInfoProcesos(argc, argv, reporte);
            if (estat != 0)
            {
                printf("Error al abrir el archivo %s\n", argv[estat]); //error
                exit(1);
            }
            fclose(reporte);
            exit(0);
        }
        else
        {
            if (argc != 2)
            {
                printf("Numero de argumentos invalido\n"); //error
                exit(1);
            }

            if (pillarDatos(argv[1], NULL) == 1)
            {
                printf("Error al abrir el archivo\n"); //error
                exit(1);
            }
            exit(0);
        }
    }
}