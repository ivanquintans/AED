#ifndef PILAOPERANDOS_H
#define PILAOPERANDOS_H

#include "abin.h"

//Interfaz TAD pila
typedef void *pilaOperandos; /*tipo opaco*/

//CONTENIDO DE CADA ELEMENTO DE LA PILA
//MODIFICAR: PARA LA PILA DE OPERADORES: char
//MODIFICAR: PARA LA PILA DE OPERANDOS: abin
typedef abin tipoelemOperandos;

//Funciones de creacion y destruccion
/**
 * Crea la pila vacia. 
 * @param P Puntero a la pila. Debe estar inicializada.
 */
void crearPilaOperandos(pilaOperandos *P);

/**
 * Destruye la pila
 * @param P puntero a la pila
 */
void destruirPilaOperandos(pilaOperandos *P);

//Funciones de informacion
/**
 * Comprueba si la pila esta vacia
 * @param P pila
 */
unsigned esVaciaPilaOperandos(pilaOperandos P);

/*
 * Recupera la informacion del tope de la pila
 * @param P pila
 * 
*/
tipoelemOperandos topeOperandos(pilaOperandos P);

//Funciones de insercion/eliminacion
/**
 * Inserta un nuevo nodo en la pila para el elemento E
 * en el tope de la pila
 * @param P puntero a la pila
 * @param E Informacion del nuevo nodo. 
 */
void pushOperandos(pilaOperandos *P, tipoelemOperandos E);

/**
 * Suprime el elemento en el tope de la pila
 * @param P puntero a la pila
 */
void popOperandos(pilaOperandos *P);

#endif	// PILAOPERANDOS_H

