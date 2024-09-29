#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "scheduling.h"

// Función para simular la ejecución de un proceso con RR
void *execute_process(void *arg)
{
    process_t *process = (process_t *)arg;
    while (process->burst_time > 0)
    {
        printf("Process %d running for %d second(s), remaining burst time: %d\n",
               process->id, QUANTUM, process->burst_time - QUANTUM);
        sleep(QUANTUM); // Simula el tiempo de ejecución
        process->burst_time -= QUANTUM;
        if (process->burst_time <= 0)
        {
            printf("Process %d has finished execution.\n", process->id);
        }
    }
    return NULL;
}

// Planificador Round Robin (RR)
void round_robin_scheduler(linked_list_t *process_list)
{
    //Puntero que apunta al inicio de la lista enlazada
    process_t *current_process = process_list->head;
    pthread_t threads[NUM_PROCESSES];

    while (current_process != NULL)
    {
        if (current_process->burst_time > 0)
        {
            // Crear un hilo para el proceso actual
            pthread_create(&threads[current_process->id - 1], NULL, execute_process, (void *)current_process);
            pthread_join(threads[current_process->id - 1], NULL); // Esperar a que el proceso termine su quantum
        }
        current_process = current_process->next; // Siguiente proceso en la lista
        if (current_process == NULL)
        {
            // Reinicia el ciclo si hay procesos aún por ejecutar
            current_process = process_list->head;
        }
    }
}

int main()
{
    // Crear la lista de procesos
    linked_list_t process_list;
    process_list.head = NULL;
    process_list.tail = NULL;

    // Crear los procesos con tiempos de burst diferentes
    add_process(&process_list, create_process(1, 3)); // Proceso 1, tiempo de burst 3
    add_process(&process_list, create_process(2, 4)); 
    add_process(&process_list, create_process(3, 20)); 
    add_process(&process_list, create_process(4, 5)); 

    // Ejecutar el planificador Round Robin
    round_robin_scheduler(&process_list);

    return 0;
}
