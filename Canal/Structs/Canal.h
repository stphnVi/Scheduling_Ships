#ifndef CANAL_H
#define CANAL_H

struct Canal {
    short size;
    char control[1];
    short time;
    struct NodeList* list;
};
#endif