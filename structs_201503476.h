#ifndef STRUCTS_201503476_H
#define STRUCTS_201503476_H
#include <cadenas_201503476.h>
#define DISK_LIMIT 5
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
    string ruta;//RUTA DEL DATANODE
    int nodo_size_nm;//TAMANIO DEL DATANODE SIN METADATOS
    int nodo_size_ym;//TAMANIO DEL DATANODE CON METADATOS
}datanode;

//STRUCTS DE NOMBRES
typedef struct Data_nombre
{
    string name;//NOMBRE DEL ARCHIVO O CARPETA CREADO
    int type;//TIPO CARPETA O ARCHIVO
    string date;//FECHA DE CREACION
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

//METODOS
void escribeListaDisco(int index, char nombre[], char path[], int space, int status);
void imprimirListado();
int indexDisponible();


#endif // STRUCTS_201503476_H
