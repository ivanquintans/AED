#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"
#include "funciones.h"

//FUNCIONES DEL PROGRAMA DE PRUEBA DE GRAFOS

//Opción a del menú, introducir un vertice en el grafo

void introducir_vertice(grafo *G) {
    tipovertice v1;
    printf("Introduce vertice: ");
    scanf(" %[^\r\n]", v1.nombreCiudad);
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
    //si no hay distancia entre autopistas
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

void cargar_archivo(grafo *G) {

    FILE *archivo;
    char linea[300],valores[50];
    char  diferenciador,desprecio;

    tipovertice v1, v2;
    float valorcarretera, valorautopista;


    if ((archivo = fopen("datos.txt", "r")) == NULL) { //COMPROBACION DE APERTURA
        printf("Error al abrir el archivo\n");

    } else { //SI ES CORRECTA

        fgets(linea,300,archivo);
        strip_line(linea);
        while (strcmp(linea,"*")!=0){
            printf("%s\n",linea);
            strcpy(v1.nombreCiudad,linea);
            if (existe_vertice(*G, v1))
                printf("Ese vertice ya esta en el grafo\n");
            else
                insertar_vertice(G, v1);

            fgets(linea,300,archivo);
            strip_line(linea);

        }
         do{
            fscanf(archivo," %[^=-]",v1.nombreCiudad);
            printf("%s\n",v1.nombreCiudad);
            fscanf(archivo," %c",&diferenciador);
            printf("%c\n",diferenciador);
            fscanf(archivo,"%[^;]",v2.nombreCiudad);
            printf("%s\n",v2.nombreCiudad);


            if(diferenciador=='='){// si es una autopista
                fscanf(archivo," %c",&desprecio);
                printf("%c\n",desprecio); //no queremos para nada el punto y coma
                fscanf(archivo," %[^\r\n]",valores);
                valorautopista = atof(valores);
                printf("%.2f\n",valorautopista);

                //Comprobacion de que el vertice se introdujo correctamente
                if (!existe_vertice(*G, v1)) {
                    printf("El vertice %s no existe en el grafo\n", v1.nombreCiudad);
                    return;
                }
                if (!existe_vertice(*G, v2)) {
                    printf("El vertice %s no existe en el grafo\n", v1.nombreCiudad);
                    return;
                }

                //si no hay distancia entre autopistas
                if (!distanciaAutopistas(*G, posicion(*G, v1), posicion(*G, v2))) {
                    if(valorautopista>0) {
                        InsertarArcoAutopista(G, posicion(*G, v1), posicion(*G, v2), valorautopista);
                    } else printf("VALOR INTRODUCIDO NO VALIDO, NO SE CREO EL ARCO AUTOPISTA\n");
                }

            }

            //si es carretera

            if(diferenciador=='-'){
                fscanf(archivo," %c",&desprecio);
                printf("%c\n",desprecio); //no queremos para nada el punto y coma
                fscanf(archivo," %[^\r\n]",valores);
                valorcarretera = atof(valores);
                printf("%.2f\n",valorcarretera);

                //Comprobacion de que el vertice se introdujo correctamente
                if (!existe_vertice(*G, v1)) {
                    printf("El vertice %s no existe en el grafo\n", v1.nombreCiudad);
                    return;
                }
                if (!existe_vertice(*G, v2)) {
                    printf("El vertice %s no existe en el grafo\n", v1.nombreCiudad);
                    return;
                }

                //si no hay distancia entre autopistas
                if (!distanciaCarreteras(*G, posicion(*G, v1), posicion(*G, v2))) {
                    if(valorcarretera>0) {
                        InsertarArcoCarretera(G, posicion(*G, v1), posicion(*G, v2), valorcarretera);
                    } else printf("VALOR INTRODUCIDO NO VALIDO, NO SE CREO EL ARCO AUTOPISTA\n");
                }

            }
            //MIENTRAS NO NOS ENCONTREMOS EN EL FINAL DEL ARCHIVO
        } while ((feof(archivo) == 0));

        fclose(archivo); //cerramos el archivo

    }


}
void strip_line ( char * linea ) {
    linea [ strcspn ( linea , "\r\n") ] = 0;
}


