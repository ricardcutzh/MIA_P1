#ifndef STRUCTS_201503476_H
#define STRUCTS_201503476_H
#include <cadenas_201503476.h>
#include<operaciones_201503476.h>
#include<componentes_201503476.h>
#include<datastructure_201503476.h>
#define DISK_LIMIT 10
/* PROPOSITO DE ARCHIVO:
 * DEFINIR STRUCTS
 * DEFINIR OPERACIONES DE LECTURA Y ESCRITURA SOBRE STRUCTS
*/





//METODOS DE ESCRITURA Y LECTURA
void escribeListaDisco(int index, char nombre[], char path[], int space, int status);//ESCRIBE UN DISCO EN EL LISTADO DE DISCOS
void imprimirListado();//IMPRIME EL LISTADO DE DISCOS DISPONIBLES
int indexDisponible();//INDEX DISPONIBLE PARA ESCRIBIR UN DISCO MAS EN LISTA
int countDisks();//CONTAR CUANTOS DISCOS SE HAN CREADO Y EXAMINAR SI SE PUEDEN AGREGAR

//MONTAR
void montaDisco(int index);
void menuMontado(MBR mbr);

//METODOS DE ESCRIBIR ARCHIVOS DE DISCO ESPECIFICAMENTE
//NAMENODO
void escribeNameNode(char ruta[], int numNodes);
void escribreDataNodes(char ruta[], int numNodes, int bytes);

/*-------------METODOS DE NAMENODE----------------------------------------*/
//METODOS DE MBR
MBR leeMBR(char ruta[]);//RECIBE LA RUTA COMPLETA DEL NAMENODE A LEER EL MBR

//METODOS DE TABLA DE NODOS
int nodTBuscaDisponible(int TPinit, char ruta[]);
void nodTWrite(int index, int TPinit, char ruta [], int size);
void printNodeTable(int TPinit, char ruta[]);

//METODOS DE TABLA DE NOMBRES
int nameTBuscaDisponible(int TPinit);
void nameTWrite(int index, int TPinit, char name[], int type, char date [], int idBlock, int Padre, int estado);

/*-------------METODOS DE NAMENODE----------------------------------------*/

/*-------------METODOS DE DATANODE----------------------------------------*/
void formatDataNode(char ruta [], int espacio, int numDataNode);
void diskDataNodeReport();
void writeNodeReport(FILE *p, int bytestotales, char na[]);
/*-------------METODOS DE DATANODE----------------------------------------*/

/*-------------REPORTE DE NOMBRES ----------------------------------------*/
void nameTablesReport();
/*-------------REPORTE DE NOMBRES ----------------------------------------*/



#endif // STRUCTS_201503476_H
