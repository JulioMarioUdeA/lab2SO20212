#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "metodos.h"

int main(int argc, char *argv[])
{
    char *infos[80] = {"Nombre del proceso: ",
                       "Estado: ",
                       "Tamanio total de la imagen de memoria: ",
                       "   Tamanio de la memoria en la region TEXT: ",
                       "   Tamanio de la memoria en la region DATA: ",
                       "   Tamanio de la memoria en la region STACK: ",
                       "Numero de cambios de contexto realizados (voluntarios - no voluntarios): "};

    if (argc == 1)
    {
        printf("error: psinfo necesita un argumento\n");
        printf("\n./psinfo <PID>\nejemplo:\n./psinfo 104\n");
        exit(1);
    }
    else
    {
        if (strcmp(argv[1], "-l") == 0)
        {
            if (argc < 3)
            {
                printf("error: psinfo -l necesita argumentos\n");
                printf("\n./psinfo -l <PID> <PID> ... <PID>\nejemplo:\n./psinfo -l 104 201 ... 102\n");
                exit(1);
            }
            list_t lista;
            list_init(&lista);
            for (int i = 2; i < argc; i++)
            {
                char *ruta = ArmarRuta(argv[i]);
                char **datos = pillarDatos(ruta);
                if (strstr(datos[0],"no data") != NULL)
                {
                    printf("error: el fichero %s no se encuentra\n", ruta);
                    printf("use el comando ps aux para mirar PIDs validos\n");
                    // continue;
                }
                list_nondup_end_insert(&lista, datos);
            }
            printf("\n-- Informacion recolectada!\n");
            display(&lista, infos, NULL, argv);
        }
        else if (strcmp(argv[1], "-r") == 0)
        {
            if (argc < 3)
            {
                printf("error: psinfo -r necesita argumentos\n");
                printf("\n./psinfo -r <PID> <PID> ... <PID>\nejemplo:\n./psinfo -r 104 201 ... 102\n");
                exit(1);
            }
            int lenNombres = numeroLetras(argv, argc); // psinfo-report-10898-1342.info
            char nombreArchivo[13 + argc + lenNombres + 5 + 1];
            getNombreReporte(argv, argc, nombreArchivo);
            FILE *reporte = fopen(nombreArchivo, "w+");
            if (reporte == NULL)
            {
                printf("error: el reporte %s no fue creado\n", nombreArchivo); // error
                exit(1);
            }
            list_t lista;
            list_init(&lista);
            for (int i = 2; i < argc; i++)
            {
                char *ruta = ArmarRuta(argv[i]);
                char **datos = pillarDatos(ruta);
                if (strstr(datos[0],"no data") != NULL)
                {
                    printf("error: el fichero %s no se encuentra\n", ruta);
                    printf("use el comando ps aux para mirar PIDs validos\n");
                    // continue;
                }
                list_nondup_end_insert(&lista, datos);
            }
            printf("\n-- reporte %s generado!\n", nombreArchivo);
            display(&lista, infos, reporte, argv);
        }
        else
        {
            if (argc > 2)
            {
                printf("error: psinfo requiere un unico argumento\n");
                printf("\n./psinfo <PID>\nejemplo:\n./psinfo 104\n");
                exit(1);
            }
            char *ruta = ArmarRuta(argv[1]);
            char **datos = pillarDatos(ruta);
            if (strstr(datos[0],"no data") != NULL)
            {
                printf("error: el fichero %s no se encuentra\n", ruta);
                printf("use el comando ps aux para mirar PIDs validos\n");
                exit(1);
            }
            imprimir(infos, datos, NULL, NULL);
            exit(0);
        }
    }
}