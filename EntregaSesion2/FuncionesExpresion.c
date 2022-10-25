#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FuncionesExpresion.h"
#include "abin.h"


///Devuelve la prioridad del operador dentro de la pila.
///Prioridad('(')=0
int prioridadDentro(char op) {
    int prior;
    switch (op) {
        case '^': prior = 3;
            break;
        case '*': case '/': prior = 2;
            break;
        case '+': case '-': prior = 1;
            break;
        case '(': prior = 0; ///nunca va a entrar en la pila, provoca vaciado
            break;
    }
    return prior;
}

///Devuelve la prioridad del operador fuera de la pila.
///Prioridad('(')=4
int prioridadFuera(char op) {
    int prior;
    switch (op) {
        case '^': prior = 3;
            break;
        case '*': case '/': prior = 2;
            break;
        case '+': case '-': prior = 1;
            break;
        case '(': prior = 4; ///para que SIEMPRE entre en la pila
            break;
    }
    return prior;
}

///Devuelve 1 si c es un operador: +, -, /, *, ^, ()
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

///Devuelve 1 si c es un operando: mayúsculas y minúsculas
///completar para caracteres 0 a 9  HECHOOO
unsigned esOperando(char c) {
    if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c>= 48 && c<=57) )///añadimos para que se pueden meter en operandos numeros del 0 al 9
        return 1;
    else
        return 0;
}

///Recibe una cadena de caracteres y devuelve el arbol de expresion
///DEBES ESCRIBIR ESTA FUNCIÓN
abin arbolExpresion(const char *expr_infija) {
    tipoelemOperandos aux; ///declaro el Arbol
    pilaOperandos Pilaoperandos;
    pilaOperadores Pilaoperadores;
    tipoelemOperadores c;
    int i=0;

    ///Creo las dos pilas (pilaOperadores y pilaOperandos) y el árbol que contendrá la expresión

    crearPilaOperadores(&Pilaoperadores);
    crearPilaOperandos(&Pilaoperandos);

    c = expr_infija[i];

    ///Recorro la cadena de caracteres '
    while (c != '\0'){ ///bucle mientras no sea el final de la cadena
        if (esOperando(c)){ ///si c es un operandos
            crear(&aux); ///creo el arbol auxiliar fuera
            insizq(&aux,c); ///inserto por la izquierda, es la raiz así que no importa por donde insertemos
            pushOperandos(&Pilaoperandos,aux);///metemos el arbol en la pila operandos


        }
        else if(esOperador(c)){ /// si c es un operador
            ///pilaOperadores no vacía Y prioridad_fuera(c)<=prioridad_dentro(tope(pilaOperadores))
            while((!esVaciaPilaOperadores(Pilaoperadores))&&(prioridadFuera(c)<= prioridadDentro(topeOperadores(Pilaoperadores)))){

                resolver(&Pilaoperadores,&Pilaoperandos);/// funcion para no reptir codigo
            }
            pushOperadores(&Pilaoperadores,c);


        }else if(c==')'){
            while(topeOperadores(Pilaoperadores)!='('){

                resolver(&Pilaoperadores,&Pilaoperandos);/// funcion para no reptir codigo

            }
            popOperadores(&Pilaoperadores);


        }
        i++; ///incrementamos la i
        c = expr_infija[i]; ///actualizamos
        //if(!esVacio(aux)) destruir(&aux);


    }
    while (!esVaciaPilaOperadores(Pilaoperadores)){

        resolver(&Pilaoperadores,&Pilaoperandos);/// funcion para no reptir codigo

        //if(!esVacio(&aux)) destruir(&aux);

    }
    abin solucion = topeOperandos(Pilaoperandos);
    destruirPilaOperadores(&Pilaoperadores);
    destruirPilaOperandos(&Pilaoperandos);
    return solucion;



}
void resolver(pilaOperadores *Pilaoperadores, pilaOperandos *Pilaoperandos){
    tipoelemOperandos aux;
    crear(&aux);

    insizq(&aux,topeOperadores(*Pilaoperadores)); ///inserto por la izquierda, es la raiz así que no importa por donde insertemos
    popOperadores(Pilaoperadores);

    //crear(&aux); ///creo el arbol

    ///INSERTO LA RAMA DERECHA
    insArbolder(&aux, topeOperandos(*Pilaoperandos)); /// insertamos el tope de la pila en el arbol derecho
    popOperandos(Pilaoperandos); /// desapilamos el tope

    ///INSERTO LA RAMA IZQUIERDA
    insArbolizq(&aux, topeOperandos(*Pilaoperandos)); ///insertamos el tope de la pila en el arbol izquierdo
    popOperandos(Pilaoperandos); ///desapilamos el tope

    pushOperandos(Pilaoperandos,aux); ///insertamos el arbol aux en la pila





}

