// Boat.h

#ifndef BOAT_H
#define BOAT_H

#include "Node.h"

struct Boat{
    int id;
    int priority;
    int velocity;
    int type;
    char direction;
    int position;
};

short move_boat(struct Node* node, struct Boat* boat);
#endif // BOAT_H
