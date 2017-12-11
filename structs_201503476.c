#ifndef STRUCTS_201503476_C
#define STRUCTS_201503476_C
#include<structs_201503476.h>

void escribirDiscos(int index, string name, string path, int space, int status)
{
    if(index == -1)
    {
        FILE *f = fopen("DISKS/manage.bin","w");
        int x;
        for(x = 0; x<DISK_LIMIT; x++)
        {
            fseek(f,x*sizeof(Disk),SEEK_SET);
            Disk *aux = (Disk*)malloc(sizeof(Disk));
            aux->diskName = "SIN NOMBRE";
            aux->pathInit = "SIN PATH";
            aux->space = 0;
            aux->status = FALSE;
            fwrite(aux,sizeof(Disk),1,f);
        }
        fclose(f);
    }
    else
    {
        FILE *f = fopen("DISKS/manage.bin","r+");//USE RB PARA PODER ACTUALIZAR EL ARCHIVO
        fseek(f,index*sizeof(Disk),SEEK_SET);
        Disk *aux = (Disk*)malloc(sizeof(Disk));
        aux->diskName = nuevaCadena();
        aux->pathInit = nuevaCadena();
        strcpy(aux->diskName, name);
        strcpy(aux->pathInit, path);
        aux->space = space;
        aux->status = status;
        fwrite(aux, sizeof(Disk),1,f);
        fclose(f);
    }
}

int leeDisponible()
{
    FILE *f = fopen("DISKS/manage.bin","r");
    if(f!=NULL)
    {
        int num = 0;
        int x = 0;
        for(x=0; x<DISK_LIMIT;x++)
        {
            fseek(f,x*sizeof(Disk),SEEK_SET);
            Disk *aux = (Disk*)malloc(sizeof(Disk));
            fread(aux,sizeof(Disk),1,f);
            if(aux->status == FALSE)
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

imprimeListado()
{
    FILE *f = fopen("DISKS/manage.bin","r+");
    if(f!=NULL)
    {

        int x = 0;
        for(x=0; x<DISK_LIMIT;x++)
        {
            fseek(f,x*sizeof(Disk),SEEK_SET);
            Disk *aux = (Disk*)malloc(sizeof(Disk));
            fread(aux,sizeof(Disk),1,f);
            if(aux->status == TRUE)
            {
                printf("|| Nombre: %s\n",aux->diskName);
            }
            free(aux);
            aux = NULL;
        }
        fclose(f);
    }
    else
    {
        fclose(f);
    }
}
#endif // STRUCTS_201503476_C
