#include "Node.h"
#include "Boat.h"

short move_boat(struct Node* node, struct Boat* boat) {
    if (node->available == 1) {
        boat->position = node->id;
        node->available = 0;
        return 1;
    }else {
        return 0;
    }
}
