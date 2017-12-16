#ifndef DATASTRUCTURE_201503476_C
#define DATASTRUCTURE_201503476E_C
#include<datastructure_201503476.h>

//METODOS GENERALES
int count(List *l)
{
    if(l->sz == 0)
    {
        return 0;
    }
    else
    {
        int x = 0;
        nodo *aux = l->first;
        while(aux)
        {
            aux = aux->sig;
            x++;
        }
        return x;
    }
}
void deleteList(List *l)
{
    if(l->sz>0)
    {
        nodo *aux;
        while(l->sz!=0)
        {
            aux = pop(l);
            aux = NULL;
            free(aux);
        }
        l = NULL;
        free(l);
    }
}
List *newList()
{
    List *l = (List*)malloc(sizeof(List));
    return l;
}
void printList(List *l)
{
    printf("=========ELEMENTOS EN LISTA=============\n");
    if(l->sz!=0)
    {
        nodo *aux = l->first;
        while(aux!=NULL)
        {
            printNode(aux);
            aux = aux->sig;
        }
    }
    else
    {
        printf("No hay elementos...\n");
    }
    printf("========= FIN ELEMENTOS EN LISTA========\n");
}

//METODOS DE UNA PILA
void push(List *l, nodo *nuevo)
{
    if(l->sz==0)
    {
        l->first = nuevo;
        l->last = nuevo;
        l->sz++;
    }
    else
    {
        //INSERTA AL PRINCIPIO DE LA LISTA
        nuevo->sig = l->first;
        l->first->ant = nuevo;
        l->first = nuevo;
        l->sz++;
    }
}
nodo *pop(List *l)
{
    if(l->sz==0)
    {
        return NULL;
    }
    else
    {
        nodo *aux = l->first;
        l->first = l->first->sig;
        if(l->first)
        {
            l->first->ant = NULL;
        }
        l->sz--;
        return aux;
    }
}

//METODOS DE UNA COLA
void queue(List *l, nodo *nuevo)
{
    if(l->sz == 0)
    {
        l->first = nuevo;
        l->last = nuevo;
        l->sz++;
    }
    else
    {
        l->last->sig = nuevo;
        nuevo->ant = l->last;
        l->last = nuevo;
        l->sz++;
    }
}
nodo *deque(List *l)
{
    if(l->sz>0)
    {
        nodo *ret = l->last;
        l->last = l->last->ant;
        if(l->sz>1)
        {
            l->last->sig = NULL;
        }
        l->sz--;
        return ret;
    }
    else
    {
        return NULL;
    }
}

//METODOS DE UNA LISTA
void insertAt(List *l, nodo *n, int index)
{
    if(index<l->sz && index>=0)//SI EL INDEX ES VALIDO
    {
        if(index == 0)//EN CASO QUE LA LISTA NO ESTE VACIA Y QUIERO METER EN LE PRIMERA POSICION
        {
            push(l,n);//LLAMO AL METODO PUSH PORUE INCERTO EN LA PRIMERA POSICION
        }
        else if(index == (l->sz-1))//EN CASO DE QUE EL INDEX SEA IGUAL AL ULTIMO ELEMENTO
        {
            queue(l,n);//LLAMO AL METODO QUEUE PORQUE INCERTO EN LA ULTIMA POSICION
        }
        else//EN CASO DE QUE SEA CUALQUIER OTRO INDEX... ASI NO PIERDO LA REFERENCIA AL ULTIMO Y PRIMERO
        {
            int contador = 1;
            nodo *aux = l->first;
            while(contador<index)
            {
                aux = aux->sig;
                contador++;
            }
            aux->sig->ant = n;
            n->sig = aux->sig;
            n->ant = aux;
            aux->sig = n;
            l->sz++;
        }
    }
    else
    {
        printf("index invalido: %i\n",index);
    }
}

nodo* getElementAt(List *l, int index)
{
    if(index<l->sz && index>=0)//SI EL INDEX ES VALIDO
    {
        if(index == 0)
        {
            return pop(l);//SI QUIERO EL INDEX 0 LLAMO A POP
        }
        else if(index == (l->sz-1))
        {
            return deque(l);//SI QUIERO EL ULTIMO ELEMENTO LLAMO A deque
        }
        else//CUALQUIER OTRO INDEX...
        {
            int contador = 1;
            nodo *aux = l->first;
            while (contador<index)
            {
                aux = aux->sig;
                contador++;
            }
            nodo *retorno = aux->sig;
            nodo *elim = aux->sig;
            aux->sig = elim->sig;
            elim->sig->ant = aux;
            free(elim);
            return retorno;
        }
    }
    else//DE LO CONTRARIO
    {
        printf("index invalido: %i\n",index);
        return NULL;
    }
}

#endif // DATASTRUCTURE_201503476_C
