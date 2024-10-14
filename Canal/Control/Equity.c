#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "Passage.h"
#include "../Structs/Boat.h"
#include "../Structs/Node.h"
#include "../Structs/NodeList.h"
#include "../Structs/BoatList.h"
#include "../../CEThreads/CEThreads.c"

void Equity(int W, struct BoatList *right, struct BoatList *left, int length) {

    int i = 1;
    struct NodeList list;
    initNodeList(&list);
    while (i < length + 1) {
        appendNode(&list, create_node(i));
        i++;
    }
    struct ThreadData *thread_data_list = (struct ThreadData*) malloc(MAX_BOATS * sizeof(struct ThreadData));

    while (right->count != 0 && left->count !=0) {
        if(i == 0){
            for (int a = 0; a <= W; a++) {
                if (list.tail->available == 1 & left->count !=0)  {
                    printf("Count of boats in west: %d\n", a);
                    thread_data_list[a].boat = &left->boats[a];
                    thread_data_list[a].list = &list;
                    CEThread_create(&threads[a], thread_functionL, (void*)&thread_data_list[a]);
                    CEThread_run(&threads[a]);
                    deleteHead(left);
                }
            }
            CEThread_join(&threads);
            i = 1;
        }else{
            for (int b = 0; b <= W; b++) {
                if (list.head->available == 1 & right->count != 0) {
                    printf("Count of boats in EAST: %d\n", b);
                    thread_data_list[b].boat = &right->boats[b];
                    thread_data_list[b].list = &list;
                    CEThread_create(&threads[b], thread_functionR, (void*)&thread_data_list[b]);
                    CEThread_run(&threads[b]);
                    deleteHead(right);
                }
                CEThread_join(&threads);
            }
            i = 0;
        }
    }
    free(threads);
    free(thread_data_list);
}