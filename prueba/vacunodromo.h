#include <stdio.h>
#include <stdlib.h>
#include "abb.h"
#include "cola.h"
#define MAX_LENGTH 100
#define MAX_LENGTH_LINE 500


typedef struct {
    char nombreVacuna[MAX_LENGTH];
    int numeroPacientes;
    TCOLA colapacientes;
}VACUNODROMO;



int base_de_datos(TABB *Arbol,char *nombrearchivo);
int gestion_vacunodromo(TABB *Arbol,VACUNODROMO *vacuna_administrar,char *nombrearchivo);
void anadir_paciente(TABB *Arbol);
void listadoPacientes(TABB Arbol);
void imprimir_paciente(TIPOELEMENTOABB mipaciente);
void imprimir_vacuna(TIPOELEMENTOABB mipaciente);
void inorden(TABB A);
void eliminar_paciente(TABB *arbol);
void _strip_line ( char * linea );
void cargar_archivo( char *nombrearchivo,TABB *Arbol);
void crear_vacunodromo(TABB arbol,VACUNODROMO *vacuna_administrar);
void actualizar_archivo(char *nombrearchivo,TABB Arbol);
void imprimir_paciente_archivo(TIPOELEMENTOABB mipaciente,FILE *archivo);
void imprimir_vacuna_archivo(TIPOELEMENTOABB mipaciente,FILE *archivo);
void preorden_archivo(TABB Arbol,FILE *archivo);
void inorden_comprobar(TABB A,VACUNODROMO *vacuna_administrar);
void vacunar(TABB *Arbol,VACUNODROMO *vacuna_administrar);



