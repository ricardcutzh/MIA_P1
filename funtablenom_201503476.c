#ifndef FUNTABLENOM_201503476_C
#define FUNTABLENOM_201503476_C
#include<funtablenom_201503476.h>

//CODIGO
int buscaIndexDisponible(int PTinit, char ruta[])//PINIT ES EL PUNTERO REAL DONDE INICIA LA TABLA
{
    //ABRIMOS EL ARCHIVO
    FILE *f = fopen(ruta, "r");
    if(f!=NULL)
    {
        //POSICIONANDO PUNTERO
        int index = 0;
        int x;
        for(x = 0; x < 10; x++)
        {
            fseek(f, PTinit+(x*sizeof(Data_nombre)), SEEK_SET);
            Data_nombre aux;
            fread(&aux, sizeof(Data_nombre), 1, f);
            if(aux.state==FALSE)
            {
                index = x;
                break;
            }
        }
        //CERRANDO ARCHIVO
        fclose(f);
        //RETORNANDO
        return index;
    }
    else
    {
        return -1;
    }
}

//MARCAR LA CARPETA PRINCIPAL PARA INDICAR QUE LA TABLA ESTA OCPUPADA
void marcaTablaOcupada(int PTinit, char ruta[])
{
    FILE *f = fopen(ruta, "r+");
    if(f!=NULL)
    {
        fseek(f, PTinit, SEEK_SET);
        Data_nombre aux;
        strcpy(aux.name, "NAC");
        aux.type = BANDERA;
        aux.dnode = -1;
        strcpy(aux.date,"NAC");
        aux.init_block = -1;
        aux.padre = -1;
        aux.state = TRUE;
        fwrite(&aux, sizeof(Data_nombre), 1, f);
        fclose(f);
    }
}
//BUSCA CARPETA: ES DECIR QUE BUSCA EL INDICE DE LA TABLA ASOCIADA A LA CARPETA INDICADA
int buscaPunteroDeCarpeta(int PTinit, char ruta[], char nombre[], int puntTabla)
{
    FILE *f = fopen(ruta, "r");
    if(f!=NULL)
    {
        fseek(f, PTinit, puntTabla);
        int ret;
        int x;
        for(x = 0; x < 10; x++)
        {
            Data_nombre aux;
            fread(&aux, sizeof(Data_nombre), 1, f);
            if((strcmp(aux.name, nombre)==0) && (aux.state == TRUE) && (aux.type == CARPETA))
            {
                ret = aux.init_block;
                break;
            }
        }

        fclose(f);
        return ret;
    }
    else
    {
        return -1;
    }
}

//REPORTE DE TABLA
void escribeReporteDeTabla(FILE *f, int PTiniti, FILE *lectura)
{
    int x;
    int d;
    for(x = 0; x< 10; x++)
    {
        d = PTiniti + (x*sizeof(Data_nombre));
        fseek(lectura,d,SEEK_SET);
        Data_nombre aux;
        fread(&aux,sizeof(Data_nombre), 1, lectura);
        if(aux.state == TRUE && aux.type!= BANDERA)
        {
            fprintf(f,"|| %i || NOMBRE: %s || FECHA: %s ",x, aux.name, aux.date);
            if(aux.type == -1)
            {
                fprintf(f,"|| TIPO: CARPETA ");
            }
            else
            {
                fprintf(f,"|| TIPO: ARCHIVO ");
            }
            fprintf(f,"|| BLOQUE INICIAL: %i || NUM_DATANODE: %i || NUM_PADRE: %i || ESTADO: OCUPADO \n", aux.init_block, aux.dnode, aux.padre);
        }
    }
}

#endif // FUNTABLENOM_201503476_C
