#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "../Structs/NodeList.h"
#include "Passage.h"
#include "../Structs/BoatList.h"

void Tica(struct BoatList *right, struct BoatList *left, int length) {

    int i = 1;
    struct NodeList list;
    initNodeList(&list);
    while (i < length + 1) {
        appendNode(&list, create_node(i));
        i++;
    }
    pthread_t *thread_list = (pthread_t*) malloc(MAX_BOATS * sizeof(pthread_t));
    struct ThreadData *thread_data_list = (struct ThreadData*) malloc(MAX_BOATS * sizeof(struct ThreadData));
    int counterR = 0;
    int counterL = 0;

    if (right->boats[0].priority > left->boats[0].priority) {
       while (counterR < right->count) {
            if (list.head->available == 1) {
                printf("Count of boats in EAST: %d\n", counterR);
                thread_data_list[counterR].boat = &right->boats[counterR];
                thread_data_list[counterR].list = &list;
                pthread_create(&thread_list[counterR], NULL, thread_functionR, (void*)&thread_data_list[counterR]);
                counterR++;
            }
        }
        for (int i = 0; i < right->count; i++) {
            pthread_join(thread_list[i], NULL);
        }
        while (counterL < left->count) {
            if (list.head->available == 1) {
                printf("Count of boats in west: %d\n", counterL);
                thread_data_list[counterL].boat = &left->boats[counterL];
                thread_data_list[counterL].list = &list;
                pthread_create(&thread_list[counterL], NULL, thread_functionL, (void*)&thread_data_list[counterL]);                counterL++;
            }
        }
    } else {
        while (counterL < left->count) {
                if (list.head->available == 1) {
                printf("Count of boats in west: %d\n", counterL);
                thread_data_list[counterL].boat = &left->boats[counterL];
                thread_data_list[counterL].list = &list;
                pthread_create(&thread_list[counterL], NULL, thread_functionL, (void*)&thread_data_list[counterL]);                
                counterL++;
                }
            }
        for (int i = 0; i < left->count; i++) {
            pthread_join(thread_list[i], NULL);
            }
        while (counterR < right->count) {
            if (list.head->available == 1) {
                printf("Count of boats in EAST: %d\n", counterR);
                thread_data_list[counterR].boat = &right->boats[counterR];
                thread_data_list[counterR].list = &list;
                pthread_create(&thread_list[counterR], NULL, thread_functionR, (void*)&thread_data_list[counterR]);
                counterR++;
            }
        }
    }
    free(thread_list);
    free(thread_data_list);
}

