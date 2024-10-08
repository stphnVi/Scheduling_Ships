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
//                                                                             ______________________________
//____________________________________________________________________________/ Round Robin (RR)

void rr_scheduler(linked_list_t *process_list)
{
    // Puntero que apunta al inicio de la lista enlazada
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

//                                                                             _____________________________________
//____________________________________________________________________________/ Shortest Job First (SJF) && Priority

// Comparison function for qsort
int comparePriority(const void *a, const void *b)
{
    return ((const process_t *)a)->priority - ((const process_t *)b)->priority;
}

int compareSJF(const void *a, const void *b)
{
    return ((const process_t *)a)->burst_time - ((const process_t *)b)->burst_time;
}

void priSJF_scheduler(linked_list_t *process_list, int a)
{

    int count = 0;

    process_t *current = process_list->head;

    // contar procesos

    while (current != NULL)
    {
        count++;
        current = current->next;
    }

    // Convertir la lista array
    process_t *process_array = malloc(count * sizeof(process_t));
    current = process_list->head;
    for (int i = 0; i < count; i++)
    {
        process_array[i] = *current;
        current = current->next;
    }

    //  qsort

    if (a == 1)
    {
        qsort(process_array, count, sizeof(process_t),
              comparePriority);
    }
    else
    {
        qsort(process_array, count, sizeof(process_t),
              compareSJF);
    }

    // Volver a convertir el array ordenado en una lista enlazada
    current = process_list->head;
    for (int i = 0; i < count; i++)
    {
        *current = process_array[i];
        current = current->next;
    }

    // Mostrar la lista enlazada ordenada
    printf("\nLista ordenada:\n");
    current = process_list->head;

    if (a == 1)
    {
        while (current != NULL)
        {
            printf("ID: %d, Prioridad: %d\n", current->id, current->priority);
            current = current->next;
        }
    }
    else
    {
        while (current != NULL)
        {
            printf("ID: %d, SJF: %d\n", current->id, current->priority);
            current = current->next;
        }
    }

    free(process_array);
}

//                                                                             _____________________________________
//____________________________________________________________________________/        First-come, first-served

void FCFS_scheduler(linked_list_t *process_list)
{
    process_t *current = process_list->head;

    printf("\nLista ordenada con First-come, first-served:\n");
    while (current != NULL)
    {
        printf("ID: %d, Prioridad: %d\n", current->id, current->priority);
        current = current->next;
    }
}

//                                                                             _____________________________________
//____________________________________________________________________________/       Real Time Scheduler

void real_time_scheduler(linked_list_t *process_list)
{
    process_t *current = process_list->head;

    while (current != NULL)
    {
        if (current->time > 0)
        {
            printf("Ejecutando  %d\n", current->id);

            if (current->time > QUANTUM)
            {
                // Simular la ejecución del proceso durante el quantum
                sleep(QUANTUM); // Simula el tiempo de ejecución
                current->time -= QUANTUM;
                printf("Interrupción  ID: %d con %d segundos restantes\n", current->id, current->time);
            }
            else
            {

                sleep(current->time);
                printf("Proceso ID %d completado\n", current->id);
                current->time = 0;
            }
        }

        current = current->next;

        if (current == NULL)
        {
            // volvemos al inicio si aún hay procesos
            current = process_list->head;
        }

        // Verificar
        int all_done = 1;
        process_t *check = process_list->head;
        while (check != NULL)
        {
            if (check->time > 0)
            {
                all_done = 0;
                break;
            }
            check = check->next;
        }

        if (all_done)
        {
            printf("\nTodos los procesos han sido completados.\n");
            break;
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
    add_process(&process_list, create_process(1, 3, 1)); // Proceso 1, tiempo de burst 3, prioridad 1
    add_process(&process_list, create_process(2, 4, 5));
    add_process(&process_list, create_process(3, 2, 3));
    add_process(&process_list, create_process(4, 5, 25));

    // rr_scheduler(&process_list);
    // priSJF_scheduler(&process_list, 1); // 1= priority, else = sjf
    // FCFS_scheduler(&process_list);
    real_time_scheduler(&process_list);

    return 0;
}
