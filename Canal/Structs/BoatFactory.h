#ifndef BOATFACTORY_H
#define BOATFACTORY_H

typedef enum {
    COMMON,
    FAST,
    POLICE
} BoatType;

struct Boat createBoat(BoatType boatType, char direction, short velocity);

#endif