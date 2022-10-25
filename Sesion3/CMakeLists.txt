cmake_minimum_required(VERSION 3.23)
project(Sesion3 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Sesion3
        abb.c
        abb.h
        lista.c
        lista.h
        main.c
        vacunodromo.c
        vacunodromo.h
        cola.c
        cola.h)
