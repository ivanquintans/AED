cmake_minimum_required(VERSION 3.23)
project(HashRecolocacion)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(HashRecolocacion
        main.c
        pacientes_vacunodromo.txt
        tabla_hash_recolocacion.c
        tabla_hash_recolocacion.h)
