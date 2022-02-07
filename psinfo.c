#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct __node_t node_t;
typedef struct __list_t list_t;

struct __node_t
{
    char **datos;
    node_t *next;
};

struct __list_t
{
    node_t *head;
};

void list_init(list_t *l)
{
    l->head = NULL;
}

void imprimir(char **infos, char **datos, FILE *reporte)
{
    FILE *salida = stdout;
    if (reporte != NULL)
    {
        salida = reporte;
    }
    for (int i = 0; i < 6; i++)
    {
        fprintf(salida, "%s%s\n", infos[i], datos[i]);
    }
    fprintf(salida, "%s%s - %s\n", infos[6], datos[6], datos[7]);
}

/*
This function realize the insert of an element on a list of type list_t
list_t is a list of elements of type node_t
A node consist of an atirbute char* and a pointer to another node_t element

If you try to insert an element already present in the list, so the element is nos inserted and the function return -1
When an element is inserted the function return the number of elements of the list
*/
int list_nondup_end_insert(list_t *list, char **datos)
{
    node_t *tmp, *tmp1, *tmp2;
    tmp = list->head;
    int count = 0;
    if (tmp == NULL)
    {
        tmp1 = (node_t *)malloc(sizeof(node_t));
        tmp1->datos = datos;
        tmp1->next = NULL;
        list->head = tmp1;
        count++;
        return count;
    }
    else
    {
        do
        {
            tmp2 = tmp;
            count++;
            tmp = tmp->next;
        } while (tmp != NULL);
        tmp1 = (node_t *)malloc(sizeof(node_t));
        tmp1->datos = datos;
        tmp1->next = NULL;
        tmp2->next = tmp1;
        count++;
    }
    return count;
}

/*
This function simply print the elements of the list
*/
void display(list_t *list, char **infos, FILE *salida)
{
    node_t *tmp;
    tmp = list->head;
    while (tmp != NULL)
    {
        imprimir(infos, tmp->datos, salida);
        tmp = tmp->next;
    }
}

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
        return 0; // no limpia, linea vacía
    }
    while (*p != '\0')
    {
        if (*p == '\n' || *p == 13)
        {
            *p = '\0';
            break;
        }
        p++; // limpia
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
            pos = -1;
        }
    }
    fclose(archivo);

    return datos;
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
        printf("error: psinfo necesita por lo menos un argumento");
        exit(1);
    }
    else
    {
        if (strcmp(argv[1], "-l") == 0)
        {
            if (argc < 3)
            {
                printf("error: psinfo -l necesita argumentos");
                exit(1);
            }
            list_t lista;
            list_init(&lista);
            for (int i = 2; i < argc; i++)
            {
                char *ruta = ArmarRuta(argv[i]);
                char **datos = pillarDatos(ruta);
                if (datos == NULL)
                {
                    printf("error: el fichero %s no se encuentra", ruta);
                    exit(1);
                }
                list_nondup_end_insert(&lista, datos);
            }
            printf("\n-- Informacion recolectada!");
            display(&lista, infos, NULL);
        }
        else if (strcmp(argv[1], "-r") == 0)
        {
            if (argc < 3)
            {
                printf("error: psinfo -r necesita argumentos");
                exit(1);
            }
            int lenNombres = numeroLetras(argv, argc); // psinfo-report-10898-1342.info
            char nombreArchivo[13 + argc + lenNombres + 5 + 1];
            getNombreReporte(argv, argc, nombreArchivo);
            FILE *reporte = fopen(nombreArchivo, "w+");
            if (reporte == NULL)
            {
                printf("El reporte %s no existe\n", nombreArchivo); // error
                exit(1);
            }
            list_t lista;
            list_init(&lista);
            for (int i = 2; i < argc; i++)
            {
                char *ruta = ArmarRuta(argv[i]);
                char **datos = pillarDatos(ruta);
                if (datos == NULL)
                {
                    printf("error: el fichero %s no se encuentra", ruta);
                    exit(1);
                }
                list_nondup_end_insert(&lista, datos);
            }
            display(&lista, infos, reporte);
        }
        else
        {
            if (argc > 2)
            {
                printf("error: psinfo solo requiere un argumento");
                exit(1);
            }
            char *ruta = ArmarRuta(argv[1]);
            char **datos = pillarDatos(ruta);
            if (datos == NULL)
            {
                printf("error: el fichero %s no se encuentra", ruta);
                exit(1);
            }
            imprimir(infos, datos, NULL);
            exit(0);
        }
    }
}