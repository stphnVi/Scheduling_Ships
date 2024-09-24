#include <stdio.h>
#include <stdlib.h>
#include "Boat_list.h"
#include "Boat.h"

// Initialize an empty list
void initBoatList(struct BoatList* list) {
    list->head = NULL;
    list->size = 0;
}

// Add a boat to the list
void addBoatToList(struct BoatList* list, struct boat boat) {
    struct BoatNode* newNode = (struct BoatNode*) malloc(sizeof(struct BoatNode));
    newNode->boat = boat;
    newNode->next = list->head;
    list->head = newNode;
    list->size++;
}

// Print all boats in the list
void printBoatList(struct BoatList* list) {
    struct BoatNode* current = list->head;
    while (current != NULL) {
        struct boat boat = current->boat;
        printf("Boat ID: %d, Type: %c, Direction: %c, Priority: %d, Velocity: %d\n",
               boat.id, boat.type[0], boat.direction[0], boat.priority, boat.velocity);
        current = current->next;
    }
}

// Free the list from memory
void freeBoatList(struct BoatList* list) {
    struct BoatNode* current = list->head;
    while (current != NULL) {
        struct BoatNode* temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
    list->size = 0;
}