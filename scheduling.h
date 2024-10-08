#ifndef TASK_LIST_H
#define TASK_LIST_H

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define QUANTUM 1
#define MAX_EXECUTION_TIME 1 // Tiempo máximo de ejecución en segundos

// Definición de la estructura de las tareas
typedef struct task
{
    int task_id;
    int duration; // duracion de la terea
    int priority; // Prioridad
    int type;
    struct task *next;
} task_t;

// Lista de tareas (cabeza de la lista enlazada)
extern task_t *task_list;

//  sincronización
extern pthread_mutex_t mutex;

// Prototipos de las funciones
void add_task(int task_id, int duration, int priority, int type);
task_t *remove_task();
void free_task_list();

#endif // TASK_LIST_H
