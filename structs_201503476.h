#ifndef STRUCTS_201503476_H
#define STRUCTS_201503476_H
#include <cadenas_201503476.h>
#define DISK_LIMIT 10
/* PROPOSITO DE ARCHIVO:
 * DEFINIR STRUCTS
 * DEFINIR OPERACIONES DE LECTURA Y ESCRITURA SOBRE STRUCTS
*/

//STRUCT DEL MBR DE DISCO
typedef struct MBR
{
    int mbr_c_nodes;//CANTIDAD DE DATANODOS
    int mbr_m_numbre;//NUMERO MAGICO
    int mbr_t_nodes;//PUNTERO EN TABLA DE NODOS
    int mbr_t_names;//PUNTERO EN TABLA DE NOMBRES
}MBR;

//STRUCT DE DATANODES
typedef struct datanode
{
    char ruta[PATH_SIZE];//RUTA DEL DATANODE
    int nodo_size_nm;//TAMANIO DEL DATANODE SIN METADATOS
    int nodo_size_ym;//TAMANIO DEL DATANODE CON METADATOS
}datanode;

//STRUCTS DE NOMBRES
typedef struct Data_nombre
{
    char name[LINE_SIZE];//NOMBRE DEL ARCHIVO O CARPETA CREADO
    int type;//TIPO CARPETA O ARCHIVO
    char date[LINE_SIZE];//FECHA DE CREACION
    int init_block;//NUMERO HACIA EL BLOQUE INICIAL DONDE INICIA LA INFO DEL ARCHIVO
    int dnode;//DATANODE QUE ALMACENA EL BLOQUE INICIAL
    int padre;//NUMERO A ESTRUCTURA DEL DIRECTORIO PADRE, ES DECIR LA TABLA DONDE SE ENCUENTRA EL PADRE
    int state;//ESTADO DEL REGISTRO SI ESTA OCUPADO O NO
}Data_nombre;

//STRUCT DE BLOQUE DE DATOS
typedef struct dataBlock
{
    char bd_data[51];//CONTENIDO DE BLOQUE
    int id;//ID DEL BLOQUE
    int next;//ID DEL SIGUIENTE BLOQUE QUE CONTIENE LA INFO
    int NdataNode;//NUMERO DE DATANODE QUE CONTIENE EL SIGUIENTE BLOQUE DEL ARCHIVO
    int state;//ESTADO DEL BLOQUE
}dataBlock;

//STRUCT DE LISTADO DE DISCOS CREADOS (PERSONALIZAD PARA MONTAR Y DESMONTAR)
typedef struct Disk
{
    char diskname[LINE_SIZE];
    char path[PATH_SIZE];
    int space;
    int status;
}Disk;

//PATH GLOBAL
char globalPath[PATH_SIZE];
char globlaDiskPath[PATH_SIZE];
char DiscoActual[LINE_SIZE];

//METODOS DE ESCRITURA Y LECTURA
void escribeListaDisco(int index, char nombre[], char path[], int space, int status);//ESCRIBE UN DISCO EN EL LISTADO DE DISCOS
void imprimirListado();//IMPRIME EL LISTADO DE DISCOS DISPONIBLES
int indexDisponible();//INDEX DISPONIBLE PARA ESCRIBIR UN DISCO MAS EN LISTA
int countDisks();//CONTAR CUANTOS DISCOS SE HAN CREADO Y EXAMINAR SI SE PUEDEN AGREGAR

//MONTAR
void montaDisco(int index);

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

#endif // STRUCTS_201503476_H
