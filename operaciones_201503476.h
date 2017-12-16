#ifndef OPERACIONES_201503476_H
#define OPERACIONES_201503476_H
#include<cadenas_201503476.h>
#include<componentes_201503476.h>
#include<funtablenom_201503476.h>
#include<datastructure_201503476.h>
//CREAR
void crear(MBR mbr, char rglob[], char rdiskGlobal[], int indiceTabla);

int creameCarpeta(MBR mbr, char rutaGlob[], char path[], int indice, int typeRoute, char name[]);

int buscaIndexDisponible(int PTinit, char ruta[]);

void listarDirectorioActual(int PTinit, char ruta[]);

char nombreDir(int PTinit, char ruta[], int indiceBuscado);

void navegar(char pathBuscar[], int indice,List *ambito, MBR mbr, char rutaGlob[]);

void buscaCarpetaParaAmbito(int indice, char rutaGlopb[], char mod[]);//ESTE METODO MODIFICA EL MOD

/*-------------REPORTE DE NOMBRES ----------------------------------------*/
void escribeReporteNobres(int x, FILE *f, MBR mbr, FILE *lee);
/*-------------REPORTE DE NOMBRES ----------------------------------------*/


#endif // OPERACIONES_201503476_H
