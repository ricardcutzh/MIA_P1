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

/*****************************************************************/
int countDiskDataNodes(MBR mbr, char ruta[]);
int escribeArchivo(int indice, char rutaglob[], MBR mbr, char contenido[], int tipoRuta, char rutaSinDataNode[], char rutaCreacion[], char nombre[]);
int buscaIDBloque(char rutaSinData[], int numeroDataNode);
void escribeDatablock(char rutaSinData[], int numerDatanode, dataBlock bloque);
void escribeDatanombre(char rutaglob[], int indice, Data_nombre nom, MBR mbr);
void separandoContenido(char contenido[], char tempora[], int inicio, int final);
void emptyArray(char cadena[]);
/*****************************************************************/
#endif // OPERACIONES_201503476_H
