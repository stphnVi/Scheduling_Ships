#include <stdlib.h>
#include "Node.h"

struct Node create_node(short id) {
    struct Node node;

<<<<<<< Updated upstream
    node.id = id;
                      node.available = 1;
    node.next = NULL;
    node.prev = NULL;
=======
<<<<<<< HEAD
    newNode->id = id;
    newNode->available = 1;
    newNode->next = NULL;
    newNode->prev = NULL;
=======
    node.id = id;
    node.available = 1;
    node.next = NULL;
    node.prev = NULL;
>>>>>>> parent of 0fb0959 (Update the memory managment)
>>>>>>> Stashed changes

    return node;
}