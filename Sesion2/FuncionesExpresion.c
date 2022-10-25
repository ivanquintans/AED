#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "abin.h"

//Devuelve la prioridad del operador dentro de la pila.
//Prioridad('(')=0
int prioridadDentro(char op) {
    int prior;
    switch (op) {
        case '^': prior = 3;
            break;
        case '*': case '/': prior = 2;
            break;
        case '+': case '-': prior = 1;
            break;
        case '(': prior = 0; //nunca va a entrar en la pila, provoca vaciado
            break;
    }
    return prior;
}

//Devuelve la prioridad del operador fuera de la pila.
//Prioridad('(')=4
int prioridadFuera(char op) {
    int prior;
    switch (op) {
        case '^': prior = 3;
            break;
        case '*': case '/': prior = 2;
            break;
        case '+': case '-': prior = 1;
            break;
        case '(': prior = 4; //para que SIEMPRE entre en la pila
            break;
    }
    return prior;
}

//Devuelve 1 si c es un operador: +, -, /, *, ^, ()
unsigned esOperador(char c) {
    unsigned ope;
    switch (c) {
        case '^': case '*': case '/': case '+': case '-': case '(':
            ope = 1;
            break;
        default:
            ope = 0;
    }
    return ope;
}

//Devuelve 1 si c es un operando: mayúsculas y minúsculas
//completar para caracteres 0 a 9
unsigned esOperando(char c) {
    if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) )
        return 1;
    else
        return 0;
}

//Recibe una cadena de caracteres y devuelve el arbol de expresion
//DEBES ESCRIBIR ESTA FUNCIÓN
abin arbolExpresion(char *expr_infija) {

    
    
    
    
}

