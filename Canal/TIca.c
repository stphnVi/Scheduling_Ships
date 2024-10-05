#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "Passage.h"
#include "Structs/BoatList.h"

void Tica( struct BoatList *right, struct BoatList *left, struct NodeList *list){

    pthread_t *threads = malloc( right->count * sizeof(pthread_t));
    struct ThreadData **thread_data = malloc(right->count * sizeof(struct ThreadData*));

    if (right->head->priority > left->head->priority) {
        for (int i = 0; i < right->count; i++) {
            thread_data[i] = (struct ThreadData*) malloc(sizeof(struct ThreadData));
            thread_data[i]->boat = getHead(right);
            thread_data[i]->list = list;
            deleteHead(right);

            pthread_create(&threads[i], NULL, thread_functionR, (void*) thread_data[i]);
        }
        for (int i = 0; i < left->count; i++) {
            thread_data[i] = (struct ThreadData*) malloc(sizeof(struct ThreadData));
            thread_data[i]->boat = getHead(left);
            thread_data[i]->list = list;
            deleteHead(left);

            pthread_create(&threads[i], NULL, thread_functionL, (void*) thread_data[i]);
        }
    }else if (right->head->priority < left->head->priority) {
        for (int i = 0; i < left->count; i++) {
            thread_data[i] = (struct ThreadData*) malloc(sizeof(struct ThreadData));
            thread_data[i]->boat = getHead(left);
            thread_data[i]->list = list;
            deleteHead(left);

            pthread_create(&threads[i], NULL, thread_functionL, (void*) thread_data[i]);
        }
        for (int i = 0; i < right->count; i++) {
            thread_data[i] = (struct ThreadData*) malloc(sizeof(struct ThreadData));
            thread_data[i]->boat = getHead(right);
            thread_data[i]->list = list;
            deleteHead(right);

            pthread_create(&threads[i], NULL, thread_functionR, (void*) thread_data[i]);
        }
    }else {
        for (int i = 0; i < right->count; i++) {
            thread_data[i] = (struct ThreadData*) malloc(sizeof(struct ThreadData));
            thread_data[i]->boat = getHead(right);
            thread_data[i]->list = list;
            deleteHead(right);

            pthread_create(&threads[i], NULL, thread_functionR, (void*) thread_data[i]);
        }
        for (int i = 0; i < left->count; i++) {
            thread_data[i] = (struct ThreadData*) malloc(sizeof(struct ThreadData));
            thread_data[i]->boat = getHead(left);
            thread_data[i]->list = list;
            deleteHead(left);

            pthread_create(&threads[i], NULL, thread_functionL, (void*) thread_data[i]);
        }
    }
    free(threads);
    free(thread_data);
}