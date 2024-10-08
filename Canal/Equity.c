#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "Passage.h"
#include "Structs/Boat.h"
#include "Structs/Node.h"
#include "Structs/NodeList.h"
#include "Structs/BoatList.h"

void Equity(int W, char direction, struct BoatList *right, struct BoatList *left, struct NodeList *list) {
    pthread_t *threads = malloc(W * sizeof(pthread_t));
    struct ThreadData **thread_data = malloc(W * sizeof(struct ThreadData*));

    if(direction == 'R') {
        if (right != NULL) {
            for (int i = 0; i < W; i++) {
                thread_data[i] = (struct ThreadData*) malloc(sizeof(struct ThreadData));
                thread_data[i]->boat = getHead(right);
                thread_data[i]->list = list;
                deleteHead(right);
                
                pthread_create(&threads[i], NULL, thread_functionR, (void*) thread_data[i]);
            }

            for (int i = 0; i < W; i++) {
                pthread_join(threads[i], NULL);
                free(thread_data[i]);
            }
        } else {
            Equity(W, 'L', right, left, list);
        }
    } else if (direction == 'L') {
        if (left != NULL) {
            for (int i = 0; i < W; i++) {
                thread_data[i] = (struct ThreadData*) malloc(sizeof(struct ThreadData));
                thread_data[i]->boat = getHead(left);
                thread_data[i]->list = list;
                deleteHead(left);

                pthread_create(&threads[i], NULL, thread_functionL, (void*) thread_data[i]);
            }
            for (int i = 0; i < W; i++) {
                pthread_join(threads[i], NULL);
                free(thread_data[i]);
            }
        } else {
            Equity(W, 'R', right, left, list);
        }
    }
    free(threads);
    free(thread_data);
}