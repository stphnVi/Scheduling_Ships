#ifndef CANAL_H
#define CANAL_H

struct Canal {
    short size;
    short speed;
    char control[1];
    short time;
    short w;
    struct NodeList* list;
    struct BoatList* right;
    struct BoatList* left;
};
#endif