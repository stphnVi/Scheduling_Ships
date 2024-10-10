#ifndef TASK_LIST_H
#define TASK_LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "CEThreads.c"

#define QUANTUM 2

// Definición de la estructura de las tareas
typedef struct task
{
    int task_id;
    int duration; // duracion de la terea
    int priority; // Prioridad
    struct task *next;
    int position; //posición en la lista
    int boat_id;
} task_t;

// Lista de tareas (cabeza de la lista enlazada)
task_t *task_list = NULL;

//  sincronización
CEmutex mutex;
//Descriptor de archivo para el cliente del socket
int client_fd;

// Prototipos de las funciones
void add_task(int task_id, int duration, int priority, int boat_id);
task_t *remove_task();
void free_task_list();
void send_status(const char* scheduler_type);

// Implementación: agregar
void add_task(int task_id, int duration, int priority, int boat_id)
{
    CEmutex_lock(&mutex);

    task_t *new_task = malloc(sizeof(task_t));
    new_task->task_id = task_id;
    new_task->duration = duration;
    new_task->priority = priority;
    new_task->boat_id = boat_id;
    new_task->next = NULL;


    int position = 0; //primera tarea

    if (task_list == NULL)
    {
        new_task->position = position;
        task_list = new_task;
    }
    else
    {
        task_t *temp = task_list;
        while (temp->next != NULL)
        {
            temp->position = position;
            position++;
            temp = temp->next;
        }
        new_task->position = position+1; // La nueva tarea toma la siguiente posición
        temp->next = new_task;
    }
    //send_status();
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

    task_t *temp = task_list;
    //int position = 0;

    while (temp != NULL)
    {
      //  temp->position = position;
        //position++;
        temp = temp->next;
    }
    //send_status();
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


void generate_json(char *buffer, size_t size, const char* scheduler_type)
{

    task_t *temp = task_list;
    snprintf(buffer, size,"{\"scheduler\": \"%s\", \"tasks\": [", scheduler_type);

    while (temp != NULL)
    {
        char task_info[64];
        snprintf(task_info, sizeof(task_info),
                 "{\"task_id\": %d,\"boat_id\": %d, \"position\": %d}",
                 temp->task_id, temp->boat_id, temp->position);

        strcat(buffer, task_info);
        if (temp->next != NULL)
        {
            strcat(buffer, ", ");
        }

        temp = temp->next;
    }
    strcat(buffer, "] }\n");
}



// Función para enviar el estado de la tarea por el socket
void send_status(const char* scheduler_type)
{
    char buffer[1024];
    generate_json(buffer, sizeof(buffer), scheduler_type);
    if (client_fd > 0) {
        write(client_fd, buffer, strlen(buffer)); // Enviar el JSON por el socket
        printf("Estado enviado: %s\n", buffer); // Mostrar el estado enviado para depuración
    } else {
        printf("Error: cliente del socket no conectado.\n");
    }
}

#endif // TASK_LIST_H
