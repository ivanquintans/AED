//
// Created by ivan on 29/11/22.
//

#ifndef FUNCIONESBACK_H
#define FUNCIONESBACK_H

#define N 3
//NOS PERMITE UTILIZAR LA VARIABLE GLOBAL DEL MAIN
extern int B[N][N];


/**
 * algoritmo de backtracking que nos proporciona el resultado deseado
 * @param solucion
 */
void Backtracking(int solucion[]);

/**
 * algoritmo de backtracking que nos proporciona el resultado deseado con las funciones del vector usadas
 * @param solucion
 */
void BacktrackingUsadas(int solucion[],int usadas[]);
/**
 * aumenta el valor en el nivel en el que nos encontramos y actualiza el beneficio de la solucion actual
 * @param nivel
 * @param [] solucion.
 * @param *contador
 */
void Generar(int nivel, int solucion[],int * bact,int *contador);

/**
 * determina si la solucion es valida
 * @param  nivel
 * @param  [] solucion.
 * @param *contador
 * @param *contadorCriterio
 * @return devuelve 1 si es valida la solucion y 0 si no.
 *
 */
int Solucion(int nivel, int solucion[],int *contador,int *contadorCriterio);


/**
 * devuelve 1 si las tareas son asignadas correctamente
 * @param  nivel
 * @param [] solucion.
 * @return devuelve 1 si se cumple la comprobacion y 0 si no.
 */
int Criterio(int nivel, const int solucion[],int *contador);

/**
 * comprueba si hay mas tareaas que se pueden asignar
 * @param  nivel
 * @param  [] solucion.
 * @param *contador
 * @return devuelve 1 si tienen mas tareas y 0 si no.
 */
int MasHermanos(int nivel, const int solucion[],int *contador);

/**
 * retrocedemos al nivel amterior y actulizamos el benficio actual
 * @param nivel
 * @param [] solucion.
 * @param *contador
 */
void Retroceder(int *nivel, int solucion[],int *bact,int *contador);

/**
 * misma funcion que la funcion Generar pero utilizando el vector usadas
 * @param nivel
 * @param solucion
 * @param bact
 ** @param usadas
 */
void GenerarUsadas(int nivel, int solucion[],int * bact,int usadas[],int *contador);


/**
 * misma funcion que la funcion Criterio pero utilizando el vector usadas
 * @param nivel
 * @param solucion
 * @param usadas
 * @param *contador
 */
int CriterioUsadas(int nivel, const int solucion[],int usadas [],int *contador);

/**
 * misma funcion que la funcion Retroceder pero utilizando el vector usadas
 * @param nivel
 * @param solucion
 * @param bact
 * @param usadas
 * @param *contador
 */
void RetrocederUsadas(int *nivel, int solucion[],int *bact,int usadas[],int *contador);


#endif //FUNCIONESBACK_H
