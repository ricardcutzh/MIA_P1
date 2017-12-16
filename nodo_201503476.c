#ifndef NODO_201503476_C
#define NODO_201503476_C
#include<nodo_201503476.h>
#include<stdio.h>

nodo *newNodo()
{
    //ESTRUCTURA OBLIGATORIA
    nodo *n = (nodo*)malloc(sizeof(nodo));
    n->ant = NULL;
    n->sig = NULL;
    //PERSONALIZABLE
    n->valor = 0;
}

//PERMITE IMPRIMIR EL NODO SE SOBRE ESCRIBE CON LA PROPIEDAD QUE SE DESEA IMPRIMIR
void printNode(nodo *n)
{
    printf("val: %i\n",n->valor);
}

#endif // NODO_201503476_C
