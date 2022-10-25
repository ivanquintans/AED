#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

//FUNCIONES DEL PROGRAMA DE PRUEBA DE GRAFOS

//Opción a del menú, introducir un vertice en el grafo

void introducir_vertice(grafo *G) {
    tipovertice v1;
    printf("Introduce vertice: ");
    scanf(" %[^\r\n]", v1.nombreCiudad); //declaramos con m ya que nos guarda memoria para un string
    if (existe_vertice(*G, v1))
        printf("Ese vertice ya esta en el grafo\n");
    else
        insertar_vertice(G, v1);
}
//Opción b del menú, eliminar un vértice del grafo

void eliminar_vertice(grafo *G) {
    tipovertice v1;
    printf("Introduce vertice: ");
    scanf(" %[^\r\n]", v1.nombreCiudad);
    if (existe_vertice(*G, v1))
        borrar_vertice(G, v1);
    else
        printf("Ese vertice no existe en el grafo\n");
}

//Opción c del menú, crear una relación entre dos vértices

void nuevo_arco(grafo *G) {
    tipovertice v1, v2;
    float valorcarretera,valorautopista;
    //Insertamos una nueva relación pidiendo los datos al usuario controlando que existan los vértices
    printf("Nueva relacion vertice1-->vertice2\n");
    //Vértice origen del arco
    printf("Introduce vertice origen: ");
    scanf(" %[^\r\n]", v1.nombreCiudad);
    if (!existe_vertice(*G, v1)) {
        printf("El vertice %s no existe en el grafo\n", v1.nombreCiudad);
        return;
    }
    //Vértice destino del arco
    printf("Introduce vertice destino: ");
    scanf(" %[^\r\n]", v2.nombreCiudad);
    if (!existe_vertice(*G, v2)) {
        printf("El vertice %s no existe en el grafo\n", v2.nombreCiudad);
        return;
    }

    //pillamos las distancias

    //carretera
    printf("Introduce la distancia del trayecto para carretera: ");
    scanf("%f", &valorcarretera);

    //autopista
    printf("Introduce la distancia del trayecto para autopista: ");
    scanf("%f", &valorautopista);

    //Creación del arco
    //si no existe distancia entre las carreteras creamos nuestro arco
    if (!distanciaCarreteras(*G, posicion(*G, v1), posicion(*G, v2))) {
        if(valorcarretera>0) {
            InsertarArcoCarretera(G, posicion(*G, v1), posicion(*G, v2), valorcarretera);
        }else printf("VALOR INTRODUCIDO NO VALIDO, NO SE CREO EL ARCO CARRETERA\n");
    }
    //si no hay distancia entre carreteras
    if (!distanciaAutopistas(*G, posicion(*G, v1), posicion(*G, v2))) {
        if(valorautopista>0) {
            InsertarArcoAutopista(G, posicion(*G, v1), posicion(*G, v2), valorautopista);
        } else printf("VALOR INTRODUCIDO NO VALIDO, NO SE CREO EL ARCO AUTOPISTA\n");
    }

}
//Opción d del menú, eliminar una relación entre dos vértices
void eliminar_arco(grafo *G) {
    tipovertice v1, v2;
    char flag;
    //Eliminamos una relación pidiendo los datos al usuario controlando que existan los vértices
    printf("Eliminar relacion vertice1-->vertice2\n");
    //Vértice origen del arco
    printf("Introduce vertice origen: ");
    scanf(" %[^\r\n]", v1.nombreCiudad);
    if (!existe_vertice(*G, v1)) {
        printf("El vertice %s no existe en el grafo\n", v1.nombreCiudad);
        return;
    }
    //Vértice destino del arco
    printf("Introduce vertice destino: ");
    scanf(" %[^\r\n]", v2.nombreCiudad);
    fgetc(stdin);
    if (!existe_vertice(*G, v2)) {
        printf("El vertice %s no existe en el grafo\n", v2.nombreCiudad);
        return;
    }
    //Eliminación del arco
    printf("Que arco desea eliminar: C/A");
    //fgetc(stdin);
    scanf(" %c", &flag);



    switch (flag) {

        case 'C':
            //ELiminacion del arco carreteras
            if (distanciaCarreteras(*G, posicion(*G, v1), posicion(*G, v2))) {
                borrarArcoCarretera(G, posicion(*G, v1), posicion(*G, v2));
            }
            break;

        case 'A':

            //Eliminacion del arco autopista
            if(distanciaAutopistas(*G, posicion(*G, v1), posicion(*G, v2))) {
                borrarArcoAutopista(G, posicion(*G, v1), posicion(*G, v2));
            }

            break;

        default:
            printf("Opcion incorrecta, vuelva a intentar eliminar el arco");
    }
}
//Opción i del menú, imprimir el grafo
//Función que imprime el grafo utilizando num_vertices para saber cuántos vértices tiene
//y array_vertices para recuperar el vector de vértices y recorrerlo

void imprimir_grafo(grafo G) {
    tipovertice *VECTOR; //Para almacenar el vector de vértices del grafo
    int N; //número de vértices del grafo

    //Para recorrerla, simplemente vamos a recorrer la matriz de adyacencia
    N = num_vertices(G);
    VECTOR = array_vertices(G);

    int i, j;
    printf("El grafo actual es:\n");
    for (i = 0; i < N; i++) {
        //Imprimo el vértice
        printf("Vertice(%d): %s\n", i, VECTOR[i].nombreCiudad);
        //Chequeo sus arcos
        for (j = 0; j < N; j++) {

            //si son carreteras
            if (distanciaCarreteras(G, i, j)) {
                printf("\t-->%s(%.2f kms)\n", VECTOR[j].nombreCiudad,distanciaCarreteras(G, i, j));
            }
            //si son autopistas
            if (distanciaAutopistas(G, i, j)) {
                printf("\t==>%s(%.2f kms)\n", VECTOR[j].nombreCiudad,distanciaAutopistas(G, i, j));
            }
        }
    }
}

