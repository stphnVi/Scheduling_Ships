#include "scheduling.h"
#include <unistd.h>

// Función que ejecuta una tarea (simulación) POSIBLEMENTE HAYA QUE CAMBIAR LA LECTURA DEL QUANTUM
void *execute_task(void *arg)
{
    task_t *task = (task_t *)arg;
    printf("Hilo ejecutando tarea con ID: %d por %d segundos\n", task->task_id, QUANTUM);
    sleep(QUANTUM); // Simula ejecución por el quantum
    task->duration -= QUANTUM;

    pthread_exit(NULL);
}

//                                                                 _________________________________________
//________________________________________________________________/ Algoritmo Round Robin
void round_robin_scheduler()
{
    while (1)
    {
        task_t *current_task = remove_task(); // Obtener la primera tarea

        if (current_task == NULL)
        {
            printf("No hay más tareas.\n");
            break;
        }

        pthread_t thread;
        pthread_create(&thread, NULL, execute_task, current_task);
        pthread_join(thread, NULL); // Esperar a que el hilo termine

        // Si la tarea no ha terminado, agregarla al final de la lista
        if (current_task->duration > 0)
        {
            add_task(current_task->task_id, current_task->duration, current_task->priority);
        }
        else
        {
            printf("Tarea %d completada.\n", current_task->task_id);
            free(current_task); // Liberar memoria de la tarea
        }
    }
}
//                                                                 _________________________________________
//________________________________________________________________/ Algoritmo Prioridad & SJF

//  comparación para qsort
int compare_priority(const void *a, const void *b)
{
    task_t *task_a = *(task_t **)a; // Convertir punteros de void a punteros a task_t
    task_t *task_b = *(task_t **)b;

    // Ordenar de mayor a menor prioridad
    return task_b->priority - task_a->priority;
}

int compare_SJF(const void *a, const void *b)
{
    task_t *task_a = *(task_t **)a;
    task_t *task_b = *(task_t **)b;

    return task_a->duration - task_b->duration;
}

// Función para ejecutar tareas en orden de prioridad
void priSJF_scheduler(int a)
{
    // Contar el número de tareas
    int count = 0;
    task_t *temp = task_list;
    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }

    // Crear un arreglo de punteros a tareas
    task_t **tasks_array = malloc(count * sizeof(task_t *));
    temp = task_list;
    for (int i = 0; i < count; i++)
    {
        tasks_array[i] = temp;
        temp = temp->next;
    }

    if (a == 1)
    {
        // Ordenar el arreglo por prioridad
        qsort(tasks_array, count, sizeof(task_t *), compare_priority);
    }
    else // Ordenar el arreglo por tiempo
    {
        qsort(tasks_array, count, sizeof(task_t *), compare_SJF);
    }

    // Ejecutar las tareas en orden de prioridad
    pthread_t threads[count]; // Array para los hilos
    for (int i = 0; i < count; i++)
    {
        while (tasks_array[i]->duration > 0)
        {                                                                    // Mientras haya duración restante
            pthread_create(&threads[i], NULL, execute_task, tasks_array[i]); // Crear hilo para la tarea
            pthread_join(threads[i], NULL);                                  // Esperar a que el hilo termine
        }
    }

    // Liberar el arreglo temporal
    free(tasks_array);
}

//                                                                 __________________________________________
//________________________________________________________________/  Algoritmo First Come First Served (FCFS)
void fcfs_scheduler()
{
    while (1)
    {
        task_t *current_task = remove_task(); // Obtener la primera tarea

        if (current_task == NULL)
        {
            printf("No hay más tareas.\n");
            break;
        }

        pthread_t thread;
        pthread_create(&thread, NULL, execute_task, current_task);
        pthread_join(thread, NULL); // Esperar a que el hilo termine

        printf("Tarea %d completada.\n", current_task->task_id);
        free(current_task); // Liberar memoria de la tarea
    }
}

int main()
{
    pthread_mutex_init(&mutex, NULL);
    int a = 0;
    // Agregar tareas a la lista
    add_task(1, 3, 2); // Tarea 1 con duración 3 y prioridad 2
    add_task(2, 1, 3); // Tarea 2 con duración 1 y prioridad 3
    add_task(3, 4, 1); // Tarea 3 con duración 4 y prioridad 1

    // printf("Iniciando Round Robin Scheduler:\n");
    // round_robin_scheduler(); // Ejecutar Round Robin
    // printf("Iniciando Fcfs:\n");
    // fcfs_scheduler();
    printf("Iniciando prioridad:\n");
    priSJF_scheduler(a);

    // Limpiar la lista destruir el mutex
    free_task_list();
    pthread_mutex_destroy(&mutex);

    return 0;
}
