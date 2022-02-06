#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char *ArmarRuta(char *pid)
{
    int numLetras = 13 + strlen(pid) + 1;
    char *ruta = (char *)malloc(numLetras);
    strcpy(ruta, "/proc/");
    strcat(ruta, pid);
    strcat(ruta, "/status");
    return ruta;
}
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
char *getDatoLimpio(char *linea)
{
    int lenb = strlen(linea);
    int dosPuntos = 0;
    int pos = 0;
    for (int i = 0; i < lenb; i++)
    {
        if (dosPuntos == 1 && linea[i] != 32 && linea[i] != 9)
        {
            pos = i;
            break;
        }
        if (linea[i] == ':')
        {
            dosPuntos = 1;
        }
    }
    int lenDato = (lenb - pos) + 1;
    char *dato = (char *)malloc(lenDato);
    dato[lenDato - 1] = '\0';
    strcpy(dato, (linea + pos));
    limpiarSaltoln(dato);
    return dato;
}
char **pillarDatos(char *ruta)
{
    char **datos = (char **)malloc(9 * sizeof(char *));
    datos[8] = NULL;

    FILE *archivo = fopen(ruta, "r");
    if (archivo == NULL)
    {
        return NULL;
    }

    size_t len = 0;
    char *line = NULL;
    int pos = -1;
    while (getline(&line, &len, archivo) != -1)
    {
        if (strstr(line, "Name") != NULL)
        {
            pos = 0;
        }
        else if (strstr(line, "State") != NULL)
        {
            pos = 1;
        }
        else if (strstr(line, "VmSize") != NULL)
        {
            pos = 2;
        }
        else if (strstr(line, "VmExe") != NULL)
        {
            pos = 3;
        }
        else if (strstr(line, "VmData") != NULL)
        {
            pos = 4;
        }
        else if (strstr(line, "VmStk") != NULL)
        {
            pos = 5;
        }
        else if (strstr(line, "nonvoluntary_ctxt_switches") != NULL)
        {
            pos = 7;
        }
        else if (strstr(line, "voluntary_ctxt_switches") != NULL)
        {
            pos = 6;
        }

        if (pos != -1)
        {
            datos[pos] = getDatoLimpio(line);
            //printf(">>%d-%s", pos, datos[pos]);
            pos = -1;
        }
    }
    fclose(archivo);

    return datos;
}

int main(int argc, char *argv[])
{
    char infos[][80] = {"Nombre del proceso: ",
                        "Estado: ",
                        "Tamanio total de la imagen de memoria: ",
                        "   Tamanio de la memoria en la region TEXT: ",
                        "   Tamanio de la memoria en la region DATA: ",
                        "   Tamanio de la memoria en la region STACK: ",
                        "Numero de cambios de contexto realizados (voluntarios - no voluntarios): "};

    if (argc == 2)
    {
        char *ruta = ArmarRuta(argv[1]);
        printf("la ruta es %s \n", ruta);
        char **datos = pillarDatos(ruta);
        int i = 0;
        while (i != 6)
        {
            printf("%s%s\n", infos[i], datos[i]);
            free(datos[i]);
            i++;
        }
        printf("%s%s - %s\n", infos[i], datos[i], datos[i + 1]);
        free(datos[i]);
        free(datos);
        exit(0);
    }
    exit(1);
}