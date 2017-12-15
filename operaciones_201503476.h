#ifndef OPERACIONES_201503476_H
#define OPERACIONES_201503476_H
#include<cadenas_201503476.h>
#include<componentes_201503476.h>
#include<funtablenom_201503476.h>
//CREAR
void crear(MBR mbr, char rglob[], char rdiskGlobal[], int indiceTabla);

int creameCarpeta(MBR mbr, char rutaGlob[], char path[], int indice, int typeRoute, char name[]);

int buscaIndexDisponible(int PTinit, char ruta[]);

/*-------------REPORTE DE NOMBRES ----------------------------------------*/
void escribeReporteNobres(int x, FILE *f, MBR mbr, FILE *lee);
/*-------------REPORTE DE NOMBRES ----------------------------------------*/


#endif // OPERACIONES_201503476_H
