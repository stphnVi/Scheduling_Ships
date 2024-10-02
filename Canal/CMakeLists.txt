cmake_minimum_required(VERSION 3.29)
project(Canal C)

set(CMAKE_C_STANDARD 11)

add_executable(Canal
        Structs/Boat.h
        Structs/BoatFactory.h
        Structs/Boat_list.h
        Structs/Boat_list.c
        Equity.c
        Passage.c
        Structs/Canal.c
        Structs/Canal.h
        Structs/Node.h
        Structs/NodeList.c
        Structs/NodeList.h
        Structs/Boat.c
        Setup.c)
