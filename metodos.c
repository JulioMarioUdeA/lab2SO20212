#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "metodos.h"

void list_init(list_t *l)
{
    l->head = NULL;
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
esta funcion imprime en reporte la concatenacion de cada uno de los elementos de infos con
cada uno de los elementos de datos. si reporte es null imprime en la salida estandar, si pid
es null no lo imprime y si es diferente de null lo imprime y ademas en ambos casos imrpime
la demas informacion de infos y datos.
*/
void imprimir(char **infos, char **datos, FILE *reporte, char *pid)
{
    FILE *salida = stdout;
    if (reporte != NULL)
    {
        salida = reporte;
    }
    if (pid != NULL)
    {
        fprintf(salida, "\nPID: %s\n", pid);
    }
    for (int i = 0; i < 6; i++)
    {
        fprintf(salida, "%s%s\n", infos[i], datos[i]);
    }
    fprintf(salida, "%s%s - %s\n", infos[6], datos[6], datos[7]);
}
/*
This function simply print the elements of the list. usa el metodo imprimir(params)
*/
void display(list_t *list, char **infos, FILE *salida, char **pids)
{
    node_t *tmp;
    tmp = list->head;
    if (pids == NULL)
    {
        while (tmp != NULL)
        {
            imprimir(infos, tmp->datos, salida, NULL);
            tmp = tmp->next;
        }
    }
    else
    {
        int i = 2;
        while (tmp != NULL)
        {
            imprimir(infos, tmp->datos, salida, pids[i]);
            i++;
            tmp = tmp->next;
        }
    }
}
/*
esta funcion concatena "/proc/" con el parametro pid y a eso le concatena "/status"
retorna el string concatenado, ejemplo: /proc/34/status
*/
char *ArmarRuta(char *pid)
{
    int numLetras = 13 + strlen(pid) + 1;
    char *ruta = (char *)malloc(numLetras);
    strcpy(ruta, "/proc/");
    strcat(ruta, pid);
    strcat(ruta, "/status");
    return ruta;
}
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
/*
este metodo devuelve el dato limpio del parametro line.
el dato limpio es el dato que hay despues del caracter ":" en line y que no 
contiene espacios por la derecha e izquieda ni contiene saltos de linea.
ejemplo:para la linea '<\tab>Vmsize: 140 kb<\n>' devuelve '140 kb'.
*/
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
/*
este metodo va a la ruta especificada por el parametro ruta y extrae los datos de interes que son
Name, State, VmSize, VmExe, VmData, VmStk, voluntary_ctxt_switches, nonvoluntary_ctxt_switches.
devuelve un vector con los datos en ese orden y con un null en la ultima posicion.
si la ruta no existe el vector que devuelve contendrá en todas las posiciones el string "no data"
excepto en la ultima posicion que igual tendrá un null.
*/
char **pillarDatos(char *ruta)
{
    char **datos = (char **)malloc(9 * sizeof(char *));
    datos[8] = NULL;

    FILE *archivo = fopen(ruta, "r");
    if (archivo == NULL)
    {
        for (int i = 0; i < 8; i++)
        {
            datos[i] = (char *)malloc(10);
            strcpy(datos[i], "no data");
        }
        return datos;
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
Devuelve el numero total de caracteres que tiene un arreglo de strings desde la posicion 2. 
nunca se cuenta el caracter de fin de string de ninguno de los strings en el arreglo.
*/
int numeroLetras(char *arreglo[], int lenArreglo)
{
    int sum = 0;
    for (int i = 2; i < lenArreglo; i++)
    {
        sum += strlen(arreglo[i]);
    }
    return sum;
}
/*
Devuelve el nombre para el reporte usado para psinfo -r, el nombre será escrito en nombreArchivo
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