#include "CEScheduling.h"
#include <unistd.h>





// Función que ejecuta una tarea (simulación) POSIBLEMENTE HAYA QUE CAMBIAR LA LECTURA DEL QUANTUM
void *execute_task(void *arg)
{
    task_t *task = (task_t *)arg;
    printf("Hilo ejecutando tarea con ID: %d por %d segundos\n", task->task_id, QUANTUM);
    sleep(QUANTUM); // Simula ejecución por el quantum
    task->duration -= QUANTUM;
}

//                                                                 _________________________________________
//________________________________________________________________/ Algoritmo Round Robin
void round_robin_scheduler()
{
    send_status("Round Robin");

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
            add_task(current_task->task_id, current_task->duration, current_task->priority, current_task->boat_id);
            send_status("Round Robin");

        }
        else
        {
            printf("Tarea %d completada.\n", current_task->task_id);
            free(current_task); // Liberar memoria de la tarea
        }
    }
}
//                                                                 _________________________________________
//________________________________________________________________/ Algoritmo Prioridad

//  comparación para qsort
int compare_tasks(const void *a, const void *b)
{
    task_t *task_a = *(task_t **)a; // Convertir punteros de void a punteros a task_t
    task_t *task_b = *(task_t **)b;

    // Ordenar de mayor a menor prioridad
    return task_b->priority - task_a->priority;
}

// Función para ejecutar tareas en orden de prioridad
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
    qsort(tasks_array, count, sizeof(task_t *), compare_tasks);

    // Actualizar la lista enlazada para reflejar el nuevo orden por prioridad
    task_list = tasks_array[0]; // Establecer el primer elemento como la nueva cabeza
    temp = task_list;
    for (int i = 1; i < count; i++)
    {
        temp->next = tasks_array[i];
        temp = temp->next;
    }
    temp->next = NULL; // Terminar la lista

    // Enviar el estado actualizado después de ordenar
    send_status("Priority");

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
   send_status("FCFS");
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

int main()
{
    CEmutex_init(&mutex);



    // Configuración del Unix Domain Socket
    int server_fd;
    struct sockaddr_un server_addr;

    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd < 0)
    {
        perror("Error al crear el socket");
        return -1;
    }

    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, "/tmp/ship_socket");

    unlink("/tmp/ship_socket");
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Error al enlazar el socket");
        close(server_fd);
        return -1;
    }

    if (listen(server_fd, 1) < 0)
    {
        perror("Error al escuchar en el socket");
        close(server_fd);
        return -1;
    }

    printf("Esperando conexión en el socket Unix Domain...\n");
    client_fd = accept(server_fd, NULL, NULL);
    if (client_fd < 0)
    {
        perror("Error al aceptar la conexión");
        close(server_fd);
        return -1;
    }

    printf("Cliente conectado, listo para enviar estados de tareas.\n");



    // Agregar tareas a la lista
    add_task(1, 3, 4,3); // Tarea 1 con duración 3 y prioridad 2 y boat ID Paco
    add_task(2, 1, 2,2); // Tarea 2 con duración 1 y prioridad 3 y boat ID Pesquero
    add_task(3, 4, 1,2); // Tarea 3 con duración 4 y prioridad 1 y boat ID Pesquero
    add_task(4, 2, 3,1); // Tarea 4 con duración 4 y prioridad 1 y boat ID Cargo
    add_task(5, 4, 1,1); // Tarea 5 con duración 4 y prioridad 1 y boat ID Cargo
    //printf("Iniciando Round Robin Scheduler:\n");
    //round_robin_scheduler(); // Ejecutar Round Robin
    printf("Iniciando Fcfs:\n");
    fcfs_scheduler();
    //printf("Iniciando prioridad:\n");
    //execute_tasks_by_priority();

    // Limpiar la lista destruir el mutex
    free_task_list();
    CEmutex_destroy(&mutex);

    return 0;

}
