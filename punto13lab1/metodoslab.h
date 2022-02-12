#ifndef __METODOSLAB_H_
#define __METODOSLAB_H_

int pillarDatos(char *nombreFichero, FILE *reporte);
int numeroLetras(char *arreglo[], int tamanoArreglo);
char *getNombreReporte(char *arreglo[], int tamanoArreglo, char nombreArchivo[]);
int getInfoProcesos(int argc, char *argv[], FILE *reporte);

#endif