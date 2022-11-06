#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "grafo.h"
#include "funciones.h"

#define VELOCIDAD_A 120
#define VELOCIDAD_C 70
#define PRECIO_A 0.07
#define PRECIO_C 0.01

double D[MAXVERTICES][MAXVERTICES];
struct tipo {
    int vprevio;
    char via;
};
struct tipo P[MAXVERTICES][MAXVERTICES];


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
                printf("\t-->%s (%.2f kms)\n", VECTOR[j].nombreCiudad,distanciaCarreteras(G, i, j));
            }
            //si son autopistas
            if (distanciaAutopistas(G, i, j)) {
                printf("\t==>%s (%.2f kms)\n", VECTOR[j].nombreCiudad,distanciaAutopistas(G, i, j));
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
            fscanf(archivo," %c",&diferenciador);
            fscanf(archivo,"%[^;]",v2.nombreCiudad);
             //no queremos para nada el punto y coma
             fscanf(archivo," %c",&desprecio);


            if(diferenciador=='='){// si es una autopista
                fscanf(archivo," %[^\r\n]",valores);
                valorautopista = atof(valores);

                //Comprobacion de que el vertice se introdujo correctamente
                if (!existe_vertice(*G, v1)) {
                    printf("El vertice %s no existe en el grafo\n", v1.nombreCiudad);
                    return;
                }
                if (!existe_vertice(*G, v2)) {
                    printf("El vertice %s no existe en el grafo\n", v2.nombreCiudad);
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
                fscanf(archivo," %[^\r\n]",valores);
                valorcarretera = atof(valores);

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

void actualizar_archivo(grafo G){

    FILE *archivo;
    tipovertice *VECTOR; //Para almacenar el vector de vértices del grafo
    int N; //número de vértices del grafo
    //Para recorrerla, simplemente vamos a recorrer la matriz de adyacencia
    N = num_vertices(G);
    VECTOR = array_vertices(G);
    if ((archivo = fopen("datos.txt", "w")) == NULL) { //COMPROBACION DE APERTURA
        printf("Error al abrir el archivo\n");

    }else{
        int i, j;
        for (i = 0; i < N; i++) {
            //Imprimo los vértices
            fprintf(archivo,"%s\n",VECTOR[i].nombreCiudad);
        }
        //separador de vertices a arcos
        fprintf(archivo,"*\n");
        //una vez impresos los vertices debemos imprimir los arcos asi que volvemos a hacer el bucle
        for (i = 0; i < N; i++) {
            //Chequeo sus arcos
            for (j = i; j < N; j++) {
                //si son carreteras
                if (distanciaCarreteras(G, i, j)) {
                    fprintf(archivo,"%s-%s;%.2f\n", VECTOR[i].nombreCiudad,VECTOR[j].nombreCiudad,distanciaCarreteras(G, i, j));
                }
                //si son autopistas
                if (distanciaAutopistas(G, i, j)) {
                    fprintf(archivo,"%s=%s;%.2f\n", VECTOR[i].nombreCiudad,VECTOR[j].nombreCiudad,distanciaAutopistas(G, i, j));
                }
            }
        }


    }

}
void inicializar_matrices(grafo G,int tipo){

    double factorA,factorC;

    switch (tipo) {
        case 0:
            //distnacia mas corta
            factorA=1;
            factorC=1;
            break;

        case 1:
            //menos velocidad
            //velocidad en autopista es 120km/h y en carretera es 70km/k
            factorA=1./VELOCIDAD_A;
            factorC=1./VELOCIDAD_C;

            break;

        case 2:
            //precio del kilometro recorrido en autopista y en carretera
            factorA=PRECIO_A;
            factorC=PRECIO_C;

            break;

    }
    int N = num_vertices(G);

    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            //SI I ES DISTINTO DE J
            if(i==j) {
                //SI SON IGUALES PONEMOS 0
                D[i][j] = 0;

                //INICIALIZAMOS LA MATRIZ P
                //0 EN CUALQUIER CASO EN EL QUE NO HAYA AUTOPISTA O CARRETERA
               P[i][j].vprevio=0;

            //SI ENCONTRAMOS ALGUNA DISTANCIA TANTO PARA CARRETERA COMO PARA AUTOPISTA
            }else if(factorA*distanciaAutopistas(G,i,j)!=0 || factorC*distanciaCarreteras(G,i,j)!=0) {

                //INICIALIZAMOS LA MATRIZ P
                //si existe carretera o autopista añadimos el vertice
                P[i][j].vprevio=i;

                //SI LA AUTOPISTA ES LA DISTANCIA MAS PEQUEÑA
                if (factorA*distanciaAutopistas(G, i, j) < factorC*distanciaCarreteras(G, i, j)) {
                    //SI LA DISTANCIA DE LA AUTOPISTA ES CERO METEMOS LA CARRETERA YA QUE LA CARRETERA ES LA MENOR DISTANCIA
                    if(factorA*distanciaAutopistas(G, i, j)==0) {
                        D[i][j] = factorC*distanciaCarreteras(G, i, j);
                        P[i][j].via='C';
                    //SI ES DISTINTA DE CERO AÑADIMOS LA AUTOPISTA
                    }else{
                        D[i][j] = factorA*distanciaAutopistas(G,i,j);
                        P[i][j].via='A';
                    }
                //MISMO CASO PERO EN ESTE CASO PARA LAS CARRETERAS
                } else {
                    if(factorC*distanciaCarreteras(G, i, j)==0) {
                        D[i][j] = factorA*distanciaAutopistas(G, i, j);
                        P[i][j].via='A';
                    }else{
                        D[i][j] = factorC*distanciaCarreteras(G,i,j);
                        P[i][j].via='C';
                    }
                }
            //SI NO SE CUMPLE NINGUNA DE LAS ANTERIORES CONDICIONES
            }else{
                //EN CUALQUIER OTRO CASO EL VALOR ES INFINITO
                D[i][j]=INFINITY;

                //INICIALIZAMOS LA MATRIZ P
                //0 EN CUALQUIER CASO EN EL QUE NO HAYA AUTOPISTA O CARRETERA
                P[i][j].vprevio=0;
            }
        }
    }
}
void algoritmo_Floyd_Warshall(grafo G,int tipo){

    tipovertice v1,v2;

    //INICIALIZAMOS LAS MATRICES
    inicializar_matrices(G,tipo);

    int N = num_vertices(G);

    for(int k=0;k<N;k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if(D[i][j]>D[i][k]+D[k][j]){
                    D[i][j]=D[i][k]+D[k][j];
                    P[i][j]=P[k][j];
                }
            }
        }
    }

    //solicitamos el camino que queremos recorrer
    printf("\nIntroduce vertice origen: ");
    scanf(" %[^\r\n]", v1.nombreCiudad);

    printf("Introduce vertice destino: ");
    scanf(" %[^\r\n]", v2.nombreCiudad);

    switch (tipo) {
        case 0:
            //En caso de distancia corta
            printf("\nA distancia total desde %s ata %s es de %.2f kms\n",v1.nombreCiudad,v2.nombreCiudad,D[posicion(G,v1)][posicion(G,v2)]);
            break;

        case 1:
            //En caso de tiempo
            printf("\nO tempo total desde %s ata %s es de %.2f horas\n",v1.nombreCiudad,v2.nombreCiudad,D[posicion(G,v1)][posicion(G,v2)]);
            break;

        case 2:
            //En caso de coste
            printf("\nO custe economico total desde %s ata %s es de %.2f €\n",v1.nombreCiudad,v2.nombreCiudad,D[posicion(G,v1)][posicion(G,v2)]);
            break;

    }


    //a la funcion imprimir camino le pasamos directamente la posicion del tipo vertice que tenemos

    imprimir_camino(posicion(G,v1), posicion(G,v2),G);


}

void imprimir_camino(int origen,int destino,grafo G){
    tipovertice *VECTOR; //Para almacenar el vector de vértices del grafo
    VECTOR= array_vertices(G);

    if(origen!=destino){
        //pasamos la funcion recursiva para que siga imprimiendo el camnino
        imprimir_camino(origen,P[origen][destino].vprevio,G);

        //ahora debemos comprobar si es carretera o autopista para saber si imprimimos ==> o -->
        //si ese vertice es una carretera
        if(P[origen][destino].via=='C'){
            printf("--> %s",VECTOR[destino].nombreCiudad);
        //si no si es una autopista
        }else if(P[origen][destino].via=='A'){
            printf("==> %s",VECTOR[destino].nombreCiudad);
        }
    //el origen es el destino
    }else{
        printf("\tRuta: %s",VECTOR[destino].nombreCiudad);

    }
}
void algoritmoPrim(grafo G){

    int N = num_vertices(G);
    int Selected[N];

    //inicializamos el conjunto de vertices
    for(int i=0;i<N;i++){
        Selected[i]=0;
    }
    int numarcos=0;
    double distanciaTotal=0;

    //inicializamos el algoritmo para el primer vertice
    Selected[0]=1;

    while(numarcos<N) {
        //inicializamos el minimo
        double minimo = INFINITY;
        int xv=0,vy=0;

        //Buscamos el arco  x-y con valor mínimo, con Selected(vx)=1, Selected(vy)=0
    }



}

void _printMatrix(double matrix [MAXVERTICES][MAXVERTICES], int V){
    int i,j;
    for(i=0;i<V;i++){
        for(j=0;j<V;j++){
            if (matrix[i][j]==INFINITY)
                printf("%10s","INF");
            else
                printf("%10.2f",matrix[i][j]);
        }
        printf("\n");
    }
}





