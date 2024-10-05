#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <signal.h> // Asegúrate de incluir esta línea
#include <sys/time.h>
#include <unistd.h>
#include "scheduling.h"

void *execute_thread(void *arg)
{
    thread_t *thread = (thread_t *)arg;

    // Ejecutar el quantum
    int time_to_run = (thread->burst_time < QUANTUM) ? thread->burst_time : QUANTUM;

    printf("Thread %d running for %d second(s), remaining burst time: %d\n",
           thread->id, time_to_run, thread->burst_time - time_to_run);

    sleep(time_to_run); // Simula el tiempo de ejecución
    thread->burst_time -= time_to_run;

    // Informar si el hilo ha terminado
    if (thread->burst_time <= 0)
    {
        printf("Thread %d has finished execution.\n", thread->id);
    }

    return NULL;
}

//                                                                             _____________________________________
//____________________________________________________________________________/         Round Robin

void rr_scheduler(thread_t *thread_list)
{
    while (1)
    {
        int all_finished = 1; // Verifica si todos los hilos han terminado

        thread_t *current_thread = thread_list; // Reinicia con el primer hilo

        while (current_thread != NULL)
        {
            if (current_thread->burst_time > 0)
            {
                all_finished = 0;

                pthread_create(&current_thread->thread_id, NULL, execute_thread, (void *)current_thread);
                pthread_join(current_thread->thread_id, NULL); // Espera a que termine
            }
            current_thread = current_thread->next; // Avanza al siguiente hilo
        }

        if (all_finished)
        {
            break; // Si todos los hilos han terminado, salir
        }
    }
}

//                                                                             _____________________________________
//____________________________________________________________________________/        First-come, first-served

void FCFS_scheduler(thread_t *thread_list)
{
    // int all_finished = 1; // Verifica si todos los hilos han terminado

    thread_t *current_thread = thread_list; // Reinicia con el primer hilo

    printf("\nLista ordenada con First-come, first-served:\n");
    while (current_thread != NULL)
    {
        pthread_create(&current_thread->thread_id, NULL, execute_thread, (void *)current_thread);
        pthread_join(current_thread->thread_id, NULL);
        // printf("ID: %d, Prioridad: %d\n", current_thread->id, current_thread->priority);
        current_thread = current_thread->next;
    }
}

//                                                                             _____________________________________
//____________________________________________________________________________/ Shortest Job First (SJF) && Priority

int main()
{
    thread_t *thread_list = NULL;

    // Agregar hilos a la lista
    add_thread(&thread_list, create_thread(1, 7, 1));
    add_thread(&thread_list, create_thread(2, 4, 2));
    add_thread(&thread_list, create_thread(3, 5, 3));

    // Ejecutar el planificador Round Robin
    rr_scheduler(thread_list);

    FCFS_scheduler(thread_list);
    // priSJF_scheduler(thread_list, 1); // 1= priority, else = sjf

    // Liberar memoria (opcional)
    while (thread_list != NULL)
    {
        thread_t *temp = thread_list;
        thread_list = thread_list->next;
        free(temp);
    }

    return 0;
}

/*
// Crear la lista de procesos
linked_list_t process_list;
process_list.head = NULL;
process_list.tail = NULL;


// Crear los procesos con tiempos de burst diferentes
add_process(&process_list, create_process(1, 8, 1)); // Proceso 1, tiempo de burst 3, prioridad 1
add_process(&process_list, create_process(2, 6, 5));
add_process(&process_list, create_process(3, 4, 3));
add_process(&process_list, create_process(4, 2, 25));

//rr_scheduler(&process_list);
// priSJF_scheduler(&process_list, 1); // 1= priority, else = sjf
// FCFS_scheduler(&process_list);
// real_time_scheduler(&process_list);


return 0;
*/
