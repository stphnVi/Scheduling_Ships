#include <stdio.h>
#include <stdlib.h>
#include "BoatList.h"

struct BoatList* createBoatList() {
    struct BoatList* list = (struct BoatList*)malloc(sizeof(struct BoatList));
    if (list == NULL) {
        printf("Error al asignar memoria para la lista de barcos.\n");
        exit(1);
    }
    list->boats = (struct Boat*)malloc(MAX_BOATS * sizeof(struct Boat));
    if (list->boats == NULL) {
        printf("Error al asignar memoria para los barcos.\n");
        free(list);
        exit(1);
    }
    list->count = 0; 
    return list;
}

void initBoatList(struct BoatList* list) {
    for (int i = 0; i < MAX_BOATS; i++) {
        list->boats[i].priority = 0;
        list->boats[i].velocity = 0;
        list->boats[i].type = 0;
        list->boats[i].direction = 0;
        list->boats[i].position = 0;
    }
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

void destroyBoatList(struct BoatList* list) {
    if (list != NULL) {
        free(list->boats);
        free(list);
    }
}

