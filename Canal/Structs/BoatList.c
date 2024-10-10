#include <stdio.h>
#include <stdlib.h>
#include "BoatList.h"

void initBoatList(struct BoatList* list) {
    list->count = 0;
}

void addBoatToList(struct BoatList* list, struct Boat boat) {
    if (list->count >= MAX_BOATS) {
        printf("La lista de barcos está llena. No se pueden agregar más barcos.\n");
        return;
    }

    list->boats[list->count] = boat;

    list->count++;

}


struct Boat* getHead(struct BoatList* list) {
    if (list == NULL || list->count == 0) {
        return NULL;
    }
    return &list->boats[0];
}
void deleteHead(struct BoatList* list) {
    if (list == NULL || list->count == 0) {
        return;
    }

    for (int i = 0; i < list->count - 1; i++) {
        list->boats[i] = list->boats[i + 1];
    }

    list->count--;
}
