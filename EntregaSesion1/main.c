/* Practica 1: Prueba de manejo de Arboles Binarios  */
#include <stdlib.h>
#include <stdio.h>

#include "abin.h"
#include "recorridos.h"
#include "funcionesArboles.h"

int main(int argc, char** argv) { //SALE WARNING YA QUE ARGC Y ARGV NO SE USAN EN EL PROGRAMA

    abin Arbol, aux=NULL; //aux= NULL antes de la función
    char entrada;

    //Creo el Arbol
    crear(&Arbol);
    printf("Arbol creado\n");

    // Insertamos la raiz
    insizq(&Arbol, 'J');

    //Insertamos lo correspondientes nodos restates del arbol
    insizq(&Arbol,'F'); //Colocamos la F a la izquierda del nodo J
    insder(&Arbol,'M'); //Colocamos la M a la derecha del nodo J

    //Insertamos los nodos de la parte derecha
    //Para eso tendremos que movernos a la derecha de la raíz
    aux = der(Arbol);
    //insertamos nuestros nodos
    insder(&aux,'W'); //Colocamos la W a la derecha del nodo M
    insizq(&aux,'K'); //Colocamos la K a la izquierda del nodo M

    //Insertamos los nodos de la parte izquierda
    //Para eso tendremos que movernos a la izquierda de la raíz
    aux = izq(Arbol);
    //insertamos nuestro nodo
    insder(&aux,'G'); //Colocamos la G a la derecha del nodo F
    insizq(&aux,'D'); //Colocamos la D a la izquierda del nodo F

    //Insertamos los subnodos de la parte izquierda
    //Para eso tendremos que movernos a la izquierda del anterior nodo e este caso F
    aux = izq(aux);
    //insertamos nuestro nodo
    insizq(&aux,'B'); //Colocamos la B a la izquierda del nodo D
    insder(&aux,'E'); //Colocamos la E a la derecha del nodo D

    //Insertamos los subnodos de la parte derecha
    //Para eso tendremos que movernos a la derecha del anterior nodo e este caso F
    aux = der(izq(Arbol)); //de esta manera podemos referenciar el nodo G
    //insertamos nuestro nodo
    insder(&aux,'H'); //Colocamos la H a la derecha del nodo G

    //Imprimimos la altura del árbol final
    printf("Altura de arbol: %d", AlturaArbol(Arbol));


    printf("\nRecorrido en inorden no recursivo (usa pilas):\n "); inordenNR(Arbol);




    // Borramos el arbol derecho de F:
    //aux = izq(Arbol); //nos movemos a la izquierda de la raiz
    // así sería la función si no tuvieramos la busqueda

    aux=NULL;
    printf("\nEscriba el nodo que quiera eliminar:");
    scanf(" %c",&entrada);
    buscar(Arbol,entrada,&aux); //función de busqueda

    supder(&aux); //eliminamos el subarbol
    printf("Arbol derecho del nodo elejido eleminado\n");


    //Imprimimos en inorden, numero de nodos y altura del arbol
    printf("Recorrido InOrden:\n ");     inorden(Arbol);
    printf("\nAltura de arbol: %d", AlturaArbol(Arbol));
    printf("\nN nodos: %d", NumeroNodos(Arbol));


    // Liberamos memoria asociada al arbol:
    destruir(&Arbol);
    //destruir(&aux); NO SE SI ES NECESARIO O ES CORRECTO ESTO.

    return (EXIT_SUCCESS);
}
