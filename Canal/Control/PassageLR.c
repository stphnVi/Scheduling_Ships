#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../Structs/Boat.h"
#include "../Structs/Node.h"
#include "../Structs/NodeList.h"

void passageLR(struct Boat *boat, struct NodeList *list) {
    struct Node* current = list->head;
    while (current != NULL) {
        short check_movement = move_boat(current, boat);
        if (check_movement == 1) {
            current->available = 1;
            current = current->prev;
            sleep(boat->velocity);
        }else {
            sleep(boat->velocity);
        }
    }
}
