//
// Created by ivan on 1/10/22.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "abb.h"
#include "vacunodromo.h"



int main(int argc,char** argv) {
    char opcion;
    char *nombrearchivo;
    TABB Arbol; //creamos el arbol al iniciar el programa y lo borramos al salir del main
    VACUNODROMO vacuna_administrar;
    vacuna_administrar.numeroPacientes=0; //asignamos a cero
    strcpy(vacuna_administrar.nombreVacuna,"NULL");
    crearAbb(&Arbol); // lo creamos

    if (argc>2 && (strcmp(argv[1],"-f"))==0){ //si en el argv 1 hay un -f me lo abre si no no

        nombrearchivo =  argv[2];
       cargar_archivo(nombrearchivo,&Arbol);

    }else{ // si no pasan el comando con el barra f pues leemos de todas formas el archivo si lo pasan como ./ejecutable archivo_pacientes.txt
        nombrearchivo =argv[1];
        cargar_archivo(nombrearchivo,&Arbol);

    }

    do{
        printf("\nBienvenid@ al programa de gestion PacVac que desea:");
        printf("\nA. GESTION DE LA BASE DE DATOS");
        printf("\nB. GESTION DEL VACUNODROMO");
        printf("\nS. SALIR");
        printf("\nSelecciona una opcion: ");
        scanf( " %c",&opcion);

        switch (opcion) {
            case 'A':case 'a':
                printf("\n");
                base_de_datos(&Arbol,nombrearchivo); //al hacer cambios en la base de datos actualizamos el archivo.


                break;
            case 'B':case 'b':

                gestion_vacunodromo(&Arbol,&vacuna_administrar,nombrearchivo); //al vacunar tenemos que actualizar el archivo ya que varia

                break;

            case 's':case 'S':

                actualizar_archivo(nombrearchivo, Arbol); //actualizamos al salir

                destruirCola(&vacuna_administrar.colapacientes); //eliminamos la cola
                destruirAbb(&Arbol); //eliminamos el arbol

                printf("\nSaliendo del programa y liberando la memoria\n");
                printf("\nEl arbol ha sido eliminado\n\n");

                break;


            default:
                printf("Opcion incorrecta\n");

            }
        }while (opcion != 's' && opcion != 'S'); //mientras no sea una s repetimos
        return (EXIT_SUCCESS);
}

