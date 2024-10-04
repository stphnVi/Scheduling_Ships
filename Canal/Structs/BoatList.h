#ifndef BOAT_LIST_H
#define BOAT_LIST_H

#include "Boat.h"
struct BoatList {
    struct Boat* head; // Puntero al primer barco de la lista    int count; // Número de barcos en la lista
    int count;
};
void addBoatToList(struct BoatList* list, struct Boat boat);
struct Boat* getHead(struct BoatList* list);

#endif // BOAT_LIST_H