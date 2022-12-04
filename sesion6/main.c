#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "funcionesBack.h"


int B[N][N]={{11,17,8},
             {9,7,6,},
             {13,15,16},};

int main(int argc,char **argv) {

    int solucion[N];
    int voa=0;
    int opcion;
    int usada[N];
    //inicializamos la solucion a -1

    for(int i=0;i<N;i++){
        solucion[i]=-1;
        usada[i]=0;
    }


    printf("Que algoritmo desea ejecutar??\n");
    printf("1.Backtracking\n");
    printf("2.Ramificacion y poda\n");
    printf("Opcion:");
    scanf("%d",&opcion);

    switch (opcion) {

        case 1:
            printf("\nVector usadas o no???\n");
            printf("1.Sin vector usadas\n");
            printf("2.Con vector usadas\n");
            printf("Opcion:");
            scanf("%d",&opcion);

            switch (opcion) {

                case 1:

                    Backtracking(solucion);
                    printf("=====SOLUCION=====");
                    printf("\nSolucion: ");
                    for (int i = 0; i < N; i++) {
                        printf("%d,", solucion[i]);
                        voa += B[i][solucion[i]];
                    }
                    printf(" Voa: %d\n", voa);
                    break;

                case 2:
                    //contamos el numero de veces que se ejecuta la funcion menos en el caso de criterio que contamos como pasos el numero de interacciones que realizan
                    BacktrackingUsadas(solucion,usada);
                    printf("=====SOLUCION=====");
                    printf("\nSolucion: ");
                    for (int i = 0; i < N; i++) {
                        printf("%d,", solucion[i]);
                        voa += B[i][solucion[i]];
                    }
                    printf(" Voa: %d\n", voa);



                    break;

                default:
                    break;
            }

            break;

        case 2:


            break;

    }


}

