#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

/*
 * Programa que muestra el uso del TAD grafo de números enteros
 */

//fsacnf(archivo,%[⁻=]%c][^\r\n]

int main(int argc, char** argv) {
    //Grafo de números enteros
    grafo G; //grafo
    char opcion;

    //Creo el grafo
    crear_grafo(&G);
    cargar_archivo(&G);
    do {
        printf("\n\na. Insertar nuevo vertice\n");
        printf("b. Eliminar vertice\n");
        printf("c. Crear arco\n");
        printf("d. Eliminar arco\n");
        printf("i. Imprimir grafo\n");
        printf("e. Imprimir a ruta mais curta\n");
        printf("f. Imprimir a ruta mais rapida\n");
        printf("g. Imprimir a ruta mais economica\n");
        printf("h. Imprimir a mínima infraestrutura de conexións que fai que as cidades estean conectadas\n");
        printf("s. Salir\n");

        printf("Opcion: ");
        scanf(" %c", &opcion);
        fgetc(stdin);

        switch (opcion) {
            case 'a':case'A':
                introducir_vertice(&G);
                break;
            case 'b':case 'B':
                eliminar_vertice(&G);
                break;
            case 'c': case 'C':
                nuevo_arco(&G);
                break;
            case 'd': case 'D':
                eliminar_arco(&G);
                break;
            case 'i': case 'I':
                imprimir_grafo(G);
                break;
            case 'e': case 'E':
                //como el primer caso es el cero le pasamos el 0 en el tipo
                algoritmo_Floyd_Warshall(G,0);

                break;
            case 'f': case 'F':
                //como el primer caso es el cero le pasamos el 0 en el tipo
                algoritmo_Floyd_Warshall(G,1);

                break;
            case 'g': case 'G':
                //como el primer caso es el cero le pasamos el 0 en el tipo
                algoritmo_Floyd_Warshall(G,2);

                break;
            case 'h': case 'H':

                break;
            case 's': case 'S':
                opcion='s';
                break;
            default:
                printf("Opción equivocada\n");
        }
    } while (opcion != 's');
    actualizar_archivo(G);
    //Al salir, liberamos la memoria del TAD, lo destruimos
    borrar_grafo(&G);

    return (EXIT_SUCCESS);
}

