// Boat.h

#ifndef BOAT_H
#define BOAT_H

#include "Node.h"

struct Boat{
    short priority;
    short velocity;
    char type;
    char direction;
    short position;
};

short move_boat(struct Node* node, struct Boat* boat);
#endif // BOAT_H
