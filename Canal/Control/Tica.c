#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../Structs/NodeList.h"
#include "Passage.h"
#include "../Structs/BoatList.h"
#include "../../CEThreads/CEThreads.c"

void Tica(struct BoatList *right, struct BoatList *left, int length) {

    int i = 1;
    struct NodeList list;
    initNodeList(&list);
    while (i < length + 1) {
        appendNode(&list, create_node(i));
        i++;
    }
    struct ThreadData *thread_data_list = (struct ThreadData*) malloc(MAX_BOATS * sizeof(struct ThreadData));
    int counterR = 0;
    int counterL = 0;

    if (right->boats[0].priority > left->boats[0].priority) {
       while (counterR < right->count) {
            if (list.head->available == 1) {
                    thread_data_list[a].boat = &right->boats[a];
                    thread_data_list[a].list = &list;
                    CEThread_create(&threads[a], thread_functionR, (void*)&thread_data_list[a]);
                    CEThread_run(&threads[a]);
                    counterR++;
            }
        }
        CEThread_join(&threads);
        while (counterL < left->count) {
            if (list.head->available == 1) {
                    thread_data_list[a].boat = &left->boats[a];
                    thread_data_list[a].list = &list;
                    CEThread_create(&threads[a], thread_functionL, (void*)&thread_data_list[a]);
                    CEThread_run(&threads[a]);
                    counterL ++;
            }
        }
    } else {
        while (counterL < left->count) {
                if (list.head->available == 1) {
                    thread_data_list[a].boat = &left->boats[a];
                    thread_data_list[a].list = &list;
                    CEThread_create(&threads[a], thread_functionL, (void*)&thread_data_list[a]);
                    CEThread_run(&threads[a]);
                counterL++;
                }
            }
        CEThread_join(&threads);
        while (counterR < right->count) {
            if (list.head->available == 1) {
                    thread_data_list[a].boat = &right->boats[a];
                    thread_data_list[a].list = &list;
                    CEThread_create(&threads[a], thread_functionR, (void*)&thread_data_list[a]);
                    CEThread_run(&threads[a]);
                    counterR++;
            }
        }
    }
    free(threads);
    free(thread_data_list);
}

