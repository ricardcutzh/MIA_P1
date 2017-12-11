#include <stdio.h>
#include<cadenas_201503476.h>
#include<consola_201503476.h>
#include<structs_201503476.h>
int main()
{
    //LLAMADA A LOS METODOS QUE SE NECESITAN
    int dispo = leeDisponible();
    if(dispo == 0)
    {
        escribirDiscos(-1,"","",0,FALSE);
    }
    menu();
    return 0;
}
