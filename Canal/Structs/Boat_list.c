#include <stdio.h>
#include <stdlib.h>
#include "Boat_list.h"

void addBoatToList(struct BoatList* list, struct Boat boat) {
    struct Boat* newBoat = (struct Boat*)malloc(sizeof(struct Boat));
    if (newBoat == NULL) {
        // Manejo de error en caso de que no se pueda asignar memoria
        return;
    }
    *newBoat = boat; // Copia los datos del barco
    newBoat->next = NULL;

    if (list->head == NULL) {
        list->head = newBoat;
    } else {
        struct Boat* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newBoat;
    }
    list->count++;
}