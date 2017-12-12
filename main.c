#include <stdio.h>
#include<cadenas_201503476.h>
#include<consola_201503476.h>
#include<structs_201503476.h>
int main()
{
    //LLAMADA A LOS METODOS QUE SE NECESITAN
    FILE *prueba = fopen("DISKS/manage.bin","r");
    if(prueba==NULL)
    {
        escribeListaDisco(-1,"NAC",'"NAC',0,FALSE);
    }
    menu();
    //escribeListaDisco(-1,"hola","hola",0,FALSE);
    //printf("------------------------------------------\n");
    //imprimirListado();
    /*printf("------------------------------------------\n");
    escribeListaDisco(1,"EDITAD", "EDIT", 10, TRUE);
    escribeListaDisco(3,"NUEVO", "EDIT", 10, TRUE);
    imprimirListado();*/

    return 0;
}
