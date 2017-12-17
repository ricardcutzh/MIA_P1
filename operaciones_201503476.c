#ifndef OPERACIONES_201503476_C
#define OPERACIONES_201503476_C
#include<operaciones_201503476.h>
#include<math.h>
#include<time.h>
char rutaAuxiliar[PATH_SIZE];


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
        if(compruebaCompletExistenciaDe(ARCHIVO,mbr, indiceTabla, rglob, name, type, p)==FALSE)
        {
            printf("|| CONTENIDO DEL ARCHIVO: >> ");
            char con[500];//cantidad de caracteres del mensaje
            gets(con);
            int res = escribeArchivo(indiceTabla, rglob, mbr, con, type, rdiskGlobal, p,name);
            if(res == TRUE)
            {
                printf("|| ARCHIVO CREADO CON EXITO!\n");
                getchar();
            }
            else
            {
                printf("|| OCURRIO UN ERROR PORFAVOR COMPRUEBE EL PATH QUE INDICO\n");
                getchar();
            }
        }
        else
        {
            printf("|| OCURRIO UN ERROR , AL PARECER DESEA CREAR UN ARCHIVO QUE YA EXISTE EN EL PATH INDICADO\n");
            getchar();
        }

    }
    else if(strcmp(tipo, "D")==0)
    {
        //CARPETA
        if(compruebaCompletExistenciaDe(CARPETA,mbr, indiceTabla, rglob, name, type, p)==FALSE)
        {
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
        else
        {
            printf("|| ESTA CARPETA YA EXISTE EN EL DIRECTORIO INDICADO...\n");
            getchar();
        }
    }
    printf("===============================================================\n");
}
//ELIMINAR
void eliminar(MBR mbr, char rglob[], char rdiskGlobal[], int indice)
{
    printf("===============================================================\n");
    printf("||                      ELIMINAR                             ||\n");
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
        //buscaContenidoDeArchivo(indice, rglob, mbr, type, p, name, rdiskGlobal);
        eliminaArchivo(indice, rglob, mbr, type, p,name,rdiskGlobal);
    }
    else if(strcmp(tipo, "D")==0)
    {
        //DIRECTORIO
        eliminaCarpeta(indice, rglob, mbr, type, p, name, rdiskGlobal);
    }

}
//EDITAR
void editar(MBR mbr, char rglob[], char rdiskGlobal[], int indice)
{
    printf("===============================================================\n");
    printf("||                     EDITAR ARCHIVOS                       ||\n");
    printf("===============================================================\n");
    printf("|| AGREGAR (M) O SOBREESCRIBIR (S): >> ");
    char ope[2];
    gets(ope);
    printf("|| TIPO DE RUTA RELATIVA(R) O ABSOLUTA(A): >> ");
    char tipoR[2];
    gets(tipoR);
    printf("|| NOMBRE: >> ");
    char name[LINE_SIZE];
    gets(name);
    printf("|| RUTA: >> ");
    char p[PATH_SIZE];
    gets(p);
    int type = 1;//RELATIVA
    if(strcmp(tipoR, "A")==0)//TIPO DE RUTA
    {
        type = 2;//SI LA RUTA ES ABSOLUTLA
    }
    int opera = 2;//OVERWRITE
    if(strcmp(ope, "M")==0)
    {
        opera = 1;
        if(compruebaCompletExistenciaDe(ARCHIVO,mbr, indice, rglob, name, type, p)==TRUE)
        {
            printf("=====================================================================================================\n");
            buscaContenidoDeArchivo(indice, rglob, mbr, type, p, name, rdiskGlobal);
            printf("=====================================================================================================\n");
            printf("|| NUEVO CONTENIDO >> ");
            char nuevainfo[PATH_SIZE]="";
            gets(nuevainfo);
            int res = editaElArchivo(indice, rglob, mbr, nuevainfo, type, rdiskGlobal, p, name, opera);
            if(res == TRUE)
            {
                printf("|| ARCHIVO EDITADO CORRECTAMENTE! \n");
            }
            else {
                printf("|| ERROR EN PATH \n");
            }
            getchar();
        }
        else
        {
            printf("|| ERROR EN PATH \n");
            getchar();
        }
    }
    else if(opera == 2)
    {

        if(compruebaCompletExistenciaDe(ARCHIVO, mbr, indice, rglob, name, type, p)==TRUE)
        {
            printf("|| NUEVO CONTENIDO QUE REEMPLAZA AL VIEJO >> ");
            char nuevainfo[PATH_SIZE]="";
            gets(nuevainfo);
            int res = editaElArchivo(indice, rglob, mbr, nuevainfo, type, rdiskGlobal, p, name, opera);
            if(res == TRUE)
            {
                printf("|| ARCHIVO SOBREESCRITO CORRECTAMENTE! \n");
            }
            else {
                printf("|| ERROR EN PATH \n");
            }
            getchar();
        }
        else
        {
            printf("|| ERROR EN PATH \n");
            getchar();
        }
    }

}
//COPIAR
void copiar(MBR mbr, char rglob[], char rdiskGlobal[], int indice)
{
    int type = ARCHIVO;
    printf("===============================================================\n");
    printf("||                    COPIAR                                 ||\n");
    printf("===============================================================\n");
    printf("|| COPIAR DIRECTORIO (D) O ARCHIVO (A): >> ");
    char tipo[2];
    gets(tipo);
    if(strcmp(tipo, "D")==0)
    {
        type = CARPETA;
    }
    printf("|| PATH ORIGEN: >> ");
    char pathOrigin[PATH_SIZE];
    gets(pathOrigin);
    printf("|| NOMBRE: >> ");
    char name[LINE_SIZE];
    gets(name);
    printf("|| PATH DESTINO: >> ");
    char pathDest[PATH_SIZE];
    gets(pathDest);
    int comp1 = compruebaCompletExistenciaDe(type, mbr, indice, rglob, name, 2, pathOrigin);
    int comp2 = devuelvemeIndiceDeRuta(indice, rglob, mbr, 2, pathDest);
    if(comp1 == TRUE && comp2!=-1)//ES PORQUE SI EXISTE
    {
        if(type == ARCHIVO)
        {
            if(copiaElArchivo(indice, rglob, mbr, 2, rdiskGlobal, pathOrigin, name, pathDest)==TRUE)
            {
                printf("|| ARCHIVO COPIADO CON EXITO...\n");
            }
        }
        else
        {
            //QUE SAD NO TENGO EL COPIAR DIRECTORIO :(
        }
    }
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
    //printList(ambito);
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

void generaReporteArchivos(MBR mbr, char rglob[], char rdiskGlobal[], int indice)
{
     int x;
     FILE *f = fopen(rglob, "r");
     FILE *txt = fopen("REPORTS/ArchivosReporte.txt", "w");
     fprintf(txt, "=================================================================================================================================================================\n");
     fprintf(txt,"||  REPORTE TABLA DE ARCHIVOS DE DISCO: %s\n", rdiskGlobal);
     fprintf(txt, "=================================================================================================================================================================\n");
     //fprintf(txt, "                                                                                                                                                             \n");
     //fprintf(txt,"******************************************************************************************************************************************************************\n");
     for(x = 0; x< 1000; x++)
     {
         int dispo = estaDisponibleTabla(mbr.mbr_t_names + (x*sizeof(Data_nombre)*10),rglob);
         if(dispo == FALSE)
         {
             int pt = mbr.mbr_t_names + (x * sizeof(Data_nombre)*10);

             //fprintf(txt,"||                                       TABLA NO: %i || PUNTERO EN ARCHIVO: %i\n", x, pt);
             //fprintf(txt,"******************************************************************************************************************************************************************\n");
             //AQUI IMPRIMO INFORMACION POR TABLA
             recorreTabla(x, f, txt, mbr,rdiskGlobal,rglob);
             //fprintf(txt, "                                                                                                                                                             \n");
             //fprintf(txt, "*****************************************************************************************************************************************************************\n");

         }
     }
     fprintf(txt, "=================================================================================================================================================================\n");
     fclose(f);
     fclose(txt);
}

void buscar(MBR mbr, char rglob[])
{
    printf("|| BUSCAR: >> ");
    char nombreBuscar[LINE_SIZE];
    emptyArray(nombreBuscar);
    gets(nombreBuscar);
    printf("------------------------------------------------------------------------------------------------------\n");
    buscarPorNombre(mbr, rglob, nombreBuscar);
    printf("------------------------------------------------------------------------------------------------------\n");
    getchar();
}
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*/
//ARCHIVOS MENEJO
int countDiskDataNodes(MBR mbr, char ruta[])//RETORNA EL NUMERO DE DATANODES
{
    FILE *f = fopen(ruta,"r");
    if(f!=NULL)
    {
        fseek(f, mbr.mbr_t_nodes, SEEK_SET);
        int count  = 0;
        int x;
        for(x = 0; x<10;x++)
        {
            datanode aux;
            fread(&aux, sizeof(datanode), 1, f);
            if(aux.nodo_size_nm!=-1)
            {
                count++;
            }
        }
        fclose(f);
        return count;
    }
    return 0;
}
int escribeArchivo(int indice, char rutaglob[], MBR mbr, char contenido[], int tipoRuta, char rutaSinDataNode[], char rutaCreacion[], char nombre[])
{
    if(strcmp(rutaCreacion,"NAC")!=0)//SI LA RUTA NO ES NAC
    {
        if(tipoRuta !=1)
        {
            indice = 0;
        }
        char cadenaaux[PATH_SIZE] = "";
        int lenght = strlen(rutaCreacion);
        int x;
        int ban = 0;
        for(x = 0; x< lenght; x++)
        {
            if(rutaCreacion[x]=='/' || rutaCreacion[x]=='\0')//SI EL CARACTER NO ES SLASH O FINALIZACION
            {
                //BUSCAR Y LIMPIAR
                int p = mbr.mbr_t_names + (indice * sizeof(Data_nombre)*10);//CALCULO EL PUNTERO
                int puntero = buscaPunteroDeCarpeta(p,rutaglob, cadenaaux, SEEK_SET);
                if(puntero!= -1)
                {
                    indice = (puntero - mbr.mbr_t_names)/(sizeof(Data_nombre)*10);
                }
                else
                {
                    //SI NO ENCUENTRO ENTONCES ROMPO EL CICLO Y LO IGUALO A MENOS 1 PARA INDICAR EL ERROR
                    indice = -1;

                    return FALSE;
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
                cadenaaux[ban] = rutaCreacion[x]; //HAS LA NUEVA CADENA
                ban++;

            }
        }
        //EN ESTE PUNTO YA TENGO EL INDICE
        int qdatanodes = mbr.mbr_c_nodes;
        int qblocks = floor(strlen(contenido)/50)+1;
        dataBlock bloques[qblocks];
        int numDataNode[qblocks];
        int xc;
        for(xc = 0; xc< qblocks;xc++)
        {
            numDataNode[xc] = randomGen(1,qdatanodes);
            dataBlock aux;
            char temp[50] = "";
            emptyArray(temp);
            separandoContenido(contenido, temp, 50*xc, 50+(xc*50));
            strcpy(aux.bd_data, temp);//AUN TENGO QUE DIVIDIR EL CONTENIDO
            aux.id = 1 + buscaIDBloque(rutaSinDataNode, numDataNode[xc]);
            aux.NdataNode = numDataNode[xc];
            aux.state = TRUE;
            bloques[xc] = aux;
            emptyArray(temp);
            //ESTE ES PARA MARCAR EL ESPACIO PARA RESERVARLOS
            dataBlock temp1;
            strcpy(temp1.bd_data, "MARCADO");
            temp1.id = aux.id;
            temp1.NdataNode = numDataNode[xc];
            temp1.next = -1;
            temp1.state = TRUE;
            escribeDatablock(rutaSinDataNode, numDataNode[xc],temp1);
        }
        //CREO EL REGISTRO DE NOMBRE PARA TABLA
        Data_nombre nuevo;
        time_t t;
        time(&t);
        strcpy(nuevo.date, ctime(&t));
        nuevo.dnode = numDataNode[0];
        nuevo.init_block = bloques[0].id;//RECUERDA QUE ES ID - 1
        strcpy(nuevo.name, nombre);
        nuevo.padre = mbr.mbr_t_names + (indice*sizeof(Data_nombre)*10);
        nuevo.state = TRUE;
        nuevo.type = ARCHIVO;
        int v;
        for(v = 0; v< qblocks; v++)
        {
            if(v!= (qblocks-1))
            {
                bloques[v].next = bloques[v+1].id;
                bloques[v].NdataNode = bloques[v+1].NdataNode;
            }
            else
            {
                bloques[v].next = -1;
                bloques[v].NdataNode = -1;
            }
            escribeDatablock(rutaSinDataNode, numDataNode[v], bloques[v]);
        }
        escribeDatanombre(rutaglob, indice, nuevo, mbr);
        return TRUE;
    }
    else
    {
        //EN ESTE PUNTO YA TENGO EL INDICE
        int qdatanodes = mbr.mbr_c_nodes;
        int qblocks = floor(strlen(contenido)/50)+1;
        dataBlock bloques[qblocks];
        int numDataNode[qblocks];
        int xc;
        for(xc = 0; xc< qblocks;xc++)
        {
            numDataNode[xc] = randomGen(1,qdatanodes);
            dataBlock aux;
            char temp[50] = "";
            emptyArray(temp);
            separandoContenido(contenido, temp, 50*xc, 50+(xc*50));
            strcpy(aux.bd_data, temp);//AUN TENGO QUE DIVIDIR EL CONTENIDO
            aux.id = 1 + buscaIDBloque(rutaSinDataNode, numDataNode[xc]);
            aux.NdataNode = numDataNode[xc];
            aux.state = TRUE;
            bloques[xc] = aux;
            emptyArray(temp);
            //PARA MARCAR ESPACIO
            dataBlock temp1;
            strcpy(temp1.bd_data, "MARCADO");
            temp1.id = aux.id;
            temp1.NdataNode = numDataNode[xc];
            temp1.next = -1;
            temp1.state = TRUE;
            escribeDatablock(rutaSinDataNode, numDataNode[xc],temp1);
        }
        //CREO EL REGISTRO DE NOMBRE PARA TABLA
        Data_nombre nuevo;
        time_t t;
        time(&t);
        strcpy(nuevo.date, ctime(&t));
        nuevo.dnode = numDataNode[0];
        nuevo.init_block = bloques[0].id;//RECUERDA QUE ES ID - 1
        strcpy(nuevo.name, nombre);
        nuevo.padre = mbr.mbr_t_names + (indice*sizeof(Data_nombre)*10);
        nuevo.state = TRUE;
        nuevo.type = ARCHIVO;
        int v;
        for(v = 0; v< qblocks; v++)
        {
            if(v!= (qblocks-1))
            {
                bloques[v].next = bloques[v+1].id;
                bloques[v].NdataNode = bloques[v+1].NdataNode;
            }
            else
            {
                bloques[v].next = -1;
                bloques[v].NdataNode = -1;
            }
            escribeDatablock(rutaSinDataNode, numDataNode[v], bloques[v]);
        }
        escribeDatanombre(rutaglob, indice, nuevo, mbr);
        return TRUE;
    }
}
int buscaIDBloque(char rutaSinData[], int numeroDataNode)
{
    char route[PATH_SIZE];
    strcpy(route, rutaSinData);
    strcat(route, "/DataNode");
    char temp[2];
    sprintf(temp, "%d", numeroDataNode);
    strcat(route, temp);
    strcat(route, ".bin");
    int index = 0;
    FILE *f = fopen(route, "r");
    if(f!=NULL)
    {
        fseek(f, 0, SEEK_END);
        int filesize = ftell(f);
        rewind(f);
        int maxBlocks = floor(filesize/sizeof(dataBlock));
        int x;
        for(x = 0; x<maxBlocks; x++)
        {
            dataBlock aux;
            fread(&aux, sizeof(dataBlock), 1, f);
            if(aux.state == FALSE)
            {
                break;
            }
            index++;
        }
        fclose(f);
        return index;
    }
    return index;
}
void escribeDatablock(char rutaSinData[], int numerDatanode, dataBlock bloque)
{
    char route[PATH_SIZE];
    strcpy(route, rutaSinData);
    strcat(route, "/DataNode");
    char temp[2];
    sprintf(temp, "%d", numerDatanode);
    strcat(route, temp);
    strcat(route, ".bin");

    FILE *f = fopen(route, "r+");
    if(f!=NULL)
    {
        fseek(f,(bloque.id-1)*sizeof(dataBlock), SEEK_SET);
        fwrite(&bloque, sizeof(dataBlock), 1, f);
        fclose(f);
    }
}
void escribeDatanombre(char rutaglob[], int indice, Data_nombre nom, MBR mbr)
{
    int punt = mbr.mbr_t_names + (indice * sizeof(Data_nombre)*10);
    FILE *f = fopen(rutaglob, "r+");
    if(f!=NULL)
    {
        int index = buscaIndexDisponible(punt, rutaglob);
        fseek(f,punt + (index * sizeof(Data_nombre)), SEEK_SET);
        fwrite(&nom, sizeof(Data_nombre), 1, f);
        fclose(f);
    }
}
void separandoContenido(char contenido[], char tempora[], int inicio, int final)
{
    int x;
    int index = 0;
    for(x = inicio; x <final; x++)
    {
        if(contenido[x]!='\0')
        {
            tempora[index] = contenido[x];
            index++;
        }
        else
        {
            break;
        }
    }
}
void emptyArray(char cadena[])
{
    int len = strlen(cadena);
    int x;
    for(x = 0; x< len; x++)
    {
        cadena[x] = '\0';
    }
}
int devuelvemeIndiceDeRuta(int indice, char rutaglob[], MBR mbr, int tipoRuta, char rutaCreacion[])
{
    if(strcmp(rutaCreacion, "NAC")!=0)
    {
        if(tipoRuta !=1)
        {
            indice = 0;
        }
        char cadenaaux[PATH_SIZE] = "";
        int lenght = strlen(rutaCreacion);
        int x;
        int ban = 0;
        for(x = 0; x< lenght; x++)
        {
            if(rutaCreacion[x]=='/' || rutaCreacion[x]=='\0')//SI EL CARACTER NO ES SLASH O FINALIZACION
            {
                //BUSCAR Y LIMPIAR
                int p = mbr.mbr_t_names + (indice * sizeof(Data_nombre)*10);//CALCULO EL PUNTERO
                int puntero = buscaPunteroDeCarpeta(p,rutaglob, cadenaaux, SEEK_SET);
                if(puntero!= -1)
                {
                    indice = (puntero - mbr.mbr_t_names)/(sizeof(Data_nombre)*10);
                }
                else
                {
                    //SI NO ENCUENTRO ENTONCES ROMPO EL CICLO Y LO IGUALO A MENOS 1 PARA INDICAR EL ERROR
                    indice = -1;

                    return FALSE;
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
                cadenaaux[ban] = rutaCreacion[x]; //HAS LA NUEVA CADENA
                ban++;

            }
        }
        return indice;
    }
    else
    {
        return indice;
    }
}
dataBlock buscameDataBlock(char rutaSinDataNode[], int numBloque, int numNode)
{
    char route[PATH_SIZE];
    strcpy(route, rutaSinDataNode);
    strcat(route, "/DataNode");
    char temp[2];
    sprintf(temp, "%d", numNode);
    strcat(route, temp);
    strcat(route, ".bin");
    dataBlock nuevo;
    FILE *f = fopen(route, "r");
    if(f!=NULL)
    {
        fseek(f,(numBloque-1)*sizeof(dataBlock),SEEK_SET);
        fread(&nuevo, sizeof(dataBlock),1,f);
        fclose(f);
    }
    return nuevo;
}
void eliminaDataBlock(char rutaSinDataNode[], int numBloque, int numNode)
{
    char route[PATH_SIZE];
    strcpy(route, rutaSinDataNode);
    strcat(route, "/DataNode");
    char temp[2];
    sprintf(temp, "%d", numNode);
    strcat(route, temp);
    strcat(route, ".bin");
    dataBlock eliminar;
    FILE *f = fopen(route, "r+");
    if(f!=NULL)
    {
        strcpy(eliminar.bd_data, "EMPTY");
        eliminar.id = numBloque;
        eliminar.NdataNode = -1;
        eliminar.next = -1;
        eliminar.state = FALSE;
        fseek(f,(numBloque-1)*sizeof(dataBlock), SEEK_SET);
        fwrite(&eliminar, sizeof(dataBlock),1,f);
        fclose(f);
    }
}
Data_nombre buscaDataNombre(int PTinit, char nombre[], char rutaglob[])
{
    Data_nombre aux;
    FILE *f = fopen(rutaglob, "r");
    if(f!=NULL)
    {
        int x;
        for(x = 0; x < 10; x++)
        {
            Data_nombre temp;
            fseek(f, PTinit+(x*sizeof(Data_nombre)), SEEK_SET);
            fread(&temp, sizeof(Data_nombre),1,f);
            if(strcmp(temp.name, nombre)==0)
            {
                aux = temp;
                break;
            }
        }
        fclose(f);
    }
    return aux;
}
void eliminaDataNombre(int PTinit, char nombre[], char rutaglob[])
{
    Data_nombre eliminar;
    strcpy(eliminar.date, "EMPTY");
    eliminar.state = FALSE;
    eliminar.dnode = -1;
    eliminar.init_block = -1;
    strcpy(eliminar.name, "EMPTY");
    eliminar.padre = -1;
    eliminar.state = FALSE;
    eliminar.type = -1;
    FILE *f = fopen(rutaglob, "r+");
    if(f!=NULL)
    {
        int index=0;
        int bandera = FALSE;
        int x;
        for(x = 0; x < 10; x++)
        {
            Data_nombre temp;
            fseek(f, PTinit+(x*sizeof(Data_nombre)), SEEK_SET);
            fread(&temp, sizeof(Data_nombre),1,f);
            if(strcmp(temp.name, nombre)==0)
            {
                bandera = TRUE;
                break;
            }
            index ++;
        }
        if(bandera == TRUE)
        {
            fseek(f, PTinit+(index*sizeof(Data_nombre)), SEEK_SET);
            fwrite(&eliminar, sizeof(Data_nombre), 1, f);
        }
        fclose(f);
    }
}
void buscaContenidoDeArchivo(int indice, char rutaglob[], MBR mbr, int tipoRuta, char rutaCreacion[], char nombreFile[], char rutaSinDataNode[])
{
    //ENCONTRARE EL INDICE INDICADO
    indice = devuelvemeIndiceDeRuta(indice, rutaglob, mbr, tipoRuta, rutaCreacion);
    if(indice != -1 && compruebaSiExisteEsteNombreEn(ARCHIVO, mbr, indice, rutaglob,nombreFile)==TRUE)
    {
        //ENCUENTRO EL DATANOMBRE QUE BUSCO
        int pt = mbr.mbr_t_names + (sizeof(Data_nombre)*indice*10);
        Data_nombre auxi = buscaDataNombre(pt, nombreFile, rutaglob);
        int next = auxi.init_block;
        int node = auxi.dnode;
        char contenido[500];//CONTENIDO
        emptyArray(contenido);
        while(next!=-1)
        {
            dataBlock temp = buscameDataBlock(rutaSinDataNode, next, node);
            strcat(contenido, temp.bd_data);
            next = temp.next;
            node = temp.NdataNode;
        }
        printf("|| CONTENIDO DE ARCHIVO: %s\n", contenido);
        getchar();
    }
    else
    {
        printf("|| ERROR EN EL PATH... \n");
        getchar();
    }

    //
}
void eliminaArchivo(int indice, char rutaglob[], MBR mbr, int tipoRuta, char rutaCreacion[], char nombreFile[], char rutaSinDataNode[])
{
    //ENCONTRARE EL INDICE INDICADO
    indice = devuelvemeIndiceDeRuta(indice, rutaglob, mbr, tipoRuta, rutaCreacion);  
    if(indice!=-1 && compruebaSiExisteEsteNombreEn(ARCHIVO, mbr, indice, rutaglob,nombreFile)==TRUE)
    {
        //ENCUENTRO EL DATANOMBRE QUE BUSCO
        int pt = mbr.mbr_t_names + (sizeof(Data_nombre)*indice*10);
        Data_nombre auxi = buscaDataNombre(pt, nombreFile, rutaglob);
        int next = auxi.init_block;
        int node = auxi.dnode;
        while(next!=-1)
        {
            dataBlock temp = buscameDataBlock(rutaSinDataNode, next, node);
            eliminaDataBlock(rutaSinDataNode, next, node);
            next = temp.next;
            node = temp.NdataNode;

        }
        eliminaDataNombre(pt, nombreFile, rutaglob);
        printf("|| ARCHIVO ELIMINADO.... \n");
        getchar();
    }
    else
    {
        printf("|| OCURRIO UN ERROR CON EL PATH INDICADO \n");
        getchar();
    }
}
void eliminaCarpeta(int indice, char rutaglob[], MBR mbr, int tipoRuta, char rutaCreacion[], char nombreFile[], char rutaSinDataNode[])
{
    //ENCONTRAR EL INDICE INDICADO
    indice = devuelvemeIndiceDeRuta(indice, rutaglob, mbr, tipoRuta, rutaCreacion);
    if(indice!=-1 && compruebaSiExisteEsteNombreEn(CARPETA, mbr, indice, rutaglob,nombreFile)==TRUE)
    {
        //ENTCONTRAR EL DATANOMBRE QUE BUSCO
        int pt = mbr.mbr_t_names + (sizeof(Data_nombre)*indice*10);
        Data_nombre auxi = buscaDataNombre(pt,nombreFile, rutaglob);

        //AQUI YA OBTENGO SU PUNTERO PARA PODER ELIMINARLO EN EL METODO DE ELIMINAR TODO LO QUE TIENE
        int nIndice = (auxi.init_block-mbr.mbr_t_names)/(sizeof(Data_nombre)*10);
        eliminaContenidoCarpeta(nIndice, rutaglob, mbr, rutaSinDataNode);
        eliminaDataNombre(pt, auxi.name, rutaglob);
        printf("|| DIRECTORIO Y SUBDIRECTORIOS ELIMINADOS...\n");
        getchar();
    }
    else
    {
        printf("|| OCURRIO UN ERROR CON EL PATH INDICADO \n");
        getchar();
    }
}

void eliminaContenidoCarpeta(int indice, char rutaglob[], MBR mbr, char rutaSinData[])
{
    int pt = mbr.mbr_t_names + (sizeof(Data_nombre)*10*indice);
    FILE *f = fopen(rutaglob, "r+");
    if(f!=NULL)
    {
        int x;
        for(x = 0; x<10; x++)
        {
            Data_nombre aux;
            fseek(f, pt+(x*sizeof(Data_nombre)),SEEK_SET);
            fread(&aux, sizeof(Data_nombre), 1, f);
            if(aux.state == TRUE)//SI ESTA OCUPADA
            {
                if(aux.type == CARPETA)
                {
                    //LLAMADA RECURSIVA AL ELIMINAR
                    int nIndice = (aux.init_block - mbr.mbr_t_names)/(sizeof(Data_nombre)*10);
                    eliminaContenidoCarpeta(nIndice, rutaglob, mbr, rutaSinData);
                }
                else if(aux.type == ARCHIVO)
                {
                    //LLAMO A ALIMINAR ARCHIVO
                    eliminaArchivo(indice,rutaglob, mbr,1,"NAC", aux.name,rutaSinData);
                }
                fseek(f, pt+(x*sizeof(Data_nombre)),SEEK_SET);
                Data_nombre eliminar;
                strcpy(eliminar.date, "EMPTY");
                eliminar.state = FALSE;
                eliminar.dnode = -1;
                eliminar.init_block = -1;
                strcpy(eliminar.name, "EMPTY");
                eliminar.padre = -1;
                eliminar.state = FALSE;
                eliminar.type = -1;
                fwrite(&eliminar, sizeof(Data_nombre), 1, f);
            }
        }
        fclose(f);
    }
}
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*/
int editaElArchivo(int indice, char rutaglob[], MBR mbr, char nuevaInfo[], int tipoRuta, char rutaSinDataNode[], char rutaCreacion[], char nombre[], int tipoOperacion)
{
    if(compruebaCompletExistenciaDe(ARCHIVO, mbr, indice, rutaglob, nombre,tipoRuta, rutaCreacion)==TRUE)
    {
        if(tipoOperacion == 1)
        {
            //APPEND
            //TARIGO LA INFORMACION QUE PUEDO GUARDAR
            char info[500];
            traeInfoArchivo(indice, rutaglob, mbr, tipoRuta, rutaCreacion, nombre, rutaSinDataNode,info);
            //ELIMINO EL ARCHIVO
            eliminaArchivo(indice, rutaglob, mbr, tipoRuta, rutaCreacion, nombre, rutaSinDataNode);
            strcat(info, " ");
            strcat(info, nuevaInfo);
            //VUELVO A ESCRIBIR EL ARCHIVO
            escribeArchivo(indice, rutaglob, mbr, info, tipoRuta, rutaSinDataNode, rutaCreacion, nombre);
            return TRUE;
        }
        else
        {
            //OVERWRITE
            //ELIMINO EL ARCHIVO
            eliminaArchivo(indice, rutaglob, mbr, tipoRuta, rutaCreacion, nombre, rutaSinDataNode);
            //ESCRIBO DE NUEVO
            escribeArchivo(indice, rutaglob, mbr, nuevaInfo, tipoRuta, rutaSinDataNode, rutaCreacion, nombre);
            return TRUE;
        }
        return TRUE;
    }
    else
    {
        return FALSE;
    }

}
void traeInfoArchivo(int indice, char rutaglob[], MBR mbr, int tipoRuta, char rutaCreacion[], char nombreFile[], char rutaSinDataNode[], char tempo[])
{
    indice = devuelvemeIndiceDeRuta(indice, rutaglob, mbr, tipoRuta, rutaCreacion);
    if(indice!=-1 && compruebaSiExisteEsteNombreEn(ARCHIVO, mbr, indice, rutaglob,nombreFile)==TRUE)
    {
        int pt = mbr.mbr_t_names + (sizeof(Data_nombre)*indice*10);
        Data_nombre auxi = buscaDataNombre(pt, nombreFile, rutaglob);
        int next = auxi.init_block;
        int node = auxi.dnode;
        emptyArray(tempo);
        while(next!=-1)
        {
            dataBlock temp = buscameDataBlock(rutaSinDataNode, next, node);
            strcat(tempo, temp.bd_data);
            next = temp.next;
            node = temp.NdataNode;
        }
    }
}
int compruebaSiExisteEsteNombreEn(int tipoBuscado, MBR mbr, int indice, char rutaglob[], char nombreBuscado[])
{
    int pt = mbr.mbr_t_names + (indice * 10 * sizeof(Data_nombre));
    int ban = FALSE;
    FILE *f = fopen(rutaglob, "r");
    if(f!=NULL)
    {
        int x;
        Data_nombre aux;
        for(x = 0; x < 10 ; x++)
        {
            fseek(f, pt + (x*sizeof(Data_nombre)),SEEK_SET);
            fread(&aux, sizeof(Data_nombre), 1, f);
            if(aux.state == TRUE && aux.type == tipoBuscado && strcmp(nombreBuscado, aux.name)==0)
            {
                ban = TRUE;
                break;
            }
        }
        fclose(f);
        return ban;
    }
}
int compruebaCompletExistenciaDe(int tipoBuscado, MBR mbr, int indice, char rutaglob[], char nombreFile[], int tipoRuta, char rutaCreacion[])
{
    indice = devuelvemeIndiceDeRuta(indice, rutaglob, mbr, tipoRuta, rutaCreacion);
    if(indice!=-1 && compruebaSiExisteEsteNombreEn(tipoBuscado, mbr, indice, rutaglob,nombreFile)==TRUE)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
/*-------------------------------------------------------------------------------------------------------------------*/
int copiaElArchivo(int indice, char rutaglob[], MBR mbr,int tipoRuta, char rutaSinDataNode[], char pathOrigen[], char nombre[], char pathDest[])
{
    indice = devuelvemeIndiceDeRuta(indice, rutaglob, mbr, tipoRuta, pathOrigen);
    char contenido[500];
    emptyArray(contenido);
    traeInfoArchivo(indice, rutaglob, mbr, tipoRuta, pathOrigen, nombre, rutaSinDataNode, contenido);
    int x;
    char tempname[LINE_SIZE];
    strcpy(tempname, nombre);
    while (compruebaCompletExistenciaDe(ARCHIVO, mbr, indice, rutaglob, tempname, tipoRuta, pathDest)==TRUE)
    {
        x++;
        char temp[LINE_SIZE];
        sprintf(temp, "%d", x);
        strcat(temp, tempname);
        strcpy(tempname, temp);
    }
    int indice2 = devuelvemeIndiceDeRuta(indice, rutaglob, mbr, tipoRuta, pathDest);
    escribeArchivo(indice2, rutaglob, mbr, contenido, tipoRuta, rutaSinDataNode, pathDest, tempname);
    return TRUE;

}
void recorreTabla(int indice, FILE *f, FILE *txt, MBR mbr,char rSinData[], char rutaGlobal[])
{
    int pt = mbr.mbr_t_names + (sizeof(Data_nombre)*10*indice);
    int x;
    for(x = 0; x<10; x++)
    {
        Data_nombre aux;
        fseek(f, pt + (sizeof(Data_nombre)*x),SEEK_SET);
        fread(&aux, sizeof(Data_nombre), 1, f);
        if(aux.type == ARCHIVO && aux.state == TRUE)
        {
            char rutaPadres[PATH_SIZE] = "";
            emptyArray(rutaAuxiliar);
            buscaPadres(aux.padre, rutaGlobal, mbr, rutaPadres);
            fprintf(txt, "=================================================================================================================================================================\n");
            fprintf(txt, "|| * RUTA: %s || ARCHIVO: %s \n", rutaAuxiliar,aux.name);

            //AQUI DEBERIA DE RECORRER LOS NODOS
            int next = aux.init_block;
            int node = aux.dnode;
            while(next!=-1)
            {
                dataBlock temp = buscameDataBlock(rSinData, next, node);
                fprintf(txt,"||    - NUMERO DE DATANODE: %i | CONTENIDO: %s\n", node, temp.bd_data);
                next = temp.next;
                node = temp.NdataNode;
            }
            fprintf(txt, "=================================================================================================================================================================\n");
            fprintf(txt, "                                                                                                                                                             \n");
        }

    }
}

void buscaPadres(int puntero, char rutaGlob[], MBR mbr, char rutaFinal[])
{
    if(puntero!=mbr.mbr_t_names)
    {
        int indice = (puntero - mbr.mbr_t_names)/(sizeof(Data_nombre)*10);
        emptyArray(rutaFinal);
        char conatena[LINE_SIZE]="";

        char tempo[LINE_SIZE];
        buscaCarpetaParaAmbito(indice, rutaGlob, tempo);
        strcat(conatena, tempo);
        strcat(conatena, "/");
        strcat(conatena, rutaFinal);
        strcpy(rutaFinal, conatena);
        strcat(conatena, rutaAuxiliar);
        strcpy(rutaAuxiliar, conatena);
        Data_nombre aux = buscaCarpetaPadre(mbr, rutaGlob, puntero);
        buscaPadres(aux.padre, rutaGlob, mbr, rutaFinal);
    }
}

Data_nombre buscaCarpetaPadre(MBR mbr, char rutaGlob[], int ptr)
{
    int x;
    FILE *f = fopen(rutaGlob, "r");
    Data_nombre ret;
    if(f!=NULL)
    {
        fseek(f, mbr.mbr_t_names, SEEK_SET);
        for(x = 0 ; x< 10000; x++)
        {
            Data_nombre temp;
            fread(&temp, sizeof(Data_nombre),1,f);
            if(temp.state == TRUE && temp.type == CARPETA && ptr == temp.init_block)
            {
                ret = temp;
                break;
            }
        }
        fclose(f);
        return ret;
    }
    return ret;

}

void buscarPorNombre(MBR mbr, char rutaGlob[], char nombre[])
{
    FILE *f = fopen(rutaGlob, "r");
    if(f!=NULL)
    {
        Data_nombre aux;
        int x;
        fseek(f, mbr.mbr_t_names, SEEK_SET);
        for(x = 0; x< 10000; x++)
        {
            fread(&aux, sizeof(Data_nombre), 1, f);
            if(aux.state == TRUE && strcmp(aux.name, nombre)==0)
            {
                emptyArray(rutaAuxiliar);
                char temp[LINE_SIZE] = "";
                buscaPadres(aux.padre, rutaGlob, mbr,temp);
                printf("|| RUTA: %s || COINCIDENCIA: %s\n", rutaAuxiliar, aux.name);
            }
        }
        fclose(f);
    }
}
#endif // OPERACIONES_201503476_C
