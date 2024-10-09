cmake_minimum_required(VERSION 3.10)
project(Scheduling_Ships)

set(CMAKE_C_STANDARD 11)

# Agrega aquí todos tus archivos fuente
set(SOURCES
        main.c
        Equity.c
        PassageLR.c
        PassageRL.c
        Structs/NodeList.c
        Structs/Boat.c
        Structs/BoatList.c
        Structs/BoatFactory.c
        ThreadsAdapter.c
        Setup.c
        Setup.c
        Control.h
        TIca.c
)

# Crear el ejecutable
add_executable(my_program ${SOURCES})

# Incluir directorios adicionales
include_directories(Structs)
