//
// Created by ivan on 3/12/22.
//

#include "funcionesRyP.h"

void AsignacionTrivial(int solucion){

/////////////////////////////////////////////////////////////////////////////////
//INICIALIZACIONES
/////////////////////////////////////////////////////////////////////////////////
    TLISTA LNV;// Lista de nodos vivos
    NODO raiz, x, y;// Nodo raíz, nodo seleccionado (x) y nodo hijo de x (y)
    float C=0;// Variable de poda

    //Inicialización nodo raíz (diapositiva 67)
    raiz.bact = 0;// No hay asignaciones. Beneficio acumulado es 0
    raiz.nivel = -1;// Primer nivel del árbol

    //inicializamos los arrays

    for(int i=0;i<N;i++){
        raiz.tupla[i]=-1; // tupla de solución sin tareas asignadas
        raiz.usadas[i]=0; // todas las tareas están sin usar
    }

    CI_trivial(&raiz);// Cota inferior de raíz (trivial o precisa)
    CS_trivial(&raiz);// Cota superior de raíz (trivial o precisa)
    BE(&raiz);// Beneficio estimado de la raíz

    //Inicialización variable de poda (diapositiva 74)
    C = raiz.CI; // valor inicial variable de poda

    //Inicialización lista de nodos vivos (diapositiva 74)
    crearLista(&LNV);
    // Guardo raíz como primer elemento de LNV
    insertarElementoLista(&LNV, primeroLista(LNV), raiz);

    while (!esListaVacia(LNV)){
        for(int i=0; i<N;i++){
            y.nivel=x.nivel+1;
            /*No se si es necesario esto*/
            for(int j=0;j<N;j++){
                y.tupla[i]=x.tupla[j]; // tupla de solución sin tareas asignadas
                y.usadas[i]=x.usadas[j]; // todas las tareas están sin usar
            }
            if(!x.usadas[i]){
                y.tupla[y.nivel]=i;
                y.usadas[i]=1;
                y.bact = x.bact + B[y.nivel][i];

                CI_trivial(&y);// Cota inferior de y
                CS_trivial(&y);// Cota superior de y
                BE(&y);// Beneficio estimado de la y


            }


        }






    }

}


void AsignacionPrecisa(int solucion){

}


void BE(NODO *x){
    x->BE=(x->CI+x->CS)/2;
}


void CI_trivial(NODO *x){
    x->CI=x->bact;
}

void CS_trivial(NODO *x){
    int maximo_matriz=0;
    //buscamos el maximo de la matriz
    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            if(B[i][j]>maximo_matriz) maximo_matriz=B[i][j];
        }
    }
    x->CS=x->bact+(N-x->nivel)*maximo_matriz;

}

void CI_precisa(NODO *x){

}


void CS_precisa(NODO *x){

}


int SolucionRyP(NODO x){
    return x.nivel==N;
}


NODO Seleccionar(TLISTA LNV){

    TIPOELEMENTO nodo;
    TPOSICION posicion;
    TIPOELEMENTO maximo;

    /*HAY QUE PROBAR ESTO XD*/
    //if(!esListaVacia(LNV)){

    posicion= primeroLista(LNV);
    //el máximo es el primee elemento de la lista
    recuperarElementoLista(LNV, primeroLista(LNV), &maximo);
    //debemos de recorrer los nodos y buscar el que tenga beneficio maximo
    while (posicion!= finLista(LNV)) {
        recuperarElementoLista(LNV, primeroLista(LNV), &nodo);
        if(nodo.BE>maximo.BE) maximo=nodo;
        posicion=siguienteLista(LNV,posicion); //p+1
    }

    return maximo;

}
//Funciones privadas necesarias para CI_precisa() y CS_precisa()
int _AsignacionVoraz(NODO x) { //Devuelve valor asignación voraz (D70){
    int bacum=0;
    int k=0;
    for ( int i=0;i<x.nivel;i++){
       // k=argmax
       //x.usadas= true;
       bacum+=B[i][k];
    }
    return bacum;
}
int _MaximosTareas(NODO x){ //Devuelve valor máximos tareas (D71)

}

//Función privada necesaria para calcular la solución voraz cuando CI==CS
NODO _SolAsignacionVoraz(NODO x){


}
