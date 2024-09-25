#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* =======================================
 *           Librería CEThreads
 * =======================================
 * Esta libreria proporciona funciones, 
 * similares a pthreads, para manejar 
 * hilos personalizados en C. 
 * ======================================= */


typedef struct {
    int id;                    // Identificador del hilo
    void *value;               // Valor de retorno del hilo
    void *(*function)(void*);  // Puntero hacia la funcion del hilo
    void *arg;                 // Argumento de la funcion del hilo
    int finished;              // Bandera para indicar si el hilo ha terminado
    
} CEThread;


int CEThread_create(CEThread *thread, int id, void *(*function)(void *), void *arg){
    if (thread == NULL | function == NULL) { 
        return -1;  // generar error si el puntero es nulo
    }

    //falta verificar que el id sea unico 
    thread->id = id;         // set id
    thread->function = function; 
    thread->arg = arg;
    thread->finished = 0; // set status: hilo no finalizado

    thread->value = thread->function(thread->arg);  // Simular ejecucion del hilo

    thread->finished = 1;  // Marcar como terminado

    return 0;  

}

void CEThread_end(CEThread *thread, void *value) {
    if (thread == NULL) {
        return; // Validar puntero
    }
    
    thread->value = value;  // Almacenar el valor de retorno
    thread->finished = 1;     // Marcar como terminado
    
}

