#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
/*
*/
int pillarDatos(char *nombreFichero, FILE *reporte)
{
    FILE *salida = stdout;
    if (reporte != NULL)
    {
        salida = reporte;
    }

    int lencarpeta = strlen(nombreFichero);
    int lenruta = 6 + lencarpeta + 7 + 1;
    char ruta[lenruta];
    strcpy(ruta, "/proc/");
    strcat(ruta, nombreFichero);
    strcat(ruta, "/status");
    //printf("la ruta es %s \n", ruta);

    FILE *archivo = fopen(ruta, "r");
    if (archivo == NULL)
    {
        return (1);
    }

    size_t len = 0;
    char *line = NULL;

    while (getline(&line, &len, archivo) != -1)
    {
        if (strstr(line, "Name") != NULL)
        {
            fprintf(salida, "%s", line);
        }
        else if (strstr(line, "State") != NULL)
        {
            fprintf(salida, "%s", line);
        }
        else if (strstr(line, "VmSize") != NULL)
        {
            fprintf(salida, "%s", line);
        }
        else if (strstr(line, "VmExe") != NULL)
        {
            fprintf(salida, "%s", line);
        }
        else if (strstr(line, "VmData") != NULL)
        {
            fprintf(salida, "%s", line);
        }
        else if (strstr(line, "VmStk") != NULL)
        {
            fprintf(salida, "%s", line);
        }
        else if (strstr(line, "voluntary_ctxt_switches") != NULL)
        {
            fprintf(salida, "%s", line);
        }
        else if (strstr(line, "nonvoluntary_ctxt_switches") != NULL)
        {
            fprintf(salida, "%s", line);
        }
    }

    fclose(archivo);

    return (0);
}

/*
Devuelve el numero total de caracteres que tiene un arreglo de strings desde la posicion 2, nunca se cuenta el caracter de fin de string de ninguno de los strings en el arreglo.
*/
int numeroLetras(char *arreglo[], int tamanoArreglo)
{
    int sum = 0;
    for (int i = 2; i < tamanoArreglo; i++)
    {
        sum += strlen(arreglo[i]);
    }
    return sum;
}
/*
Devuelve el nombre para el reporte de psinfo -r, el nombre será escrito en nombreArchivo
*/
char *getNombreReporte(char *arreglo[], int tamanoArreglo, char nombreArchivo[])
{
    strcpy(nombreArchivo, "psinfo-report");
    for (int i = 2; i < tamanoArreglo; i++)
    {
        strcat(nombreArchivo, "-");
        strcat(nombreArchivo, arreglo[i]);
    }
    strcat(nombreArchivo, ".info");
    return (nombreArchivo);
}

int getInfoProcesos(int argc, char *argv[], FILE *reporte)
{
    FILE *salida = stdout;
    if (reporte != NULL)
    {
        salida = reporte;
    }
    for (int i = 2; i < argc; i++)
    {
        fprintf(salida, "\nPid: %s\n", argv[i]);
        if (pillarDatos(argv[i], salida) == 1)
        {
            return (i);
        }
    }
    return (0);
}