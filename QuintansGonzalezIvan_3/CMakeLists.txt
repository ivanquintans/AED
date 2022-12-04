cmake_minimum_required(VERSION 3.23)
project(QuintansGonzalezIvan_3 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(QuintansGonzalezIvan_3
        abb.c
        abb.h
        cola.c
        cola.h
        lista.c
        lista.h
        main.c
        vacunodromo.c
        vacunodromo.h)
