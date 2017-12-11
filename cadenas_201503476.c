#ifndef CADENAS_201503476_C
#define CADENAS_201503476_C
#include<cadenas_201503476.h>
//DEFINICION DE LAS FUNCIONES:


//METODO PARA LIBERAR UNA CADENA (LIMPIAR LA MEMORIA)
void liberaCadena(string cadena)
{
    free(cadena);
    cadena = NULL;
    cadena = (char*)calloc(LINE_SIZE,sizeof(char));
}

//METODO PARA QUITAR ESPACIOS DE UNA CADENA
string quitaEspacios(string cadena)
{
    int x;
    int y;
    string nueva = malloc(sizeof(char)*LINE_SIZE);
    for(x = y = 0; cadena[x] != '\0'; x++)
    {
        if(cadena[x]!=' ')
        {
            nueva[y++] = cadena[x];
        }
    }
    return nueva;
}

//METODO PARA INICIALIZAR LA CADENA
string nuevaCadena()
{
    string nueva = (char*)malloc(sizeof(char)*LINE_SIZE);
    return nueva;
}

//METODO PARA PASAR A MINUSCULAS
void pasameAMinuscula(string cadena)
{
    int x;
    for(x =0; cadena[x]!='\0';x++)
    {
        cadena[x] = tolower(cadena[x]);
    }
}

//METODO PARA SABER EL LARGO DE UNA CADENA
int cadenaSize(string cadena)
{
    int x = strlen(cadena);
    return x;
}


#endif // CADENAS_201503476_C
