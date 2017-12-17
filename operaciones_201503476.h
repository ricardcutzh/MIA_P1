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
//ELIMINAR
void eliminar(MBR mbr, char rglob[], char rdiskGlobal[], int indice);
//EDITAR
void editar(MBR mbr, char rglob[], char rdiskGlobal[], int indice);
//COPIAR
void copiar(MBR mbr, char rglob[], char rdiskGlobal[], int indice);
//REPORTE
void generaReporteArchivos(MBR mbr, char rglob[], char rdiskGlobal[], int indice);
//BUSCAR
void buscar(MBR mbr, char rglob[]);
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
int devuelvemeIndiceDeRuta(int indice, char rutaglob[],MBR mbr, int tipoRuta, char rutaCreacion[]);
dataBlock buscameDataBlock(char rutaSinDataNode[], int numBloque, int numNode);
void eliminaDataBlock(char rutaSinDataNode[], int numBloque, int numNode);
void buscaContenidoDeArchivo(int indice, char rutaglob[], MBR mbr, int tipoRuta, char rutaCreacion[], char nombreFile[], char rutaSinDataNode[]);
void eliminaArchivo(int indice, char rutaglob[], MBR mbr, int tipoRuta, char rutaCreacion[], char nombreFile[], char rutaSinDataNode[]);
Data_nombre buscaDataNombre(int PTinit, char nombre[], char rutaglob[]);
void eliminaDataNombre(int PTinit, char nombre[], char rutaglob[]);
//----------------------------------------------------------------//
void eliminaCarpeta(int indice, char rutaglob[], MBR mbr, int tipoRuta, char rutaCreacion[], char nombreFile[], char rutaSinDataNode[]);
void eliminaContenidoCarpeta(int indice , char rutaglob[], MBR mbr, char rutaSinData[]);
/*************************************************************************************/
int editaElArchivo(int indice, char rutaglob[], MBR mbr, char nuevaInfo[], int tipoRuta, char rutaSinDataNode[], char rutaCreacion[], char nombre[], int tipoOperacion);
void traeInfoArchivo(int indice, char rutaglob[], MBR mbr, int tipoRuta, char rutaCreacion[], char nombreFile[], char rutaSinDataNode[], char tempo[]);
int compruebaSiExisteEsteNombreEn(int tipoBuscado, MBR mbr, int indice, char rutaglob[], char nombreBuscado[]);
int compruebaCompletExistenciaDe(int tipoBuscado, MBR mbr, int indice, char rutaglob[], char nombreFile[], int tipoRuta, char rutaCreacion[]);
/*****************************************************************/
int copiaElArchivo(int indice, char rutaglob[], MBR mbr, int tipoRuta, char rutaSinDataNode[], char pathOrigen[], char nombre[], char pathDest[]);
void recorreTabla(int indice, FILE *f, FILE *txt, MBR mbr, char rSinData[], char rutaGlobal[]);
void buscaPadres(int puntero, char rutaGlob[], MBR mbr, char rutaFinal[]);
Data_nombre buscaCarpetaPadre(MBR mbr, char rutaGlob[], int ptr);
void buscarPorNombre(MBR mbr, char rutaGlob[], char nombre[]);
#endif // OPERACIONES_201503476_H
