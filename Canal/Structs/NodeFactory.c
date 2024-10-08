#include <stdlib.h>
#include "Node.h"

struct Node* create_node(short id) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        return NULL;
    }

<<<<<<< HEAD
<<<<<<< Updated upstream
    node.id = id;
                      node.available = 1;
    node.next = NULL;
    node.prev = NULL;
=======
<<<<<<< HEAD
=======
>>>>>>> parent of 2fb2a4c (Change the memory managment)
    newNode->id = id;
    newNode->available = 1;
    newNode->next = NULL;
    newNode->prev = NULL;
<<<<<<< HEAD
=======
    node.id = id;
    node.available = 1;
    node.next = NULL;
    node.prev = NULL;
>>>>>>> parent of 0fb0959 (Update the memory managment)
>>>>>>> Stashed changes
=======
>>>>>>> parent of 2fb2a4c (Change the memory managment)

    return newNode;
}