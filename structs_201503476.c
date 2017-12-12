#ifndef STRUCTS_201503476_C
#define STRUCTS_201503476_C
#include<structs_201503476.h>

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
        }
    }
}
#endif // STRUCTS_201503476_C
