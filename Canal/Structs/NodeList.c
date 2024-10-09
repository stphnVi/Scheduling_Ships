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
    if (currentIndex >= MAX_NODES) {
        return NULL;
    }

    struct Node* newNode = &nodePool[currentIndex];
    newNode->id = id;
    newNode->available = 1;
    newNode->next = NULL;
    newNode->prev = NULL;

    currentIndex++;
    return newNode;
}


void appendNode(struct NodeList* list, struct Node* node) {
    node->next = NULL;
    node->prev = list->tail;

    if (list->tail != NULL) {
        list->tail->next = node;
    } else {
        list->head = node;
    }

    list->tail = node;
}
