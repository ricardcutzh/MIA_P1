#ifndef STRUCTS_201503476_C
#define STRUCTS_201503476_C
#include<structs_201503476.h>
//ESCRIBE EL LISTADO DE DISCOS DISPONIBLES
void escribeListaDisco(int index, char nombre[], char path[], int space, int status)
{
    if(index == -1)
    {
        Disk discos[DISK_LIMIT];
        int x;
        for(x = 0; x<DISK_LIMIT; x++)
        {
            Disk aux = {"NAC", "NAC", 0, FALSE};
            discos[x] = aux;
        }
        FILE *f = fopen("DISKS/manage.bin","w");
        fwrite(discos,sizeof(Disk),DISK_LIMIT,f);
        fclose(f);
    }
    else
    {

        Disk aux;
        strcpy(aux.diskname, nombre);
        strcpy(aux.path, path);
        aux.space = space;
        aux.status = status;
        FILE *f = fopen("DISKS/manage.bin","r+");
        fseek(f,index*sizeof(Disk),SEEK_SET);
        fwrite(&aux, sizeof(Disk), 1, f);
        fclose(f);
    }
}
//IMPRIME EL LISTADO DE DISCOS DISPONIBLES PARA LA ELECCION
void imprimirListado()
{
    FILE *f = fopen("DISKS/manage.bin", "r");
    if(f!=NULL)
    {
        int x;
        int index = 1;
        Disk aux;
        for(x = 0; x<DISK_LIMIT; x++)
        {
            fseek(f,x*sizeof(Disk),SEEK_SET);
            fread(&aux, sizeof(Disk), 1, f);
            if(aux.status == TRUE)
            {
                 printf("|| %i) NOMBRE: %s LOCATION: %s\n",index, aux.diskname,aux.path);
                 index++;
            }
        }
        fclose(f);
    }
}
//BUSCA EL INDEX DISPONIBLE PARA MONTAR UN DICO
int indexDisponible()
{
    FILE *f = fopen("DISKS/manage.bin","r");
    if(f!=NULL)
    {
        int x;
        int num = 0;
        Disk aux;
        for(x = 0; x<DISK_LIMIT; x++)
        {
            fseek(f,x*sizeof(Disk),SEEK_SET);
            fread(&aux, sizeof(Disk), 1, f);
            if(aux.status == FALSE)
            {

                break;
            }
            num++;
        }
        fclose(f);
        return num;
    }
    else
    {
        return 0;
    }
}
//CUENTA EL NUMERO DE DISCOS CREADOS
int countDisks()
{
    FILE *f = fopen("DISKS/manage.bin","r");
    if(f!=NULL)
    {
        int x;
        int cont = 0;
        Disk aux;
        for(x = 0 ; x < DISK_LIMIT; x++)
        {
            fseek(f,x*sizeof(Disk),SEEK_SET);
            fread(&aux, sizeof(Disk), 1, f);
            if(aux.status == TRUE)
            {
                cont++;
            }
        }
        return cont;
    }
    else
    {
        return 0;
    }
}
//SE ENCARGA DE CREAR EL NAMENODE DE CADA DISCO
void escribeNameNode(char ruta[], int numNodes)
{
    //CONCATENANDO RUTA
    strcat(ruta, "/NameNode.bin");

    //ABRIENDO ARCHIVO
    FILE *f = fopen(ruta, "w");

    //ESCRIBIENDO EL MBR
    int p_t_nodos = sizeof(MBR);
    int p_t_nombres = sizeof(MBR) + sizeof(datanode)*10;
    MBR mbr = {numNodes, 201503476, p_t_nodos, p_t_nombres};
    fwrite(&mbr, sizeof(MBR), 1, f);

    //ESCRIBIENDO TABLA DE NODOS
    int x;
    fseek(f,p_t_nodos,SEEK_SET);
    for(x = 0; x<10; x++)
    {
        datanode nodo = {"EMPTY",-1,-1};
        fwrite(&nodo, sizeof(datanode),1,f);
    }

    //ESCRIBIENDO TABLA DE NOMBRES
    int y = 0;
    for(y = 0; y < 10000; y++)
    {
        Data_nombre nom = {"NAC",-1,"NAC",-1,-1,-1,-1};
        fwrite(&nom, sizeof(Data_nombre),1,f);
    }

    //CERRAR EL ARCHIVO
    fclose(f);

}
//MONTA LA RUTA DEL DISCO A LEER
void montaDisco(int index)
{
    index = index - 1;
    FILE *f = fopen("DISKS/manage.bin","r");//LEEMOS EL INDICE
    if(f!=NULL)
    {
        Disk aux;
        fseek(f,index*sizeof(Disk),SEEK_SET);
        fread(&aux, sizeof(Disk),1,f);
        printf("=======================================================\n");
        printf("|| MONTANDO DISCO: %s...\n", aux.diskname);
        printf("=======================================================\n");
        strcpy(globalPath, aux.path);
        strcpy(globlaDiskPath, aux.path);
        strcat(globalPath,"/NameNode.bin");
        strcpy(DiscoActual,aux.diskname);
        fclose(f);
        FILE *p = fopen(globalPath,"r");
        if(p!=NULL)
        {
            MBR mbr;
            fseek(p,0,SEEK_SET);
            fread(&mbr,sizeof(MBR),1,p);
            printf("=======================================================\n");
            printf("|| DATOS DEL DISCO:                                  ||\n");
            printf("|| CANTIDAD DE NODOS: %i\n",mbr.mbr_c_nodes);
            printf("|| FIRMA: %i\n",mbr.mbr_m_numbre);
            //IMPRIME LA TABLA DE NODOS DEL DISCO MONTADO
            printNodeTable(mbr.mbr_t_nodes, globalPath);
            //IMPRIME REPORTE DE DATANODES DE DISCO MONTADO
            diskDataNodeReport();
        }
        fclose(p);
    }
}
//ESCRIBE LOS DATANODES QUE TIENE EL DISCO
void escribreDataNodes(char ruta[], int numNodes, int bytes)
{
    //CONCATENANDO LA RUTA
    char tempR[PATH_SIZE] = "TEMP";
    strcpy(tempR, ruta);
    strcat(tempR, "/DataNode");

    //HACIENDO LOOP PARA ESCRIBIR EL ARCHIVO DATANODE
    int x;
    for(x = 1; x <= numNodes; x++ )
    {
        //CONCATENANDO NUMERO DE DATANODE
        char temp[2];
        sprintf(temp, "%d", x);
        strcat(tempR, temp);
        strcat(tempR, ".bin");

        //ABRIENDO DATANODE X
        FILE *f = fopen(tempR, "w");

        //LOOP DE ESCRITURA DE CARACTERES
        fwrite("@",sizeof(char),bytes,f);

        //CERRAR EL ARCHVIO
        fclose(f);
        strcpy(tempR, ruta);
        strcat(tempR, "/DataNode");
    }
}
//----------------------------------------------//
//LEER MBR
MBR leeMBR(char ruta[])
{
    //PREPARANDO RUTA
    char TempR[PATH_SIZE] = "TEMP";
    strcpy(TempR, ruta);

    //ABRIENDO ARCHIVO
    FILE *f = fopen(TempR, "r");
    if(f!=NULL)
    {
        MBR aux;
        fread(&aux,sizeof(MBR),1,f);
        return aux;
    }
}
//TABLA DE NODOS
int nodTBuscaDisponible(int TPinit, char ruta[])
{
    //PREPARANDO LA RUTA
    char tempr[PATH_SIZE] = "TEMP";
    strcpy(tempr, ruta);//NAMENODE

    //ABRIR EL ARCHIVO
    FILE *f = fopen(tempr, "r");
    if(f!=NULL)
    {
        fseek(f,TPinit,SEEK_SET);
        int x;
        int cont;
        for(x = 0; x<10; x++)
        {
            datanode aux;
            fread(&aux, sizeof(datanode), 1, f);
            if(aux.nodo_size_nm==-1)
            {
                return cont;
            }
            //DEVOLVER EL INDEX
            cont++;
        }
    }
    else
    {
        return -1;
    }
}
//ESCRIBIR EL NODO EN TABLA DE NODOS
void nodTWrite(int index, int TPinit, char ruta[], int size)
{
    //PREPARANDO RUTA
    char temp[PATH_SIZE] = "TEMP";
    strcpy(temp, ruta);//NAMENODE

    //ABRIR EL ARCHIVO
    FILE *f = fopen(temp, "r+");
    if(f!=NULL)
    {
        //CONVIERTIENDO A ENTERO EL INDEX
        char s[2];
        int t = index+1;
        sprintf(s,"%d",t);

        //PREPARANDO RUTA DEL DATANODE
        char temp2 [PATH_SIZE] = "DataNode";
        strcat(temp2, s);
        strcat(temp2, ".bin");

        //CALCULADON TAMANIOS
        int Numbloques = floor(size / sizeof(dataBlock));
        int sNM = Numbloques * 51;//TAMANIO SIN METADATA
        int sSM = Numbloques * sizeof(dataBlock);//TAMANIO CON METADATA

        //DECLARANDO EL STRUCT Y ESCRITURA
        datanode aux;
        strcpy(aux.ruta, temp2);
        aux.nodo_size_nm = sNM;
        aux.nodo_size_ym = sSM;
        int pos = TPinit + (index * sizeof(datanode));
        fseek(f,pos, SEEK_SET);
        fwrite(&aux, sizeof(datanode), 1, f);

        //CERRANDO ARCHIVO
        fclose(f);
    }

}
//VER LA TABLA DE NODOS DEL DISCO ACTUAL
void printNodeTable(int TPinit, char ruta[])
{
    //ARCHIVO NAMENODE
    FILE *namenode = fopen(ruta, "r");
    //ARCHIVO TXT
    FILE *txt = fopen("REPORTS/tablaNodos.txt", "w");

    if(namenode!=NULL)
    {

        int i;
        fprintf(txt, "TABLA DE NODOS DE DISCO MONTADO: \n");
        fprintf(txt,"=====================================================================================================================================================\n");
        for(i = 0; i < 10; i++)
        {
            fseek(namenode, TPinit + (i * sizeof(datanode)) , SEEK_SET);
            datanode aux;
            fread(&aux,sizeof(datanode), 1, namenode);
            if(aux.nodo_size_nm!=-1)
            {
                fprintf(txt,"|| No: %i || PATH: %s   || SIZE_NO_META: %i bytes || SIZE_YES_META: %i bytes \n",i,aux.ruta, aux.nodo_size_nm, aux.nodo_size_ym);
            }
        }
        fprintf(txt,"=====================================================================================================================================================\n");
    }

    //CERRAR
    fclose(namenode);
    fclose(txt);
}
//DA FORMATO A LOS DATANODES PARA ALISTARLOS PARA GUARDAR INFORMACION
void formatDataNode(char ruta[], int espacio, int numDataNode)
{
    //AJUSTANDO RUTA DEL DATANODE
    char tempr[PATH_SIZE] = "TEMP";
    strcpy(tempr, ruta);
    strcat(tempr, "/DataNode");
    char s[2];
    int t = numDataNode+1;
    sprintf(s,"%d",t);
    strcat(tempr, s);
    strcat(tempr, ".bin");

    //CALCULANDO EL NUMERO DE BLOQUES EL ESPACIO YA BIENE EN BYTES
    int numBloques = floor(espacio/sizeof(dataBlock));

    //ESCRIBIENDO EN EL ARCHIVO DATANODE PARA DARLE FORMATO
    FILE *f = fopen(tempr, "r+");
    if(f!=NULL)
    {
        int x;
        for(x = 0; x<numBloques; x++)
        {
            dataBlock aux;
            strcpy(aux.bd_data, "EMPTY");
            aux.id = x + 1;
            aux.NdataNode = -1;
            aux.next = -1;
            aux.state = FALSE;
            fseek(f, x*sizeof(dataBlock), SEEK_SET);
            fwrite(&aux, sizeof(dataBlock),1,f);
        }
        fclose(f);
    }

}
//FUNCIONES QUE ESCRIBEN EL REPORTE DE DATANODES
void diskDataNodeReport()
{
    FILE *f = fopen(globalPath, "r");
    FILE *txt = fopen("REPORTS/reporteDataNodes.txt", "w");
    fprintf(txt, "===================================================================================================================\n");
    fprintf(txt,"||  REPORTE DATANODES DE DISCO: %s\n", globlaDiskPath);
    fprintf(txt, "===================================================================================================================\n");
    MBR mbr;
    fread(&mbr, sizeof(MBR), 1, f);
    int x;
    for(x = 0; x < 10; x++)
    {
        fseek(f, mbr.mbr_t_nodes+(x*sizeof(datanode)),SEEK_SET);
        datanode aux;
        fread(&aux,sizeof(datanode), 1, f);
        //LLAMADA A LA ESCRITURA INDIVIDUAL
        if(aux.nodo_size_ym!=-1)
        {
            writeNodeReport(txt, aux.nodo_size_ym, aux.ruta);
        }
    }
    fprintf(txt, "===================================================================================================================\n");
    fclose(f);
    fclose(txt);
}
void writeNodeReport(FILE *p, int bytestotales, char na[])
{
    fprintf(p, "*********************************************************************************************************************\n");
    fprintf(p, "DATANODE: %s\n", na);
    fprintf(p, "*********************************************************************************************************************\n");
    //AJUSTANDO RUTA
    char rt[PATH_SIZE] = "temp";
    strcpy(rt, globlaDiskPath);
    strcat(rt, "/");
    strcat(rt, na);
    //ABRIENDO...
    FILE *f = fopen(rt, "r");
    //NUMBLOQUES
    int numb = bytestotales/sizeof(dataBlock);
    int x;
    for(x = 0; x<numb; x++)
    {
        fseek(f, x*sizeof(dataBlock), SEEK_SET);
        dataBlock aux;
        fread(&aux, sizeof(dataBlock), 1, f);
        fprintf(p,"|| IDBLOCK: %i || NEXT_INFO_BLOCK: %i || NUM_DATANODE: %i || STATE: %i || INFO: %s \n", aux.id, aux.next, aux.NdataNode, aux.state, aux.bd_data);
    }
    //CERRANDO
    fprintf(p, "*********************************************************************************************************************\n");
    fclose(f);
}
#endif // STRUCTS_201503476_C
