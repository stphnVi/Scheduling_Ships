// Boat.h

#ifndef BOAT_H
#define BOAT_H

struct Boat{
    short priority;
    short velocity;
    char type[1];
    char direction[1];
    short position;
    struct Boat* next;
};

short move_boat(struct Node* node, struct Boat* boat);
#endif // BOAT_H
