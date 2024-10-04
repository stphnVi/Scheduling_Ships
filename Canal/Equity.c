#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "Passage.h"
#include "Structs/BoatList.h"

void Equity(int W, char direction, struct BoatList *right, struct BoatList *left, struct NodeList *list) {
    pthread_t *threads = malloc(W * sizeof(pthread_t));  // Arreglo de punteros a hilos
    struct ThreadData **thread_data = malloc(W * sizeof(struct ThreadData*));  // Arreglo de punteros a datos del hilo

    if(direction == 'R') {
        if (right != NULL) {
            for (int i = 0; i < W; i++) {
                thread_data[i] = (struct ThreadData*) malloc(sizeof(struct ThreadData));  // Asigna espacio para cada dato
                thread_data[i]->boat = getHead(right);
                thread_data[i]->list = list;                // Asigna el puntero a la lista de nodos

                // Crea los hilos que ejecutarán passageLR
                pthread_create(&threads[i], NULL, thread_function, (void*) thread_data[i]);
            }

            // Esperar a que todos los hilos terminen
            for (int i = 0; i < W; i++) {
                pthread_join(threads[i], NULL);
                free(thread_data[i]);  // Libera la memoria de los datos del hilo
            }
        } else {
            Equity(W, 'L', right, left, list);
        }
    } else if (direction == 'L') {
        if (left != NULL) {
            for (int i = 0; i < W; i++) {
                thread_data[i] = (struct ThreadData*) malloc(sizeof(struct ThreadData));  // Asigna espacio para cada dato
                thread_data[i]->boat = getHead(left);  // Asigna el puntero al barco
                thread_data[i]->list = list;               // Asigna el puntero a la lista de nodos

                // Crea los hilos que ejecutarán passageLR
                pthread_create(&threads[i], NULL, thread_function, (void*) thread_data[i]);
            }

            // Esperar a que todos los hilos terminen
            for (int i = 0; i < W; i++) {
                pthread_join(threads[i], NULL);
                free(thread_data[i]);  // Libera la memoria de los datos del hilo
            }
        } else {
            Equity(W, 'R', right, left, list);
        }
    }

    free(threads);  // Libera la memoria de los punteros a hilos
    free(thread_data);  // Libera la memoria de los punteros a datos de hilo
}