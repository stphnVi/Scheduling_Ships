cmake_minimum_required(VERSION 3.29)
project(Canal C)

set(CMAKE_C_STANDARD 11)

add_executable(Canal main.c
        Structs/Boat.h
        Structs/Canal.h
        Structs/BoatFactory.h
        Structs/Boat_list.h
        Structs/Boat_list.c)
