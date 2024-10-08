#include "NodeList.h"
#include <stdlib.h>
#include <string.h>
#include "Node.h"

// Función para inicializar una lista vacía
void initNodeList(struct NodeList* list, const char* name) {
    list->head = NULL;
    list->tail = NULL;
}

// Función para agregar un nodo al final de la lista
void appendNode(struct NodeList* list, struct Node* node) {
    node->next = NULL;
    node->prev = list->tail;

    if (list->tail != NULL) {
        list->tail->next = node;
    } else {
<<<<<<< HEAD
<<<<<<< Updated upstream
         list->head = &node;  // Si la lista estaba vacía
=======
<<<<<<< HEAD
        list->head = node;  // Si la lista estaba vacía
=======
        list->head = &node;  // Si la lista estaba vacía
>>>>>>> parent of 0fb0959 (Update the memory managment)
>>>>>>> Stashed changes
=======
        list->head = node;  // Si la lista estaba vacía
>>>>>>> parent of 2fb2a4c (Change the memory managment)
    }

    list->tail = node;
}