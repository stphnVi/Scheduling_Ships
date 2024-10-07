#include <stdlib.h>
#include "Node.h"

struct Node create_node(short id) {
    struct Node node;

    node.id = id;
                      node.available = 1;
    node.next = NULL;
    node.prev = NULL;

    return node;
}