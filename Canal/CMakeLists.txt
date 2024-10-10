# Versión mínima requerida de CMake
cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(Scheduling_Ships)

# Establecer la versión del estándar de C
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Activar todas las advertencias importantes
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -g")

# Incluir directorio con headers
include_directories(./Structs)

# Archivos fuente
add_executable(Scheduling_Ships
    Canal.c
    Equity.c 
    main.c 
    PassageLR.c 
    PassageRL.c 
    Setup.c 
    ThreadsAdapter.c
    Tica.c
    BoatFactory.c 
    BoatList.c 
    NodeList.c 

)
