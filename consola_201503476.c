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
                //CREAR UN DISCO NUEVO
            }
            else if(opc == 2)
            {

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
    int opc = 0;
    string f = nuevaCadena();

    liberaCadena(f);
}

#endif // CONSOLA_201503476_C
