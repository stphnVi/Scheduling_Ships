#include <stdio.h>
#include <string.h>
#include "Boat.h"

typedef enum {
    COMMON,
    FAST,
    POLICE
} BoatType;

struct boat createBoat(BoatType boatType, char direction, short id) {
    struct boat boat1;
    boat1.id = id;
    boat1.direction[0] = direction;

    switch (boatType) {
        case COMMON:
            boat1.priority = 1;
            boat1.velocity = 10;
            boat1.type[0] = 'C';
            break;
        case FAST:
            boat1.priority = 1;
            boat1.velocity = 20;
            boat1.type[0] = 'F';
            break;
        case POLICE:
            boat1.priority = 10;
            boat1.velocity = 15;
            boat1.type[0] = 'P';
            break;
    }

    return boat1;
}

