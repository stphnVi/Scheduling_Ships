#ifndef CANAL_H
#define CANAL_H

struct Canal {
    char control;
    short time;
    short w;
    struct NodeList* nodes;
    struct BoatList* right;
    struct BoatList* left;
};
#endif