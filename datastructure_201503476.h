#ifndef DATASTRUCTURE_201503476_H
#define DATASTRUCTURE_201503476_H
#include<stdlib.h>
#include<stdio.h>
#include<nodo_201503476.h>

//DEFINICION DE UNA LISTA
typedef struct List
{
    nodo *first;
    nodo *last;
    int sz;
}List;

//METODOS GENERALES
int count(List *l);
void deleteList(List *l);
List *newList();
void printList(List *l);

//METODOS DE UNA PILA
void push(List *l, nodo *nuevo);
nodo* pop(List *l);\

//METODOS DE UNA COLA
void queue(List *l, nodo *nuevo);
nodo *deque(List *l);

//METODOS DE UNA LISTA
void insertAt(List *l, nodo *n, int index);
nodo *getElementAt(List *l, int index);//ELIMINA EL ELEMENTO EN EL INDEX INDICADO Y DIVUELVE SU REFERENCIA

#endif // DATASTRUCTURE_201503476_H
