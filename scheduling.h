#include <pthread.h>
#define QUANTUM 2 // Tiempo en segundos

typedef struct thread
{
    int id;              
    int burst_time;      // Tiempo de ejecución restante
    int priority;        
    pthread_t thread_id; // Identificador del hilo (pthread)
    struct thread *next; // Siguiente hilo en la lista
} thread_t;

// Función para crear un nuevo hilo

thread_t *create_thread(int id, int burst_time, int priority)
{
    thread_t *new_thread = (thread_t *)malloc(sizeof(thread_t));
    new_thread->id = id;
    new_thread->burst_time = burst_time;
    new_thread->priority = priority;
    new_thread->next = NULL;
    return new_thread;
}

// Función para agregar un hilo a la lista enlazada

void add_thread(thread_t **head, thread_t *new_thread)
{
    if (*head == NULL)
    {
        *head = new_thread;
    }
    else
    {
        thread_t *current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_thread;
    }
}