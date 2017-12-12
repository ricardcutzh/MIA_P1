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
        Disk aux;
        for(x = 0; x<DISK_LIMIT; x++)
        {
            fseek(f,x*sizeof(Disk),SEEK_SET);
            fread(&aux, sizeof(Disk), 1, f);
            if(aux.status == TRUE)
            {
                 printf("|| NOMBRE: %s\n", aux.diskname);
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
#endif // STRUCTS_201503476_C
