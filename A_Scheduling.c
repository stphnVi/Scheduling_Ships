#include "scheduling.h"
#include "interfaceRasp.h"
#include <unistd.h>
#include <sys/time.h> // Para gettimeofday
#include <time.h>     // Para time

task_t *task_list = NULL;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Implementación: agregar
void add_task(int task_id, int duration, int priority, int type)
{
    pthread_mutex_lock(&mutex);

    task_t *new_task = malloc(sizeof(task_t));
    new_task->task_id = task_id;
    new_task->duration = duration;
    new_task->priority = priority;
    new_task->type = type;
    new_task->next = NULL;

    if (task_list == NULL)
    {
        task_list = new_task;
    }
    else
    {
        task_t *temp = task_list;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new_task;
    }

    pthread_mutex_unlock(&mutex);
}

// Implementación: remover la primera tarea de la lista
task_t *remove_task()
{
    pthread_mutex_lock(&mutex);

    if (task_list == NULL)
    {
        pthread_mutex_unlock(&mutex);
        return NULL;
    }

    task_t *task_to_remove = task_list;
    task_list = task_list->next;

    pthread_mutex_unlock(&mutex);

    return task_to_remove;
}

// Función para liberar memoria
void free_task_list()
{
    pthread_mutex_lock(&mutex);

    task_t *temp;
    while (task_list != NULL)
    {
        temp = task_list;
        task_list = task_list->next;
        free(temp);
    }

    pthread_mutex_unlock(&mutex);
}

// Función que ejecuta una tarea (simulación) POSIBLEMENTE HAYA QUE CAMBIAR LA LECTURA DEL QUANTUM
void *execute_task(void *arg)
{
    task_t *task = (task_t *)arg;
    printf("Hilo ejecutando tarea con ID: %d por %d segundos\n", task->task_id, QUANTUM);

    sleep(QUANTUM); // Simula ejecución por el quantum
    task->duration -= QUANTUM;

    blink_led(task);

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
            add_task(current_task->task_id, current_task->duration, current_task->priority, current_task->type);
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

//                                                                 __________________________________________
//________________________________________________________________/  Algoritmo Earliest Deadline First (EDF)

// Comparador para ordenar las tareas según el deadline más cercano
int edf_comparator(const struct timeval *deadline_a, const struct timeval *deadline_b)
{
    return timercmp(deadline_a, deadline_b, >); // Compara si deadline_a es mayor que deadline_b
}

// Función para encontrar la tarea con el deadline más cercano
task_t *edf_find_earliest_deadline_task()
{
    pthread_mutex_lock(&mutex);

    if (task_list == NULL)
    {
        pthread_mutex_unlock(&mutex);
        return NULL;
    }

    task_t *earliest_task = task_list;
    task_t *temp = task_list->next;

    while (temp != NULL)
    {
        struct timeval deadline_a, deadline_b;
        gettimeofday(&deadline_a, NULL); // Deadline de earliest_task
        gettimeofday(&deadline_b, NULL); // Deadline de temp

        if (edf_comparator(&deadline_a, &deadline_b))
        {
            earliest_task = temp;
        }
        temp = temp->next;
    }

    pthread_mutex_unlock(&mutex);
    return earliest_task;
}

// Función auxiliar para ejecutar la tarea con límite de tiempo
void *execute_with_time_limit(void *arg)
{
    task_t *task = (task_t *)arg;
    int total_execution_time = 0; // Lleva la cuenta del tiempo de ejecución total

    while (task->duration > 0 && total_execution_time < MAX_EXECUTION_TIME)
    {
        // Crear un hilo para ejecutar la tarea
        pthread_t thread;
        pthread_create(&thread, NULL, execute_task, (void *)task);
        pthread_join(thread, NULL); // Esperar que el hilo termine

        total_execution_time += QUANTUM; // Incrementa el tiempo total de ejecución

        // Si la tarea ya se completó, salimos del loop
        if (task->duration <= 0)
        {
            printf("Tarea con ID: %d completada\n", task->task_id);
            break;
        }

        // Si excede el tiempo máximo, cortamos la ejecución
        if (total_execution_time >= MAX_EXECUTION_TIME)
        {
            printf("Tarea con ID: %d excedió el tiempo máximo de ejecución\n", task->task_id);
            break;
        }
    }

    pthread_exit(NULL);
}

// Función del algoritmo de planificación EDF
void edf_scheduler()
{
    pthread_t thread;
    task_t *task;

    while ((task = edf_find_earliest_deadline_task()) != NULL)
    {
        // Crear un hilo para ejecutar la tarea con límite de tiempo
        pthread_create(&thread, NULL, execute_with_time_limit, (void *)task);
        pthread_join(thread, NULL); // Esperar que el hilo termine

        // Remover la tarea de la lista después de que termine
        task_t *removed_task = remove_task();
        free(removed_task);
    }
}

int main()
{
    setup_leds();
    pthread_mutex_init(&mutex, NULL);
    int a = 0;
    // Agregar tareas a la lista
    add_task(1, 3, 2, 1); // Tarea 1 con duración 3 y prioridad 2
    add_task(2, 1, 3, 2); // Tarea 2 con duración 1 y prioridad 3
    add_task(3, 4, 1, 0); // Tarea 3 con duración 4 y prioridad 1

    // printf("Iniciando Round Robin Scheduler:\n");
    // round_robin_scheduler(); // Ejecutar Round Robin
    // printf("Iniciando Fcfs:\n");
    // fcfs_scheduler();
    // printf("Iniciando prioridad:\n");

    printf("Iniciando SJF:\n");
    priSJF_scheduler(a);
    // edf_scheduler(a);

    // Limpiar la lista destruir el mutex
    free_task_list();
    pthread_mutex_destroy(&mutex);

    return 0;
}
