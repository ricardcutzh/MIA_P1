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
    /*int x = sizeof(MBR);
    int y = sizeof(Disk);
    int j = sizeof(datanode);
    printf("%i\n",y);*/

    return 0;
}
