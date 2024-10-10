#ifndef BOAT_LIST_H
#define BOAT_LIST_H

#include "Boat.h"

#define MAX_BOATS 9


struct BoatList {
    struct Boat boats[MAX_BOATS];
    int count;
};

void addBoatToList(struct BoatList* list, struct Boat boat);
struct Boat* getHead(struct BoatList* list);
void deleteHead(struct BoatList* list);
void initBoatList(struct BoatList* list);

#endif // BOAT_LIST_H