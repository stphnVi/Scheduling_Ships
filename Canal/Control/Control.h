#ifndef CONTROL_H
#define CONTROL_H

#include "../Structs/NodeList.h"

void Tica(struct BoatList *right, struct BoatList *left, int length);
void Equity(int W, struct BoatList *right, struct BoatList *left, int length);
void TimedEquity(int T, struct BoatList *right, struct BoatList *left, int length);

#endif
