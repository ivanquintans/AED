//
// Created by ivan on 3/12/22.
//

#include "lista.h"

#ifndef SESION6_FUNCIONESRYP_H
#define SESION6_FUNCIONESRYP_H

#endif //SESION6_FUNCIONESRYP_H

#define N 3
//NOS PERMITE UTILIZAR LA VARIABLE GLOBAL DEL MAIN
extern int B[N][N];

/**
 * funcion que implementa el algoritmo de asignaciones triviales.
 * @param solucion
 */
void AsignacionTrivial(int solucion);

/**
 * funcion que implementa el algoritmo de asignaciones precisas.
 * @param solucion
 */
void AsignacionPrecisa(int solucion);

// FUNCIONES PARA CALCULAR COTAS Y BENEFICIO

//estimaciones triviales
/**
 * //beneficio estimado trivial-precisa
 * @param x
 */
void BE(NODO *x);

/**
 * //cota inferior estimación trivial (D69)
 * @param x
 */
void CI_trivial(NODO *x);

/**
 * //cota superior estimación trivial (D69)
 * @param x
 * @param B
 */
void CS_trivial(NODO *x);

//estimaciones precisas

/**
 * //cota inferior estimación precisa (D70)
 * @param x
 * @param B
 */
void CI_precisa(NODO *x);

/**
 * //cota superior estimación precisa (D71)
 * @param x
 * @param B
 */
void CS_precisa(NODO *x);


//FUNCIONES NECESARIAS PARA PROCEDIMIENTO DE RyP

/**
 * //determina si x es solución (D68)
 * @param x
 * @return
 */
//int Solucion(NODO x);

/**
 * //Devuelve nodo según estrategia MB-LIFO
 * @param LNV
 * @return NODO
 */
NODO Seleccionar(TLISTA LNV);

