cmake_minimum_required(VERSION 3.23)
project(Prueba_buena)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Prueba_buena
        abb.c
        abb.h
        archivo_pacientes.txt
        cola.c
        cola.h
        lista.c
        lista.h
        main.c
        vacunodromo.c
        vacunodromo.h)
