cmake_minimum_required(VERSION 4.2)
project(OwnLanguage C)

set(CMAKE_C_STANDARD 23)

add_executable(OwnLanguage main.c programm.c console.c
        variablen.c
        variablen.h
        logik.c
        logik.h
        run.c
        run.h
        editor.c
        editor.h)
