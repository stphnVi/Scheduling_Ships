#include <stdio.h>
#include <stdlib.h>
#include "Structs/Canal.h"
#include "Structs/BoatFactory.h"
#include "Structs/NodeFactory.h"
#include "Structs/Node.h"
#include "Structs/NodeList.h"
#include "Structs/Boat.h"
#include "Structs/BoatList.h"

void appendNode(struct NodeList * list, struct Node * id);

struct Canal setup(int length, char mode, short speed, short w, short time , int quantity) {
    struct Canal canal;
    canal.w = w;
    canal.time = time;
    canal.control = mode;

    short i = 1;
    int left = 0;
    int right = 0;

    struct NodeList node_list;
    while (i < length + 1) {
        appendNode(&node_list, create_node(i));
        i++;
    }
    struct BoatList west;
    while (left < quantity) {
        addBoatToList(&west, createBoat(COMMON,'L', speed));
        left++;
    }
    struct BoatList east;
    while (right < quantity) {
        addBoatToList(&east, createBoat(COMMON,'R', speed));
        right++;
    }

    canal.left = &west;
    canal.right = &east;
    canal.nodes = &node_list;

    return canal;
}
