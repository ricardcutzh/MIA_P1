#ifndef FUNTABLENOM_201503476_H
#define FUNTABLENOM_201503476_H
#include<cadenas_201503476.h>
#include<componentes_201503476.h>

//METODOS PARA TABLAS DE NOMBRES

int estaDisponibleTabla(int PTinit, char ruta[]);
void marcaTablaOcupada(int PTinit, char ruta[]);
int buscaPunteroDeCarpeta(int PTinit, char ruta[], char nombre[], int puntTabla);


//REPORTE DE TABLAS
void escribeReporteDeTabla(FILE *f, int PTiniti, FILE *lectura);

#endif // FUNTABLENOM_201503476_H
