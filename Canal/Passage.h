#ifndef PASSAGE_H
#define PASSAGE_H

struct ThreadData {
    struct Boat *boat;
    struct NodeList *list;
};

void passageLR(struct Boat *boat, struct NodeList *list);
void passageRL(struct Boat *boat, struct NodeList *list);
void* thread_function(void* arg);

#endif //PASSAGE_H
