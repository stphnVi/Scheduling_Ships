#include "NodeList.h"
#include <stdlib.h>
#include <string.h>
#include "Node.h"

struct Node nodePool[MAX_NODES];
int currentIndex = 0;

void initNodeList(struct NodeList* list) {
    list->head = NULL;
    list->tail = NULL;
}

struct Node* create_node(short id) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        return NULL;
    }

    newNode->id = id;
    newNode->available = 1;
    newNode->next = NULL;
    newNode->prev = NULL;

    return newNode;
}

void appendNode(struct NodeList* list, struct Node* node) {
    if (list == NULL || node == NULL) {
        printf("Error: la lista o el nodo es NULL.\n");
        return;
    }

    node->next = NULL; 
    node->prev = list->tail; 

    if (list->tail != NULL) {
        list->tail->next = node;
    } else {

        list->head = node;
    }

    list->tail = node;
}


void freeNodeList(struct NodeList* list) {
    struct Node* current = list->head;
    struct Node* next;

    while (current != NULL) {
        next = current->next;
        free(current); 
        current = next;
    }

    list->head = NULL;
    list->tail = NULL;
}
