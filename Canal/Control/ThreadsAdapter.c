#include "Passage.h"

void* thread_functionL(void* arg) {
    struct ThreadData* data = (struct ThreadData*) arg;
    passageLR(data->boat, data->list);
}

void* thread_functionR(void* arg) {
    struct ThreadData* data = (struct ThreadData*) arg;
    passageRL(data->boat, data->list);
}