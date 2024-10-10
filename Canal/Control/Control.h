#ifndef CONTROL_H
#define CONTROL_H

#include "../Structs/NodeList.h"

void Tica(struct BoatList *right, struct BoatList *left, struct NodeList *list);
void Equity(int W, char direction, struct BoatList *right, struct BoatList *left, struct NodeList *list);

#endif
