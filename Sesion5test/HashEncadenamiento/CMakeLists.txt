cmake_minimum_required(VERSION 3.23)
project(HashEncadenamiento)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(HashEncadenamiento
        lista.c
        lista.h
        main.c
        pacientes_vacunodromo.txt
        tabla_hash_encadenamiento.c
        tabla_hash_encadenamiento.h)
