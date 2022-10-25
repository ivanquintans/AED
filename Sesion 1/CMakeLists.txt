cmake_minimum_required(VERSION 3.23)
project(Sesion_1 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Sesion_1
        abin.c
        abin.h
        cola.c
        cola.h
        funcionesArboles.c
        funcionesArboles.h
        main.c
        pila.c
        pila.h
        recorridos.c
        recorridos.h)
