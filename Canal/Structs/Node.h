#ifndef NODE_H
#define NODE_H

struct Node {
    short id;
    short available;
    struct Node* next;
    struct Node* prev;
};

#endif