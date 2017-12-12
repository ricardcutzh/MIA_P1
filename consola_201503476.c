#ifndef CONSOLA_201503476_C
#define CONSOLA_201503476_C
#include<consola_201503476.h>

//VALIDA
int valida(string cad)
{
    if(strcmp(cad,"1")==0)
    {
        return 1;
    }
    if(strcmp(cad,"2")==0)
    {
        return 2;
    }
    if(strcmp(cad,"3")==0)
    {
        return 3;
    }
    if(strcmp(cad,"4")==0)
    {
        return 4;
    }
    if(strcmp(cad,"5")==0)
    {
        return 5;
    }
    return 0;
}

//OTROS
string typeSize(int tipo)
{
    if(tipo == 1)
    {
        return "Mb";
    }
    if(tipo == 2)
    {
        return "Kb";
    }
    if(tipo == 3)
    {
        return "Bytes";
    }
    return "Mb";
}

//INICIOS
void menu()
{
    int opc = 0;
    string f = nuevaCadena();
    while(opc!=3)
    {
        printf("=======================================================\n");
        printf("||     BIENVENIDO AL ASISTENTE DE DISCOS             ||\n");
        printf("=======================================================\n");
        printf("|| SELECIONE UNA DE LAS OPCIONES:                    ||\n");
        printf("|| 1) CREAR UN NUEVO DISCO                           ||\n");
        printf("|| 2) MONTAR UN DISCO DURO                           ||\n");
        printf("|| 3) SALIR DE ASISTENTE                             ||\n");
        printf("=======================================================\n");
        printf("||>> ");
        gets(f);
        opc = valida(f);
        if(opc!=0)
        {
            if(opc == 1)
            {
                system("clear");
                int discos = countDisks();
                if(discos< DISK_LIMIT)
                {
                    crearDisco();
                }
                else
                {
                    printf("=======================================================\n");
                    printf("||    SE HA LLEGADO AL LIMITE DE DISCOS A CREAR      ||\n");
                    printf("=======================================================\n");
                    printf("\n||Press any key to continue...");
                    getchar();
                }
                //CREAR UN DISCO NUEVO

            }
            else if(opc == 2)
            {
                montarDisco();
            }
        }
        else
        {
            printf("=======================================================");
            printf("\n||ERROR: OPCION INVALIDA INTENTE DE NUEVO...         ||");
            printf("\n||Press any key to continue...");
            getchar();
        }
        system("clear");
    }
    liberaCadena(f);
}

//CREAR
void crearDisco()
{
    string nombre = nuevaCadena();
    string numN = nuevaCadena();
    string space = nuevaCadena();
    string type = nuevaCadena();
    int numNodes = 3; //NUMERO DE DATANODES
    int espacio = 0; //ESPACIO QUE OCUPARA CADA DATANODES
    int tipo = 0; //UNIDAD DE MEDIDA DE CADA DATANODE
    //INICIO DE OPCION DE CREACION DE DISCO
    printf("=======================================================\n");
    printf("||              CREACION DE UN NUEVO DISCO DURO      ||\n");
    printf("=======================================================\n");
    printf("|| INGRESE EL NOMBRE DEL DISCO: >> ");
    gets(nombre);
    printf("|| INGRESE EL NUMERO DE DATANODES: >> ");
    gets(numN);
    numNodes = atoi(numN);
    if(numNodes<3)
    {
        numNodes = 3;
    }
    printf("|| MEDIDA: \n|| 1) Mb \n|| 2) Kb \n|| 3) bytes \n|| >> ");
    gets(type);
    tipo = atoi(type);
    printf("|| ESPACIO PARA CADA DATANODE: >> ");
    gets(space);
    espacio = atoi(space);
    system("clear");
    printf("=======================================================\n");
    printf("||              CREACION DE UN NUEVO DISCO DURO      ||\n");
    printf("=======================================================\n");
    printf("|| INFORMACION DE NUEVO DISCO:                       ||\n");
    printf("|| NOMBRE: %s\n", nombre);
    printf("|| DATANODES: %i\n", numNodes);
    string aux = typeSize(tipo);
    printf("|| ESPACIO POR DATANODE: %i %s\n", espacio, aux);
    printf("=======================================================\n");
    printf("||Press any key to continue...");
    getchar();
    int index = indexDisponible();

    //SE CREA EL DIRECTORIO DONDE SE COLOCARAN LOS ARCHIVOS DEL DISCO
    char cmd[LINE_SIZE];
    sprintf(cmd,"mkdir DISKS/%s", nombre);//CREA EL DIRECTORIO DONDE SE HARAN LOS ARCHIVOS DEL DISCO
    system(cmd);

    //CONCATENACION DEL LA RUTA CON EL NUEVO DIRECTORIO CREADO DONDE SE MANEJARA EL DISCO
    char pathconc[PATH_SIZE] = "DISKS/";
    strcat(pathconc, nombre);

    //SOLO VA A ESCRIBIR EN LA LISTA EL NOMBRE DEL NUEVO DISCO (EL PATH DEBE SER EL DEL NAMENODE)
    escribeListaDisco(index, nombre, pathconc, espacio, TRUE);

    //ESCRIBE EL NAMENODE
    escribeNameNode(pathconc, numNodes);
}

//MONTAR
void montarDisco()
{
    int opc = 0;
    printf("=======================================================\n");
    printf("||           LISTADO DE DISCOS DISPONIBLES           ||\n");
    printf("=======================================================\n");
    imprimirListado();
    printf("=======================================================\n");
    string entrada = nuevaCadena();
    printf("|| ELIJA UNA OPCION >> ");
    gets(entrada);
    opc = atoi(entrada);
    if(opc > countDisks())
    {
        printf("=======================================================\n");
        printf("           OPCION INVALIDA DE MONTAJE...             ||\n");
        printf("=======================================================\n");
        printf("||Press any key to continue...");
    }
    else
    {
        montaDisco(opc);
    }
    printf("||Press any key to continue...");
    getchar();
    system("clear");
}

#endif // CONSOLA_201503476_C
