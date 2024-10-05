#ifndef TASK_LIST_H
#define TASK_LIST_H

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define QUANTUM 2

// Definición de la estructura de las tareas
typedef struct task
{
    int task_id;
    int duration; // duracion de la terea
    int priority; // Prioridad
    struct task *next;
} task_t;

// Lista de tareas (cabeza de la lista enlazada)
task_t *task_list = NULL;

//  sincronización
pthread_mutex_t mutex;

// Prototipos de las funciones
void add_task(int task_id, int duration, int priority);
task_t *remove_task();
void free_task_list();

// Implementación: agregar
void add_task(int task_id, int duration, int priority)
{
    pthread_mutex_lock(&mutex);

    task_t *new_task = malloc(sizeof(task_t));
    new_task->task_id = task_id;
    new_task->duration = duration;
    new_task->priority = priority;
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

#endif // TASK_LIST_H
