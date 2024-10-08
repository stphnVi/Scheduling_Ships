#include <stdlib.h>
#include "Node.h"

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