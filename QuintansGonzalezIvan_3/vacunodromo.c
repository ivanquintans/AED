
#include "vacunodromo.h"
#include <string.h>


void anadir_paciente(TABB *Arbol) {

    TIPOELEMENTOABB mipaciente; // creamos el tipoelemento abb
    TIPOELEMENTOLISTA vacunas; // creamos la lista de vacunas del paciente que se encuentra en la estructura tipoelementoabb

    printf("\nNombre del paciente: ");
    scanf(" %[^\r\n]", mipaciente.ApellidosNombre); //pedimos el nombre de nuestro paciente a añadir

    if(esMiembroAbb(*Arbol,mipaciente)){

        printf("\nEl paciente ya está inscrito\n\n");
        return;

    }else{
        crearLista(&mipaciente.listavacunas); //creamos la lista de vacunas asociada a mi paciente
        do {
            printf(" Nombre vacuna (fin para finalizar) : ");
            scanf(" %[^\r\n]", vacunas.nombreVacuna);

            vacunas.mindosis=0; //ponemos el minimo de vacunas a cero

            if (strcmp(vacunas.nombreVacuna, "fin")) { //  mientras sean distintas, me entra ya que si son iguales devuelve 0 y no entraria

                do{
                    printf(" Número de dosis máximas: ");
                    scanf("%d", &vacunas.maxdosis); //añadimos el numero de dosis máximas

                }while(vacunas.maxdosis<0);

                insertarElementoLista(&mipaciente.listavacunas, finLista(mipaciente.listavacunas), vacunas); // insertamos las vacunas a la lista del paciente


            }


        } while (strcmp(vacunas.nombreVacuna, "fin"));

        if (!esListaVacia(mipaciente.listavacunas)) {// si la lista es vacia no la añadimos al arbol ya que no tiene elementos

            insertarElementoAbb(Arbol,mipaciente);

        }


        printf("\n");

    }


}
void listadoPacientes(TABB Arbol){


    if(!esAbbVacio(Arbol)){ //comprobamos si el arbol es vacio o no

        inorden(Arbol); //imprimimos en orden alfabético

    } else printf("\nNo hay pacientes que imprimir");

    printf("\n\n");

}
void imprimir_paciente(TIPOELEMENTOABB mipaciente){

    printf("\n%s",mipaciente.ApellidosNombre); //nombre del paciente actual
    imprimir_vacuna(mipaciente);

}
void imprimir_vacuna(TIPOELEMENTOABB mipaciente){

    TPOSICION p;
    TIPOELEMENTOLISTA vacunas;

    p= primeroLista(mipaciente.listavacunas); // p

    for (int i=0;i< longitudLista(mipaciente.listavacunas);i++) { //bucle iterando por la lista de vacuna
        recuperarElementoLista(mipaciente.listavacunas, p, &vacunas); // recuperamos las vacunas de esa posición
        printf("\n\tVacuna: %10s \t\tDosis %d de %d", vacunas.nombreVacuna, vacunas.mindosis, vacunas.maxdosis); //imprimimos
        p=siguienteLista(mipaciente.listavacunas,p); //p+1
    }
    printf("\n");
}
void inorden(TABB A){
    TIPOELEMENTOABB E;
    if(!esAbbVacio(A)){
        inorden(izqAbb(A));
        leerElementoAbb(A,&E);
        imprimir_paciente(E);
        inorden(derAbb(A));
    }
}
void eliminar_paciente(TABB *Arbol){

    TIPOELEMENTOABB mipaciente;
    TIPOCLAVE nombre;


    printf("\nNombre del paciente: ");
    scanf(" %m[^\r\n]", &nombre); //como tipo clave es un char puntero con el m reservamos memoria

    buscarNodoAbb(*Arbol,nombre,&mipaciente); // buscamos el nodo

    if(esMiembroAbb(*Arbol,mipaciente)){ //si es miembro


        suprimirElementoAbb(Arbol,mipaciente); //suprimimos el elemento

        printf("\nSe ha realizado la baja con exito\n\n");

    }else printf("\nEl elemento no está en la base de datos\n\n");

	free(nombre);

}

void cargar_archivo( char *nombrearchivo,TABB *Arbol) {

    FILE * archivo;
    char linea[MAX_LENGTH_LINE];
    char * nombre_paciente;
    char * vacuna;
    char * dosis_maximas;
    char * dosis_minimas;

    TIPOELEMENTOABB mipaciente;
    TIPOELEMENTOLISTA vacunas;

    //printf("%s\n",nombrearchivo); ///COMPROBAMOS QUE PILLO POR COMANDOS SOBRE EL ARCHIVO

    if((archivo = fopen(nombrearchivo, "r")) == NULL){ //COMPROBACION DE APERTURA
        printf("Error al abrir el archivo\n");

    }else { //SI ES CORRECTA

        while (feof(archivo) == 0) { //MIENTRAS NO NOS ENCONTREMOS EN EL FINAL DEL ARCHIVO
            fgets(linea, MAX_LENGTH_LINE, archivo);
            //printf("%s\n",linea);
            _strip_line(linea); //FUNCIÓN PARA PILLAR LA LINEA CORRECTAMENTE (RETORNO DE CARRO)



            nombre_paciente =strtok(linea, "|"); //PILLAMOS LO QUE SE ENCUENTRE HASTA EL DELIMITADOR |
            strcpy(mipaciente.ApellidosNombre, nombre_paciente);//COPIAMOS LO QUE PILLA DEL DOCUMENTO EN EL NOMBRE DEL PACIENTE

            crearLista(&mipaciente.listavacunas); //creamos la lista del paciente

            do { //MIENTRAS LA VACUNA SEA DISTINA DE NULL

                vacuna = strtok(NULL, " ; "); //PILLAMOS LO QUE SE ENCUENTRA ANTES DEL ;

                if (vacuna != NULL) {

                    strcpy(vacunas.nombreVacuna, vacuna); //COPIAMOS EL NOMBRE DE LA VACUNA EN NUESTRA VARIABLE

                    dosis_minimas = strtok(NULL, " ; "); //PILLAMOS LAS VACUNAS ADMINISTRADAS
                    vacunas.mindosis = atoi(dosis_minimas);

                    dosis_maximas= strtok(NULL, " ; "); //PILLAMOS LAS VACUNAS MÁXIMAS
                    vacunas.maxdosis = atoi(dosis_maximas);

                    insertarElementoLista(&mipaciente.listavacunas, finLista(mipaciente.listavacunas), vacunas); ///añadimos los vacunas
                }

            }while (vacuna != NULL);

            if (!esListaVacia(mipaciente.listavacunas)) {// si la lista es vacia no añadimos el elemento a la cola ya que no tiene vacunas

                insertarElementoAbb(Arbol, mipaciente); //AÑADIMOS AL ARBOL EL PACIENTE
            }


        }
        //destruimos la lista
        destruirLista(&mipaciente.listavacunas);
        fclose(archivo); //cerramos el archivo


    }


}
void _strip_line ( char * linea ) {
    linea [ strcspn ( linea , "\r\n") ] = 0;
}
int base_de_datos(TABB *Arbol,char  *nombrearchivo){
    char opcion;

    do{
        printf("Bienvenid@ al programa de gestion PacVac");
        printf("\nA. Añadir paciente");
        printf("\nL. Listado alfabético de pacientes");
        printf("\nE. Eliminar paciente"); //añadimos al main las consultas deseadas
        printf("\nS. Salir");
        printf("\nSelecciona una opcion: ");
        scanf( " %c",&opcion);

        switch (opcion) {
            case 'A': case 'a':

                anadir_paciente(Arbol);


                break;
            case 'L': case 'l':

                listadoPacientes(*Arbol);


                break;

            case 'E':case 'e':

                eliminar_paciente(Arbol);



                break;

            case 'S':case 's':

                break;


            default: printf("Opcion incorrecta\n");

        }

        //la base de datos tiene que estra siemre actualizada por lo que hay que actualizar en cada operacion necesaria
        actualizar_archivo(nombrearchivo,*Arbol);
    } while (opcion != 's' && opcion != 'S');

    return (EXIT_SUCCESS);
}
int gestion_vacunodromo(TABB *Arbol,VACUNODROMO *vacunodromo,char *nombrearchivo){
    char opcion;

    do{
        printf("\nBienvenid@ al programa de gestion PacVac que desea:");
        printf("\nC. Crear cola de vacunacion");
        printf("\nV. Vacunar");
        printf("\nS. Salir");
        printf("\nSelecciona una opcion: ");
        scanf( " %c",&opcion);

        switch (opcion) {

            case 'C': case 'c':

                crear_vacunodromo(*Arbol,vacunodromo); //creamos la cola


                break;
            case 'V': case 'v':

                vacunar(Arbol,vacunodromo); //vacunamos

                actualizar_archivo(nombrearchivo,*Arbol); //actualizamos las dosis en el archivo



                break;

            case 's': case 'S':

                break;


            default: printf("Opcion incorrecta\n");

        }
    } while (opcion != 's' && opcion != 'S'); //mientras no sea una c o una v repetimos
    return (EXIT_SUCCESS);
}
void crear_vacunodromo(TABB Arbol,VACUNODROMO *vacuna_administrar){

	if(strcmp(vacuna_administrar->nombreVacuna,"NULL")!=0){ //si completamos la vacunacion de una vacuna tenemos que eliminar tambien
		destruirCola(&vacuna_administrar->colapacientes); //borramos la otra cola

	}

    if(vacuna_administrar->numeroPacientes==0){ //si los pacientes son iguales a cero

        crearCola(&vacuna_administrar->colapacientes); //creamos la nueva cola
        vacuna_administrar->numeroPacientes=0; //asignamos a cero

    }

    if(!esColaVacia(vacuna_administrar->colapacientes)){ // si ya hay una cola y queremos sobrescribir
        destruirCola(&vacuna_administrar->colapacientes); //borramos la otra cola

    }



    printf("\nNombre de la vacuna que se quiere administrar : ");
    scanf(" %[^\r\n]", vacuna_administrar->nombreVacuna); // pedimos el nombre de la vacuna

    inorden_comprobar(Arbol,vacuna_administrar); // recorremos comprobando si

    if(esColaVacia(vacuna_administrar->colapacientes)){ // si no hay ningun paciente con la vacuna

        destruirCola(&vacuna_administrar->colapacientes); //SI NO SE ASIGNO NINGUN ELEMENTO A LA COLA ELIMINAMOS LA COLA
        strcpy(vacuna_administrar->nombreVacuna,"NULL"); //lo declaro como vacio para poder comprobar si la cola esta creado o no

    }

}

void inorden_comprobar(TABB Arbol,VACUNODROMO *vacuna_administrar){

    TIPOELEMENTOABB mipaciente;
    TIPOELEMENTOLISTA vacunas;
    TPOSICION p;

    if(!esAbbVacio(Arbol)){


        inorden_comprobar(izqAbb(Arbol), vacuna_administrar);
        leerElementoAbb(Arbol,&mipaciente);

        p= primeroLista(mipaciente.listavacunas);


        for(int i=0;i<longitudLista(mipaciente.listavacunas);i++){

            recuperarElementoLista(mipaciente.listavacunas,p,&vacunas); //RECUPERAMOS LA LISTA DE VACUNAS DEL PACIENTE

            if(strcmp(vacunas.nombreVacuna,vacuna_administrar->nombreVacuna)==0) {

                if (vacunas.mindosis < vacunas.maxdosis) { ///si el paciente tiene la vacuna y le falta alguna dosis por administrar

                    anadirElementoCola(&vacuna_administrar->colapacientes,mipaciente);// AÑADIMOS LOS PACIENTES CON ESA VACUNA A UNA COLA DE VACUNACIÓN
                    vacuna_administrar->numeroPacientes += 1; //AUMENTAMOS EL NUMERO DE PACIENTES

                }
            }

            p= siguienteLista(mipaciente.listavacunas,p);

        }

        inorden_comprobar(derAbb(Arbol),vacuna_administrar);
    }


}


void actualizar_archivo(char *nombrearchivo,TABB Arbol){

    FILE * archivo;

    if((archivo = fopen(nombrearchivo, "w")) == NULL){ //abrimos el archvo si hay en modo escritura
        printf("Error al abrir el archivo\n\n");
        return ; //si no abre el archivo salimos

    }else {
        preorden_archivo(Arbol,archivo);
        fclose(archivo); //cerramos el archivo una vez realizada la actualización
    }
    
    return ;

}

 void  preorden_archivo(TABB Arbol,FILE *archivo){

     //hacemos preorden porque si no el arbol se nos imprimiria como una lista ordenada.

    TIPOELEMENTOABB mipaciente;
    if(!esAbbVacio(Arbol)){

        leerElementoAbb(Arbol,&mipaciente); //leemos el elemento

        imprimir_paciente_archivo(mipaciente,archivo); //imprimimos el paciente en el archivo

        preorden_archivo(izqAbb(Arbol),archivo); //realizamos el preorden a la derecha y luego a la izquierda.
        preorden_archivo(derAbb(Arbol),archivo);

    }
}
void imprimir_paciente_archivo(TIPOELEMENTOABB mipaciente,FILE *archivo){

    fprintf(archivo,"%s|",mipaciente.ApellidosNombre); //imprimo el nombre del paciente actual
    imprimir_vacuna_archivo(mipaciente,archivo);

}
void imprimir_vacuna_archivo(TIPOELEMENTOABB mipaciente,FILE *archivo){

    TPOSICION p;
    TIPOELEMENTOLISTA vacunas;

    p= primeroLista(mipaciente.listavacunas); // p

    for (int i=0;i< longitudLista(mipaciente.listavacunas);i++) { //bucle iterando por la lista de vacuna
        recuperarElementoLista(mipaciente.listavacunas, p, &vacunas); // recuperamos las vacunas de esa posición
        fprintf(archivo,"%s;%d;%d;", vacunas.nombreVacuna, vacunas.mindosis, vacunas.maxdosis); //imprimimos

        p=siguienteLista(mipaciente.listavacunas,p); //siguiente elemento de la lista de vacunas
    }
    fprintf(archivo,"\n"); //Cuando todas las vacunas esten puestas realizamos salto de linea para escribir el nuevo paciente en otra linea
}
void vacunar(TABB *Arbol,VACUNODROMO *vacuna_administrar) {

    TIPOELEMENTOABB mipaciente;
    TPOSICION p;
    TIPOELEMENTOLISTA vacunas;

    if (strcmp(vacuna_administrar->nombreVacuna,"NULL")==0){ //si el nombre de la vacuna es null no vacunamos

        printf("\nNO SE PUEDE VACUNAR YA QUE NO EXISTEN VACUNAS CON ESE NOMBRE\n");
        printf("NO EXISTE COLA\n");


    }else{

        consultarPrimerElementoCola(vacuna_administrar->colapacientes, &mipaciente); //consultamos el primer paciente

        if (!esColaVacia(vacuna_administrar->colapacientes)) { //controlemos que la cola no sea vacia

            p = primeroLista(mipaciente.listavacunas);

            for (int i = 0; i < longitudLista(mipaciente.listavacunas); i++) { //iteramos por todas sus vacunas

                recuperarElementoLista(mipaciente.listavacunas, p, &vacunas); //recuperamos la vacuna

                if (strcmp(vacuna_administrar->nombreVacuna, vacunas.nombreVacuna) == 0) {

                    vacunas.mindosis += 1; //aumentamos en uno la vacuna que se administra en esa cola

                    if (vacunas.mindosis ==vacunas.maxdosis) { // controlamos si las vacunas administradas son iguales a las totales

                        printf("\nVacunando a %s con %s , dosis máximas administradas", mipaciente.ApellidosNombre,vacunas.nombreVacuna);
                        printf("\nELiminando a %s de la cola de vacunacion de %s\n", mipaciente.ApellidosNombre,vacunas.nombreVacuna);

                        suprimirElementoLista(&mipaciente.listavacunas,p); // si las dosis son iguales a las vacunas máximas suprimimos esta vacuna
                        suprimirElementoCola(&vacuna_administrar->colapacientes); //eliminamos de la cola al paciente ya que no tiene mas dosis que administar
                        vacuna_administrar->numeroPacientes--; //disminuimos el numero de pacientes ya que este paciente fue eliminado

                    } else {
                        modificarElementoLista(&mipaciente.listavacunas, p, vacunas); //SI NO MODIFICAMOS EL ELEMENTO
                        printf("\n      Vacunando a %s con %s", mipaciente.ApellidosNombre, vacunas.nombreVacuna);

                        anadirElementoCola(&vacuna_administrar->colapacientes,mipaciente); //añadimos el primer elemento al final ya que ya vacunamos
                        suprimirElementoCola(&vacuna_administrar->colapacientes); //destruimos el primer paciente ya que es el mismo que el primero


                        printf("\n\n");
                    }
                    break; //si encontramos salimos
                }
                p = siguienteLista(mipaciente.listavacunas, p); //p+1
            }
        }
        if (esListaVacia(mipaciente.listavacunas)) { //si el paciente no tiene mas listas de vacunas le eliminamos del arbol

            suprimirElementoAbb(Arbol, mipaciente); //suprimimos el elemento

            printf("\n\t\tEl paciente fue vacunado con éxito, eliminando al paciente del arbol\n\n");


        }
    }
}








