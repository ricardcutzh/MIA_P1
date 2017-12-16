#ifndef OPERACIONES_201503476_C
#define OPERACIONES_201503476_C
#include<operaciones_201503476.h>
#include<time.h>

void crear(MBR mbr, char rglob[], char rdiskGlobal[], int indiceTabla)
{
    //EL INDICE TABLA ES EL INDICE 1,2,3 DE LA TABLA DONDE ESTOY
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
    char name[LINE_SIZE];
    gets(name);
    printf("|| RUTA: >> ");
    char p[PATH_SIZE];
    gets(p);
    int type = 1;
    if(strcmp(tipoR, "A")==0)//TIPO DE RUTA
    {
        type = 2;//SI LA RUTA ES ABSOLUTLA
    }
    if(strcmp(tipo, "A")==0)//TIPO DE FILE
    {
        //ARCHIVO
        rdiskGlobal = "joads";
    }
    else if(strcmp(tipo, "D")==0)
    {
        //CARPETA
        int res = creameCarpeta(mbr,rglob, p, indiceTabla, type, name);
        if(res == TRUE)
        {
            printf("|| CARPETA CREADA CON EXITO!\n");
            getchar();
        }
        else
        {
            printf("|| OCURRIO UN ERROR PORFAVOR COMPRUEBE EL PATH QUE INDICO\n");
            getchar();
        }

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
            //VAMOS A BUSCAR LA CARPETA INDICADA
            char cadenaaux[PATH_SIZE] = "";
            int lenght = strlen(path);
            int x;
            int ban = 0;
            for(x = 0; x< lenght; x++)
            {
                if(path[x]=='/' || path[x]=='\0')//SI EL CARACTER NO ES SLASH O FINALIZACION
                {
                    //BUSCAR Y LIMPIAR
                    int p = mbr.mbr_t_names + (indice * sizeof(Data_nombre)*10);//CALCULO EL PUNTERO
                    int puntero = buscaPunteroDeCarpeta(p,rutaGlob, cadenaaux, SEEK_SET);
                    if(puntero!= -1)
                    {
                        indice = (puntero - mbr.mbr_t_names)/(sizeof(Data_nombre)*10);
                    }
                    else
                    {
                        //SI NO ENCUENTRO ENTONCES ROMPO EL CICLO Y LO IGUALO A MENOS 1 PARA INDICAR EL ERROR
                        indice = -1;
                        break;
                    }
                    int cx;
                    for(cx = 0; cx<PATH_SIZE; cx++)
                    {
                        cadenaaux[cx] = '\0';
                    }
                    ban = 0;
                }
                else
                {
                    cadenaaux[ban] = path[x]; //HAS LA NUEVA CADENA
                    ban++;

                }
            }

            //DECIDO QUE HACER
            if(indice != -1)
            {
                int pt = mbr.mbr_t_names + (indice * sizeof(Data_nombre)*10);
                FILE *f = fopen(rutaGlob, "r+");
                int posicionReg = buscaIndexDisponible(pt, rutaGlob);//fun
                fseek(f, pt + (posicionReg * sizeof(Data_nombre)),SEEK_SET);
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
                aux.padre = pt;
                fwrite(&aux, sizeof(Data_nombre), 1, f);
                fclose(f);
                return TRUE;
            }
            else
            {
                return FALSE;
            }

        }
    }
    else
    {
        int index = 0;
        char cadenaaux[PATH_SIZE] = "";
        int lenght = strlen(path);
        int x;
        int ban = 0;
        for(x = 0; x< lenght; x++)
        {
            if(path[x]=='/' || path[x]=='\0')//SI EL CARACTER NO ES SLASH O FINALIZACION
            {
                //BUSCAR Y LIMPIAR
                int p = mbr.mbr_t_names + (index * sizeof(Data_nombre)*10);//CALCULO EL PUNTERO
                int puntero = buscaPunteroDeCarpeta(p,rutaGlob, cadenaaux, SEEK_SET);
                if(puntero!= -1)
                {
                    index = (puntero - mbr.mbr_t_names)/(sizeof(Data_nombre)*10);
                }
                else
                {
                    //SI NO ENCUENTRO ENTONCES ROMPO EL CICLO Y LO IGUALO A MENOS 1 PARA INDICAR EL ERROR
                    index = -1;
                    break;
                }
                int cx;
                for(cx = 0; cx<PATH_SIZE; cx++)
                {
                    cadenaaux[cx] = '\0';
                }
                ban = 0;
            }
            else
            {
                cadenaaux[ban] = path[x]; //HAS LA NUEVA CADENA
                ban++;

            }
        }
        if(index != -1)
        {
            int pt = mbr.mbr_t_names + (index * sizeof(Data_nombre)*10);
            FILE *f = fopen(rutaGlob, "r+");
            int posicionReg = buscaIndexDisponible(pt, rutaGlob);//fun
            fseek(f, pt + (posicionReg * sizeof(Data_nombre)),SEEK_SET);
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
            aux.padre = pt;
            fwrite(&aux, sizeof(Data_nombre), 1, f);
            fclose(f);
            return TRUE;
        }
        else
        {
            return FALSE;
        }

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

void listarDirectorioActual(int PTinit, char ruta[])
{
    FILE *f = fopen(ruta, "r");
    if(f!=NULL)
    {
        printf("==========================================================================\n");
        printf("||                        DIRECTORIO ACTUAL:                            ||\n");
        printf("==========================================================================\n");
        fseek(f,PTinit, SEEK_SET);
        int x;
        for(x = 0; x < 10; x++)
        {
            Data_nombre aux;
            fread(&aux, sizeof(Data_nombre), 1, f);
            if(aux.state == TRUE && aux.type!= BANDERA)
            {
                printf("|| * %s ",aux.name);
                if(aux.type == CARPETA)
                {
                    printf("|| TIPO: CARPETA\n");
                }
                else
                {
                    printf("|| TIPO: ARCHIVO\n");
                }
            }
        }
        printf("==========================================================================\n");
    }
}

char nombreDir(int PTinit, char ruta[], int indiceBuscado)
{
    FILE *f = fopen(ruta, "r");
    if(f!=NULL)
    {
        fseek(f, PTinit, SEEK_SET);
        char ret[LINE_SIZE] = "NAC";
        int x;
        for(x = 0; x < 10000; x++)
        {
            Data_nombre aux;
            fread(&aux, sizeof(Data_nombre), 1, f);
            if(aux.type == CARPETA)
            {
                if(aux.init_block == indiceBuscado)
                {
                    strcpy(ret, aux.name);
                    break;
                }
            }
        }
        fclose(f);
        return ret;
    }
    else
    {
        return "NAC";
    }
}

//NAVEEGAR
void navegar(char pathBuscar[], int indice, List *ambito, MBR mbr, char rutaGlob[])
{
    char cadenaaux[PATH_SIZE]="";
    int length = strlen(pathBuscar);
    int x;
    int ban = 0;
    for(x = 0; x < length; x++)
    {
        if(pathBuscar[x]=='/' || pathBuscar[x]=='\0')
        {
            int p = mbr.mbr_t_names + (indice * sizeof(Data_nombre)*10);//CALCULO EL PUNTERO
            int puntero = buscaPunteroDeCarpeta(p,rutaGlob, cadenaaux, SEEK_SET);
            if(puntero!= -1 && puntero>mbr.mbr_t_names)
            {
                indice = (puntero - mbr.mbr_t_names)/(sizeof(Data_nombre)*10);
                nodo *n = newNodo();
                n->valor = indice;
                push(ambito,n);
            }
            else
            {
                //SI NO ENCUENTRO ENTONCES ROMPO EL CICLO Y LO IGUALO A MENOS 1 PARA INDICAR EL ERROR

                indice = -1;
                nodo *n = newNodo();
                n->valor = indice;
                push(ambito,n);
                break;
            }
            int cx;
            for(cx = 0; cx<PATH_SIZE; cx++)
            {
                cadenaaux[cx] = '\0';
            }
            ban = 0;
        }
        else
        {
            cadenaaux[ban] = pathBuscar[x]; //HAS LA NUEVA CADENA
            ban++;
        }
    }
    printList(ambito);
}

void buscaCarpetaParaAmbito(int indice, char rutaGlopb[], char mod[])
{
    FILE *f = fopen(rutaGlopb, "r");
    int inicio = (sizeof(MBR))+(sizeof(datanode)*10);
    int punt = inicio + (indice * sizeof(Data_nombre)*10);
    if(f!=NULL)
    {
        fseek(f, inicio, SEEK_SET);
        int x;
        for(x = 0; x<10000; x++)
        {
            Data_nombre aux;
            fread(&aux,sizeof(Data_nombre), 1, f);
            if(aux.state == TRUE && aux.type == CARPETA && aux.init_block == punt)
            {
                strcpy(mod, aux.name);
                break;
            }
        }
        fclose(f);
    }
}
#endif // OPERACIONES_201503476_C
