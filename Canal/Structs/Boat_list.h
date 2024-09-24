#include "Boat.h"

#ifndef BOATLIST_H
#define BOATLIST_H

struct BoatNode {
    struct boat boat;
    struct BoatNode* next;
};

struct BoatList {
    struct BoatNode* head;
    int size;
};

// Function declarations
void initBoatList(struct BoatList* list);
void addBoatToList(struct BoatList* list, struct Boat boat);
void printBoatList(struct BoatList* list);
void freeBoatList(struct BoatList* list);

#endif // BOATLIST_H