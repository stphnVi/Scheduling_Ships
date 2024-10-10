#ifndef NODELIST_H
#define NODELIST_H

#include "Node.h"

#define MAX_NODES 5

struct NodeList {
    struct Node* head;
    struct Node* tail;
};

struct Node* create_node(short id);
void initNodeList(struct NodeList* list);
void appendNode(struct NodeList* list, struct Node* node);

#endif //NODELIST_H
