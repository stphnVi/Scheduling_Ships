#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "Passage.h"
#include "Structs/BoatList.h"

void Tica(struct BoatList *right, struct BoatList *left, struct NodeList *list) {
    pthread_t threads[right->count];
    struct ThreadData thread_data[right->count];

    int thread_count = 0;

    if (right->boats[0].priority > left->boats[0].priority) {
        for (int i = 0; i < right->count && thread_count < right->count; i++) {
            thread_data[thread_count].boat = &right->boats[i];
            thread_data[thread_count].list = list;

            pthread_create(&threads[thread_count], NULL, thread_functionR, (void*) &thread_data[thread_count]);
            thread_count++;
        }

        // Esperar que todos los hilos terminen
        for (int i = 0; i < thread_count; i++) {
            pthread_join(threads[i], NULL);
        }

        for (int i = 0; i < left->count && thread_count < left->count; i++) {
            thread_data[thread_count].boat = &left->boats[i];
            thread_data[thread_count].list = list;

            pthread_create(&threads[thread_count], NULL, thread_functionL, (void*) &thread_data[thread_count]);
            thread_count++;
        }

    } else if (right->boats[0].priority < left->boats[0].priority) {
        for (int i = 0; i < left->count && thread_count < left->count; i++) {
            thread_data[thread_count].boat = &left->boats[i];  // Apunta al barco en la lista
            thread_data[thread_count].list = list;

            pthread_create(&threads[thread_count], NULL, thread_functionL, (void*) &thread_data[thread_count]);
            thread_count++;
        }

        // Esperar que todos los hilos terminen
        for (int i = 0; i < thread_count; i++) {
            pthread_join(threads[i], NULL);
        }

        for (int i = 0; i < right->count && thread_count < right->count; i++) {
            thread_data[thread_count].boat = &right->boats[i];  // Apunta al barco en la lista
            thread_data[thread_count].list = list;

            pthread_create(&threads[thread_count], NULL, thread_functionR, (void*) &thread_data[thread_count]);
            thread_count++;
        }

    } else {
        for (int i = 0; i < right->count && thread_count < right->count; i++) {
            thread_data[thread_count].boat = &right->boats[i];  // Apunta al barco en la lista
            thread_data[thread_count].list = list;

            pthread_create(&threads[thread_count], NULL, thread_functionR, (void*) &thread_data[thread_count]);
            thread_count++;
        }
        // Esperar que todos los hilos terminen
        for (int i = 0; i < thread_count; i++) {
            pthread_join(threads[i], NULL);
        }

        for (int i = 0; i < left->count && thread_count < left->count; i++) {
            thread_data[thread_count].boat = &left->boats[i];  // Apunta al barco en la lista
            thread_data[thread_count].list = list;

            pthread_create(&threads[thread_count], NULL, thread_functionL, (void*) &thread_data[thread_count]);
            thread_count++;
        }
    }

    // Esperar que todos los hilos terminen
    for (int i = 0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);
    }
}
