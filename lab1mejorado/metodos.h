#ifndef __METODOS_H_
#define __METODOS_H_

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

void list_init(list_t *l);
int list_nondup_end_insert(list_t *list, char **datos);
void imprimir(char **infos, char **datos, FILE *reporte, char *pid);
void liberar(char **datos);
void display(list_t *list, char **infos, FILE *salida, char **pids);
char* ArmarRuta(char *pid);
int limpiarSaltoln(char *line);
char* getDatoLimpio(char *linea);
char** pillarDatos(char *ruta);
int numeroLetras(char *arreglo[], int lenArreglo);
char* getNombreReporte(char *arreglo[], int tamanoArreglo, char nombreArchivo[]);

#endif