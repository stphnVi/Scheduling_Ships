#include <stdio.h>
#include <string.h>
#include "Boat.h"

typedef enum {
    COMMON,
    FAST,
    POLICE
} BoatType;

struct Boat createBoat(BoatType boatType, char direction, short velocity) {
    struct Boat boat1;
    boat1.direction[0] = direction;
    boat1.position = 0;

    switch (boatType) {
        case COMMON:
            boat1.priority = 1;
            boat1.velocity = velocity;
            boat1.type[0] = 'C';
            break;
        case FAST:
            boat1.priority = 5;
            boat1.velocity = velocity * 0.5;
            boat1.type[0] = 'F';
            break;
        case POLICE:
            boat1.priority = 10;
            boat1.velocity = velocity * 0.75;
            boat1.type[0] = 'P';
            break;
    }

    return boat1;
}

