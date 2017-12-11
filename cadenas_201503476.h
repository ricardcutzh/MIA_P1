#ifndef CADENAS_201503476_H
#define CADENAS_201503476_H
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#define TRUE 1
#define FALSE 0
//DEFINICION DEL SIZE DEL ARREGLO DE CHAR PARA SIMULAR STRINGS
#define LINE_SIZE 20
/*PROPOSITOS DEL ARCHIVO:
 * MANEJO DE CADENAS
 * DEFINICION DE CONSTANTES
*/
typedef char * string;
void liberaCadena(string cadena);
string quitaEspacios(string cadena);
string nuevaCadena();
void pasameAMinuscula(string cadena);
int cadenaSize(string cadena);


#endif // CADENAS_201503476_H
