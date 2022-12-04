#ifndef TABLA_HASH_ENCADENAMIENTO_H
#define TABLA_HASH_ENCADENAMIENTO_H
//////////////////////////////////////////////////////////////////////////////////////////
//////MODIFICACIONES/////////////////////////////////////////////////////////////////////
//1. TAMAÑO DE LA TABLA (CONSTANTE N): probar con distintos tamaños
//2. FUNCIÓN InsertarHash(): convertirla en una función que devuelva 1 si hubo colisión y 0 en caso contrario
//3. FUNCIÓN BuscarHash(): añadir el parámetro nPasosExtraB
//4. FUNCIÓN FuncionHash(): probar con distintos valores de K en función hash tipo 3 
//////////////////////////////////////////////////////////////////////////////////////////

/* 
 * Tabla hash con encadenamiento
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

#define N 10000 /*DEFINIR NUMERO de entradas en la tabla.*/
//El factor de carga es L=n/N, se recomienda L entre 0,5 y 0,75, es decir, N entre 2n y 4n/3
//Debemos probar con n y el primo siguiente mayor que n
//También con factor de carga 0,75: 4n/3 y su primo siguiente
//Y con factor de carga 0,5: 2n y su primo siguiente

typedef TLISTA TablaHash[N];

/**
 * Inicializa cada elemento de la tabla a una lista vacía
 * @param t tabla hash.
 */
void InicializarTablaHash (TablaHash t);

/**
 * Destruye la lista que corresponde a cada elemento de la tabla
 * @param t tabla hash.
 */
void DestruirTablaHash (TablaHash t);

/**
 * Funciones hash: 2 tipos
 * @param cad clave para calcular la posición en la tabla hash.
 * @param tipoFH=1-2, las dos funciones hash implementadas
 * @param K=256, 500, el factor de ponderación para la función hash tipoFH=2 (suma ponderada)
 * @return la posición de cad en la tabla hash
 */
int FuncionHash(char *cad, unsigned int tipoFH, unsigned int K);

/**
 * Buscar una clave en la tabla hash
 * @param t es la tabla hash en la que buscamos la clave
 * @param clavebuscar: es la clave que buscamos
 * @param e es donde almacenamos el elemento encontrado
 * @param tipoFH es la función hash utilizada (1,2)
 * @param K es el factor de ponderación cuando tipoFH=2
 * @param nPasosExtraB son los pasos que tengo que realizar en cada lista hasta encontrar e
 * @return si la búsqueda tuvo éxito
 */
/////////////////////Hay que añadir nPasosExtraB//////////////////////////
int BuscarHash(TablaHash t, char *clavebuscar, TIPOELEMENTO *e, unsigned int tipoFH, unsigned int K,int *nPasosExtraB);

/**
 * Mira si clavebuscar está en la tabla hash
 * @param t es la tabla hash en la que buscamos la clave
 * @param clavebuscar: es la clave que buscamos
 * @param tipoFH es la función hash utilizada (1,2)
 * @param K es el factor de ponderación cuando tipoFH=2
 * @return si la clave está en la tabla
 */
int EsMiembroHash (TablaHash t, char *clavebuscar, unsigned int tipoFH, unsigned int K);

/**
 * Inserta un elemento en una tabla hash al principio de la lista
 * @param t es la tabla hash
 * @param elemento es el elemento que queremos guardar en la tabla
 * @param tipoFH es la función hash utilizada (1,2)
 * @param K es el factor de ponderación cuando tipoFH=2
 * @return devuelve 1 si se produce colisión y 0 en caso contrario
 */
///HACER QUE ESTA FUNCIÓN DEVUELVA UN ENTERO QUE INDIQUE SI HUBO O NO COLISIÓN
///POR TANTO NO SERÁ UNA FUNCIÓN void
int InsertarHash (TablaHash *t, TIPOELEMENTO elemento, unsigned int tipoFH, unsigned int K);

/**
 * Borra un elemento en una tabla hash
 * @param t es la tabla hash
 * @param claveborrar es el elemento que queremos borrar en la tabla
 * @param tipoFH es la función hash utilizada (1,2)
 * @param K es el factor de ponderación cuando tipoFH=2
*/
void BorrarHash (TablaHash *t, char *claveborrar,unsigned int tipoFH, unsigned int K);
#endif	// TABLA_HASH_ENCADENAMIENTO_H

