#ifndef NODELIST_H
#define NODELIST_H

struct NodeList {
    struct Node* head;
    struct Node* tail;
};

void appendNode(struct NodeList* list, struct Node* node);
void initNodeList(struct NodeList* list);
#endif //NODELIST_H
