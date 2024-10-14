#include <unistd.h> 
#include "../../CEThreads/CEThreads.c"

void TimedEquity(int T, struct BoatList *right, struct BoatList *left, int length) {

    int i = 1;
    struct NodeList list;
    initNodeList(&list);
    
    // Inicializa la lista de nodos
    for (int n = 1; n <= length; n++) {
        appendNode(&list, create_node(n));
    }

    struct ThreadData *thread_data_list = (struct ThreadData*) malloc(MAX_BOATS * sizeof(struct ThreadData));
    
    // Variable para controlar el tiempo
    time_t start_time, current_time;

    while (right->count != 0 || left->count != 0) {
        // Empezamos a contar el tiempo
        time(&start_time);
        time(&current_time);

        if(i == 0) {  // Procesar barcos desde el lado izquierdo
            while (difftime(current_time, start_time) < T && left->count != 0) {
                if (list.head->available == 1 && left->count != 0) {
                    printf("Count of boats in west: %d\n", a);
                    thread_data_list[a].boat = &left->boats[a];
                    thread_data_list[a].list = &list;
                    CEThread_create(&threads[a], thread_functionL, (void*)&thread_data_list[a]);
                    CEThread_run(&threads[a]);
                    deleteHead(left);
                }
                time(&current_time);  // Actualiza el tiempo actual
            }
            i = 1;  // Cambiar al lado derecho
        } else {  // Procesar barcos desde el lado derecho
            time(&start_time);  // Restablece el tiempo
            time(&current_time);
            while (difftime(current_time, start_time) < T && right->count != 0) {
                if (list.head->available == 1 && right->count != 0) {
                    printf("Count of boats in west: %d\n", a);
                    thread_data_list[a].boat = &right->boats[a];
                    thread_data_list[a].list = &list;
                    CEThread_create(&threads[a], thread_functionR, (void*)&thread_data_list[a]);
                    CEThread_run(&threads[a]);
                    deleteHead(left);
                }
                time(&current_time); 
            }
            i = 0;
        }
    }

    // Liberar memoria
    free(threads);
    free(thread_data_list);
}
