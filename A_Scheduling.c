#include "scheduling.h"
#include "interfaceRasp.h"
#include <unistd.h>
#include "Canal/Control/Setup.h"
#include "Canal/Structs/Canal.h"
#include "Canal/Structs/BoatList.h"
#include "Canal/Structs/NodeList.h"
#include "Canal/Control/Control.h"
#include "CEThreads/CEThreads.c"
#include <sys/time.h> 
#include <time.h>     

task_t *task_list = NULL;
struct CEmutex mutex;

// Implementación: agregar
void add_task(int task_id, int duration, int priority, int type)
{
    CEmutex_lock(&mutex);

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

    CEmutex_unlock(&mutex);
}

// Implementación: remover la primera tarea de la lista
task_t *remove_task()
{
    CEmutex_lock(&mutex);

    if (task_list == NULL)
    {
        CEmutex_unlock(&mutex);
        return NULL;
    }

    task_t *task_to_remove = task_list;
    task_list = task_list->next;

    CEmutex_unlock(&mutex);

    return task_to_remove;
}

// Función para liberar memoria
void free_task_list()
{
    CEmutex_lock(&mutex);

    task_t *temp;
    while (task_list != NULL)
    {
        temp = task_list;
        task_list = task_list->next;
        free(temp);
    }

    CEmutex_unlock(&mutex);
}

// Función que ejecuta una tarea (simulación) POSIBLEMENTE HAYA QUE CAMBIAR LA LECTURA DEL QUANTUM
void *execute_task(void *arg)
{
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

        CEThread thread;
        CEThread_create(&thread, execute_task, current_task);
        CEThread_run(&thread);
        CEThread_join(&thread); // Esperar a que el hilo termine

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

void execute_tasks_by_priority()
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

    // Ordenar el arreglo por prioridad
    qsort(tasks_array, count, sizeof(task_t *), compare_SJF);

    // Ejecutar las tareas en orden de prioridad
    CEThread threads[count]; // Array para los hilos
    for (int i = 0; i < count; i++)
    {
        while (tasks_array[i]->duration > 0)
        {                                                                    // Mientras haya duración restante
            CEThread_create(&threads[i], execute_task, tasks_array[i]); // Crear hilo para la tarea
            CEThread_run(&threads[i]);
            CEThread_join(&threads[i]);                                  // Esperar a que el hilo termine
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

        CEThread thread;
        CEThread_create(&thread, execute_task, current_task);
        CEThread_run(&thread);
        CEThread_join(&thread); // Esperar a que el hilo termine

        printf("Tarea %d completada.\n", current_task->task_id);
        free(current_task); // Liberar memoria de la tarea
    }
}

//                                                                 __________________________________________
//________________________________________________________________/  Algoritmo Earliest Deadline First (EDF)

// Comparador para ordenar las tareas según el deadline más cercano
int edf_comparator(const struct timeval *deadline_a, const struct timeval *deadline_b)
{
    return timercmp(deadline_a, deadline_b, >);
}

// Función para encontrar la tarea con el deadline más cercano
task_t *edf_find_earliest_deadline_task()
{
    CEmutex_lock(&mutex);

    if (task_list == NULL)
    {
        CEmutex_unlock(&mutex);
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

    CEmutex_unlock(&mutex);
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
        CEThread thread;
        CEThread_create(&thread, execute_task, task);
        CEThread_run(&thread);
        CEThread_join(&thread); // Esperar a que el hilo termine  

        total_execution_time += QUANTUM;
        // Si la tarea ya se completó, salimos del loop
        if (task->duration <= 0)
        {
            printf("Tarea con ID: %d completada\n", task->task_id);
            break;
        }
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

        CEThread thread;
        CEThread_create(&thread, execute_task, task);
        CEThread_run(&thread);
        CEThread_join(&thread); // Esperar a que el hilo termine  

        task_t *removed_task = remove_task();
        free(removed_task);
    }
}

struct FileData {
    char control;
    int W;         
    int tiempo;    
    int largo;     
    int cantidadBarcos;
    char scheduling; 
    int velocidad;
};

struct FileData leerArchivo() {

    FILE *archivo = fopen('Config.txt', "r");
    struct FileData data;
    fscanf(archivo, "%d %d %d %d %d %d", &data.control ,&data.W, &data.tiempo, &data.largo, &data.cantidadBarcos, &data.scheduling, &data.velocidad);
    return data;
}

int main()
{
    setup_leds();
    CEmutex_init(&mutex);
    CEmutex_unlock(&mutex);
    // a =1 prioridad a=? SJF
    int a = 0;

    struct FileData data = leerArchivo(); 
    //int length, char mode, short speed, short w, short time , int quantity
    struct Canal canal = setup(data.largo, data.control , data.velocidad, data.W, data.tiempo, data.cantidadBarcos);
    Equity(1,canal.right, canal.left, 2);
    switch (canal.control) {
        case 'T':
            Tica(canal.right, canal.left, data.largo);
            break;
        case 'E':
            Equity(canal.w, canal.right, canal.left, data.largo);
            break;
        case 'C':
            TimedEquity(canal.time, canal.right, canal.left, data.largo);
            break;
        default:
            printf("Dato no válido: %d\n");
    }
    return 0;
}

void prueba(){
    
    struct Canal canal = setup(2, 'T', 3, 3, 3, 3);
    Tica(canal.right, canal.left, 3);
    
}