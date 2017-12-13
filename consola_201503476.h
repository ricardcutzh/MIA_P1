#ifndef CONSOLA_201503476_H
#define CONSOLA_201503476_H
#include<cadenas_201503476.h>
#include<structs_201503476.h>
/*PROPOSITO DE ARCHIVO:
 * MANEJAR LOS METODOS DE CONSOLA
 * HACER LLAMADOS A FUNCIONES QUE SIRVEN EN LA OPERACION DE DISCOS Y ARCHIVOS
*/
//OTROS:
string typeSize(int tipo);
//VALIDACION DE ENTRADA
int valida(string cad);
//MENU DE INICIO:
void menu();
//MENU CREAR DISCO
void crearDisco();
//MENU MONTAR DISCO
void montarDisco();
//CONVERTIDOR A BYTES
int toBytes(int tipo, int espacio);
#endif // CONSOLA_201503476_H
