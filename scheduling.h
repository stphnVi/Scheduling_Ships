#define QUANTUM 1       // Quantum
#define NUM_PROCESSES 4 // # procesos

//estructura de un proceso
typedef struct process
{
    int id;
    int burst_time;
    struct process *next;
} process_t;

//lista enlazada
typedef struct
{
    process_t *head;
    process_t *tail;
} linked_list_t;

// Función para crear un nuevo proceso
process_t *create_process(int id, int burst_time)
{
    process_t *new_process = (process_t *)malloc(sizeof(process_t)); //para reservar memoria dinámica en el heap para un nuevo proceso del tipo process_t
    new_process->id = id;
    new_process->burst_time = burst_time;
    new_process->next = NULL;
    return new_process;
}

// Función para agregar un proceso a la lista enlazada
void add_process(linked_list_t *list, process_t *new_process)
{
    if (list->head == NULL)
    {
        list->head = new_process;
        list->tail = new_process;
    }
    else
    {
        list->tail->next = new_process;
        list->tail = new_process;
    }
}