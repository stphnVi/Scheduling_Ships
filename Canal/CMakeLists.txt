cmake_minimum_required(VERSION 3.29)
project(Canal C)

set(CMAKE_C_STANDARD 11)

add_executable(Canal
        Structs/Boat.h
        Structs/BoatFactory.h
        Structs/BoatList.h
        Structs/BoatList.c
        Equity.c
        PassageRL.c
        Structs/Canal.c
        Structs/Canal.h
        Structs/Node.h
        Structs/NodeList.c
        Structs/NodeList.h
        Structs/Boat.c
        Setup.c
        Structs/NodeFactory.c
        Structs/NodeFactory.h
        Structs/BoatFactory.c
        PassageLR.c
        "Scheduling_Ships .c"
        "Threads Adapter.c"
        Passage.h
        TIca.c
        Flow.h)
