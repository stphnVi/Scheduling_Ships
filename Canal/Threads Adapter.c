#include <pthread.h>
#include "Passage.h"

void* thread_function(void* arg) {
    struct ThreadData* data = (struct ThreadData*) arg;
    passageLR(data->boat, data->list);
    pthread_exit(NULL);
}