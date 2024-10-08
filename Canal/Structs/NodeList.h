#ifndef NODELIST_H
#define NODELIST_H

struct NodeList {
    struct Node* head;
    struct Node* tail;
};

void appendNode(struct NodeList* list, short id, short available);
#endif //NODELIST_H
