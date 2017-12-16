#include <stdio.h>
#include<cadenas_201503476.h>
#include<consola_201503476.h>
#include<structs_201503476.h>
#include<time.h>
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
    int y = sizeof(dataBlock);
    int j = sizeof(datanode);
    printf("%i\n",y);
    time_t t;
    time(&t);


    printf("Today's date and time : %s",ctime(&t));
    getchar();*/
    /*int x;
    for(x = 0; x< 10;x++)
    {
        printf("%d \n",randomGen(1,4));
    }*/
    return 0;
}
