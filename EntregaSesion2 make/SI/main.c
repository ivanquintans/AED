#include <stdlib.h>
#include <stdio.h>

#include "abin.h"
#include "recorridos.h"
#include "FuncionesExpresion.h"


int main(int argc, char** argv) { //SALE WARNING YA QUE ARGC Y ARGV NO SE USAN EN EL PROGRAMA

    abin Arbol;
    char *entrada;

    printf("Escribe la expresion aritmética infija: ");
    scanf(" %ms",&entrada);

    Arbol= arbolExpresion(entrada);
    printf("La expresion prefija correspondiente es:\n");
    preorden(Arbol);

    printf("\nLa expresion postfija correspondiente es:\n");
    postorden(Arbol);
    
    free(entrada);
    destruir(&Arbol);



}
