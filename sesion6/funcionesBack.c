//
// Created by ivan on 29/11/22.
//
#include "funcionesBack.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void Backtracking(int solucion[]){
    //inicializamos en primer lugar los contadores
    int contadorCriterio=0;
    int contadorGenerar=0;
    int contadorSolucion=0;
    int contadorMasHermanos=0;
    int contadorRetroceder=0;
    //nodo raiz
    int nodos=1;

    int nivel=0;
    int voa=INT_MIN;
    int soa[N];
    int bact=0;

    for(int i=0;i<N;i++){
        soa[i]=-1;
    }
    do{
        //printf("Iteraccion: %d Nivel:%d\n",contador,nivel);
        Generar(nivel,solucion,&bact,&contadorGenerar);
        if (Solucion(nivel,solucion,&contadorSolucion,&contadorCriterio) && bact>voa){
            voa=bact;
            //copiamos los valores de la solucion en soa
            for(int i=0;i<N;i++){
                soa[i]=solucion[i];
            }
        }

        if (Criterio(nivel,solucion,&contadorCriterio)){
            //debemos de contar el nodo de la raiz ya que de la forma en la que esta criterio implementada no lo cogemos
            //si tenemos una solucion diferente tenemos un nodo diferenteS
            nodos++;
            //si se cumple criterio y a mayores se cumple la condicion de nivel aumentamos ek nivel
            if(nivel<N-1){
                nivel++;
            }
        }
        while (!MasHermanos(nivel,solucion,&contadorMasHermanos) && nivel>=0){
            Retroceder(&nivel,solucion,&bact,&contadorRetroceder);
        }

    } while (nivel!=-1);

    for(int i=0;i<N;i++){
        //actualizamos la solucion para imprimirla
        solucion[i]=soa[i];
    }
    printf("\n=====PASOS=====\n");
    printf("Criterio= %d\n",contadorCriterio);
    printf("Generar= %d\n",contadorGenerar);
    printf("Solucion= %d\n",contadorSolucion);
    printf("MasHermanos= %d\n",contadorMasHermanos);
    printf("Retroceder= %d\n",contadorRetroceder);
    printf("\n=====NODOS=====\n");
    printf("Nodos= %d\n",nodos);
}


void BacktrackingUsadas(int solucion[],int usadas[]){

    //inicializamos en primer lugar los contadores
    int contadorCriterio=0;
    int contadorGenerar=0;
    int contadorSolucion=0;
    int contadorMasHermanos=0;
    int contadorRetroceder=0;
    //nodo raiz
    int nodos=1;

    int nivel=0;
    int voa=INT_MIN;
    int soa[N];
    int bact=0;
    int contador=1;

    for(int i=0;i<N;i++){
        soa[i]=-1;
    }

    do{
        GenerarUsadas(nivel,solucion,&bact,usadas,&contadorGenerar);
        if (Solucion(nivel,solucion,&contadorSolucion,&contadorCriterio) && bact>voa){
            voa=bact;
            //copiamos los valores de la solucion en soa
            for(int i=0;i<N;i++){
                soa[i]=solucion[i];
            }
        }

        if (CriterioUsadas(nivel,solucion,usadas,&contadorCriterio)){
            //debemos de contar el nodo de la raiz ya que de la forma en la que esta criterio implementada no lo cogemos
            //si tenemos una solucion diferente tenemos un nodo diferenteS
            nodos++;
            //si se cumple criterio y a mayores se cumple la condicion de nivel aumentamos ek nivel
            if(nivel<N-1){
                nivel++;
            }
        }
        while (!MasHermanos(nivel,solucion,&contadorMasHermanos) && nivel>=0){
            RetrocederUsadas(&nivel,solucion,&bact,usadas,&contadorRetroceder);
        }
        contador++;

    } while (nivel!=-1);

    for(int i=0;i<N;i++){
        //actualizamos la solucion para imprimirla
        solucion[i]=soa[i];
    }

    printf("\n=====PASOS=====\n");
    printf("Criterio= %d\n",contadorCriterio);
    printf("Generar= %d\n",contadorGenerar);
    printf("Solucion= %d\n",contadorSolucion);
    printf("MasHermanos= %d\n",contadorMasHermanos);
    printf("Retroceder= %d\n",contadorRetroceder);
    printf("\n=====NODOS=====\n");
    printf("Nodos= %d\n",nodos);

}

void Generar(int nivel, int solucion[],int *bact,int *contador){
    (*contador)++;
    solucion[nivel]= solucion[nivel]+1;
    if(solucion[nivel]==0) *bact += B[nivel][solucion[nivel]];
    //restamos la tarea que asignamos anteriormente
    else *bact+= B[nivel][solucion[nivel]]-B[nivel][solucion[nivel]-1];
}
int Solucion(int nivel, int solucion[],int *contador,int *contadorCriterio){
    (*contador)++;
    return (nivel==N-1 && Criterio(nivel,solucion,contadorCriterio));
}

int Criterio(int nivel, const int solucion[],int *contador){

    for(int i=0;i<nivel;i++){
        (*contador)++;
        if(solucion[nivel]==solucion[i]) return 0;
    }
    return 1;
}

int MasHermanos(int nivel, const int solucion[],int *contador){
    (*contador)++;
    return solucion[nivel]<N-1;
}

void Retroceder(int *nivel, int solucion[],int *bact,int *contador){
    (*contador)++;
    *bact-=B[*nivel][solucion[*nivel]];
    solucion[*nivel]=-1;
    (*nivel)--;
}

void RetrocederUsadas(int *nivel, int solucion[],int *bact,int usadas[],int *contador){
    (*contador)++;
    *bact-=B[*nivel][solucion[*nivel]];
    usadas[solucion[*nivel]]--;
    solucion[*nivel]=-1;
    (*nivel)--;
}

int CriterioUsadas(int nivel, const int solucion[],int usadas [],int *contador){
    //con usadas nos olvidamos de las interacciones
    (*contador)++;
    return usadas[solucion[nivel]]==1;
}

void GenerarUsadas(int nivel, int solucion[],int * bact,int usadas[],int *contador){
    (*contador)++;
    if (solucion[nivel]!=-1){
        usadas[solucion[nivel]]--;
    }
    solucion[nivel]= solucion[nivel]+1;
    usadas[solucion[nivel]]++;
    if(solucion[nivel]==0) *bact += B[nivel][solucion[nivel]];
        //restamos la tarea que asignamos anteriormente
    else *bact+= B[nivel][solucion[nivel]]-B[nivel][solucion[nivel]-1];
}





