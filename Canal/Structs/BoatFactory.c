#include "BoatFactory.h"
#include "Boat.h"

struct Boat createBoat(BoatType boatType, char direction, short velocity) {
    struct Boat boat1;
    boat1.direction = direction;
    boat1.position = 0;

    switch (boatType) {
        case COMMON:
            boat1.priority = 1;
        boat1.velocity = velocity;
        boat1.type = 'C';
        break;
        case FAST:
            boat1.priority = 5;
        boat1.velocity = velocity * 0.5;
        boat1.type = 'F';
        break;
        case POLICE:
            boat1.priority = 10;
        boat1.velocity = velocity * 0.75;
        boat1.type = 'P';
        break;
    }

    return boat1;
}