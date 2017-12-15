#ifndef OPERACIONES_201503476_C
#define OPERACIONES_201503476_C
#include<operaciones_201503476.h>
#include<time.h>

void crear(MBR mbr, char rglob[], char rdiskGlobal[], int indiceTabla)
{

    printf("===============================================================\n");
    printf("||                      CREAR                                ||\n");
    printf("===============================================================\n");
    printf("|| TIPO DIRECTORIO(D) O ARCHIVO: (A): >> ");
    char tipo[2];
    gets(tipo);
    printf("|| TIPO DE RUTA RELATIVA(R) O ABSOLUTA(A): >> ");
    char tipoR[2];
    gets(tipoR);
    printf("|| NOMBRE: >> ");
    char name[2];
    gets(name);
    printf("|| RUTA: >> ");
    char p[PATH_SIZE];
    gets(p);
    int type = 1;
    if(strcmp(tipoR, "A")==0)//TIPO DE RUTA
    {
        type = 2;
    }
    if(strcmp(tipo, "A")==0)//TIPO DE FILE
    {
        //ARCHIVO
        rdiskGlobal = "joads";
    }
    else if(strcmp(tipo, "D")==0)
    {
        //CARPETA
        creameCarpeta(mbr,rglob, p, indiceTabla, type, name);

    }
    printf("===============================================================\n");
}

int creameCarpeta(MBR mbr, char rutaGlob[], char path[], int indice, int typeRoute, char name[])//ESTE RECIBE INDICE DE TABLA COMO UN ARREGLO (0,1,2...)
{
    if(typeRoute == 1)//RUTA RELATIVA ES DECIR EN EL DIRECTORIO DOND ESTOY (INDICE)
    {
        if(strcmp(path, "NAC")==0)
        {
            FILE *f = fopen(rutaGlob, "r+");
            //ME POSICIONO DE FORMA QUE ESTE EN EL INICIO DE LA TABLA CORRESPONDIENTE
            int punteroReal = mbr.mbr_t_names+(indice * sizeof(Data_nombre)*10);
            int posicionReg = buscaIndexDisponible(punteroReal, rutaGlob);//fun
            fseek(f, punteroReal + (posicionReg * sizeof(Data_nombre)),SEEK_SET);
            Data_nombre aux;
            time_t t;
            time(&t);
            strcpy(aux.date, ctime(&t));
            aux.dnode = -1;
            int c;
            int hijo;
            for(c = 1; c<1001; c++)
            {
                int d = estaDisponibleTabla(mbr.mbr_t_names + (c*(sizeof(Data_nombre)*10)), rutaGlob);
                if(d == TRUE)
                {
                    hijo = mbr.mbr_t_names + (c *(sizeof(Data_nombre)*10));
                    marcaTablaOcupada(hijo, rutaGlob);
                    break;
                }
            }
            aux.init_block = hijo;//TABLA VACIA
            strcpy(aux.name,name);
            aux.state = TRUE;
            aux.type = CARPETA;
            aux.padre = punteroReal;
            fwrite(&aux, sizeof(Data_nombre), 1, f);
            fclose(f);
            return TRUE;
        }
        else
        {
            //NAVEGAR PARA ENCONTRAR EL DIRECTORIO QUE BUSCO
        }
    }
    else
    {

    }
    return FALSE;

}

// BUSCA SI LA ABLA ESTA DISPONIBLE ES DECIR SI NO ESTA OCUPADA
int estaDisponibleTabla(int PTinit, char ruta[])
{
    //ABRIMOS EL ARCHIVO
    FILE *f = fopen(ruta, "r");
    if(f!= NULL)
    {
        //POSICIONANDO
        fseek(f, PTinit, SEEK_SET);
        int estaDisponible = TRUE;
        int x;
        for(x = 0; x < 10 ; x++)
        {
            Data_nombre aux;
            fread(&aux, sizeof(Data_nombre), 1, f);
            if(aux.state == TRUE)
            {
                //ENTONCES ESTA OCUPADA
                estaDisponible = FALSE;
                break;
            }
        }
        //CERRANDO
        fclose(f);
        return estaDisponible;
    }
    else
    {
        return FALSE;
    }
}

void escribeReporteNobres(int x, FILE *f, MBR mbr, FILE *lee)
{
    escribeReporteDeTabla(f,mbr.mbr_t_names+(x*sizeof(Data_nombre)*10),lee);//FUNTABLANOMB
}
#endif // OPERACIONES_201503476_C
