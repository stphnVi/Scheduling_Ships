#ifndef FLOW_H
#define FLOW_H

struct Canal setup(int length, char mode, short speed, short w, short time , int quantity);
void Equity(int W, char direction, struct BoatList *right, struct BoatList *left, struct NodeList *list);
void Tica( struct BoatList *right, struct BoatList *left, struct NodeList *list);


#endif //FLOW_H
