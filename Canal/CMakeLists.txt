cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(SchedulingShips)

# Establecer el estándar de C
set(CMAKE_C_STANDARD 99)

# Agregar todas las fuentes necesarias
set(SOURCES
    Equity.c
    PassageLR.c
    PassageRL.c
    Setup.c
    main.c
    Structs/NodeList.c
    Structs/Boat.c
    Structs/BoatList.c
    Structs/BoatFactory.c
    ThreadsAdapter.c
    Tica.c
    thread_functionR.c
    thread_functionL.c
)

# Incluir directorios de cabeceras si tienes un directorio para ello
include_directories(Structs)

# Crear el ejecutable
add_executable(Scheduling_Ships ${SOURCES})

