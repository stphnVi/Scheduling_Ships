#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "Passage.h"
#include "../Structs/Boat.h"
#include "../Structs/Node.h"
#include "../Structs/NodeList.h"
#include "../Structs/BoatList.h"

void Equity(int W, struct BoatList *right, struct BoatList *left, int length) {

    int i = 1;
    struct NodeList list;
    initNodeList(&list);
    while (i < length + 1) {
        appendNode(&list, create_node(i));
        i++;
    }

    pthread_t *thread_list = (pthread_t*) malloc(MAX_BOATS * sizeof(pthread_t));
    struct ThreadData *thread_data_list = (struct ThreadData*) malloc(MAX_BOATS * sizeof(struct ThreadData));

    while (right->count != 0 && left->count !=0) {
        if(i == 0){
            for (int a = 0; a <= W; a++) {
                if (list.tail->available == 1 & left->count !=0)  {
                    printf("Count of boats in west: %d\n", a);
                    thread_data_list[0].boat = &left->boats[0];
                    thread_data_list[0].list = &list;
                    pthread_create(&thread_list[0], NULL, thread_functionL, (void*)&thread_data_list[0]);
                    deleteHead(left);
                }
            }
            i = 1;
        }else{
            for (int b = 0; b <= W; b++) {
                if (list.head->available == 1 & right->count != 0) {
                    printf("Count of boats in EAST: %d\n", b);
                    thread_data_list[0].boat = &right->boats[0];
                    thread_data_list[0].list = &list;
                    pthread_create(&thread_list[0], NULL, thread_functionR, (void*)&thread_data_list[0]);
                    deleteHead(right);
                }
            }
            i = 0;
        }
    }
    free(thread_list);
    free(thread_data_list);
}
}