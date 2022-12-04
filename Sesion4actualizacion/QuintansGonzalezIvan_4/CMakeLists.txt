cmake_minimum_required(VERSION 3.23)
project(QuintansGonzalezIvan_4 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(QuintansGonzalezIvan_4
        funciones.c
        funciones.h
        grafo.c
        grafo.h
        main.c)
