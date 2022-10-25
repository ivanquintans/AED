cmake_minimum_required(VERSION 3.23)
project(Sesion4 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Sesion4
        funciones.c
        funciones.h
        grafo.c
        grafo.h
        main.c)
