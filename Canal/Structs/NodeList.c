#include "NodeList.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Node.h"

// Función para inicializar una lista vacía
void initNodeList(struct NodeList* list, const char* name) {
    list->head = NULL;
    list->tail = NULL;
}

// Función para agregar un nodo al final de la lista
void appendNode(struct NodeList* list, short id, short available) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->id = id;
    newNode->available = available;
    newNode->next = NULL;
    newNode->prev = list->tail;

    if (list->tail != NULL) {
        list->tail->next = newNode;
    } else {
        list->head = newNode;  // Si la lista estaba vacía
    }

    list->tail = newNode;
}