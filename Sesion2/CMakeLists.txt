cmake_minimum_required(VERSION 3.23)
project(Sesion2 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Sesion2
        abin.c
        abin.h
        FuncionesExpresion.c
        FuncionesExpresion.h
        pilaOperadores.c
        pilaOperadores.h
        pilaOperandos.c
        pilaOperandos.h
        recorridos.c
        recorridos.h)
