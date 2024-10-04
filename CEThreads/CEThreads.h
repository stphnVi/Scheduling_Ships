#ifndef CETHREADS_H
#define CETHREADS_H
#include <setjmp.h>

typedef struct {
    int id;                    // Identificador del hilo
    void *value;               // Valor de retorno del hilo
    void *(*function)(void*);  // Puntero a la funcion que ejecuta el hilo
    void *arg;                 // Argumento de la funcion del hilo
    int finished;              // Bandera para indicar si el hilo ha terminado
    jmp_buf context;           
} CEThread;

// Funciones CEThreads

int CEThread_create(CEThread *thread, int id, void *(*function)(void *), void *arg);
void CEThread_run(CEThread *thread);
void CEThread_end(CEThread *thread);
void CEThread_join(CEThread *thread);

typedef struct {
    volatile int locked;       
} CEmutex;

// Funciones CEmutex
void CEmutex_init(CEmutex *mutex);   // Inicializar el mutex
void CEmutex_lock(CEmutex *mutex);   // Bloquear el mutex
void CEmutex_unlock(CEmutex *mutex); // Desbloquear el mutex
void CEmutex_destroy(CEmutex *mutex); // Destruir el mutex

#endif // CETHREADS_H
