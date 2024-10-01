#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <setjmp.h>

/* =======================================
 *           Librería CEThreads
 * =======================================
 * Esta libreria proporciona funciones, 
 * similares a pthreads, para manejar 
 * hilos personalizados en C. 
 * ======================================= */

#define STACK_SIZE 1024 * 1024
#define MAX_THREADS 10

typedef struct {
    int id;                    // Identificador del hilo
    void *value;               // Valor de retorno del hilo 
    void *(*function)(void*);  // Puntero hacia la funcion del hilo 
    void *arg;                 // Argumento de la funcion del hilo 
    jmp_buf context;           // Contexto del hilo
    int finished;              // Bandera para indicar si el hilo ha terminado
    
} CEThread;

CEThread threads[MAX_THREADS]; // Lista de hilos, maximo 10
int current_thread = -1; // Indice del hilo actual

// RUN NEXT: Ejecutar el siguiente hilo
void CEThread_run_next() {
    for (int i = 0; i < MAX_THREADS; i++) { // para cada hilo en la lista
        if (threads[i].id != 0 && !threads[i].finished) { // si el id es diferente de 0 y no ha terminado
            current_thread = i;  // Establecer el hilo actual
            longjmp(threads[i].context, 1); // Cambiar al contexto del hilo
        }
    }
}

// RUN: Ejecutar hilo
void CEThread_run(CEThread *thread) {
    if(setjmp(thread->context) == 0) {
        thread->function(thread->arg); // ejecutar el hilo pasando el argumento
        thread->finished; // marcar como terminado
        CEThread_run_next(); // ejecutar siguiente hilo
    }
}

int CEThread_create(CEThread *thread, int id, void *(*function)(void *), void *arg){
    if (thread == NULL | function == NULL) { 
        return -1;  // generar error si el puntero es nulo
    }

    //falta verificar que el id sea unico 
    thread->id = id;             // set id
    thread->function = function; // set function
    thread->arg = arg;           // set argument
    thread->finished = 0;        // set status: hilo no finalizado

    //Ejecutar el hilo
    CEThread_run(thread);

    return 0;  

}

// END: Finalizar un hilo
void CEThread_end(CEThread *thread) {
    if (thread != NULL) { // validacion del hilo
        thread->finished = 1;     // Marcar como terminado
    }    
}

// JOIN: esperar a que un hilo termine su ejecucion, para que el hilo 
// principal u otros hilos se sincronicen con el final de ese hilo
void CEThread_join(CEThread *thread) {
    if (thread == NULL) {
        return;
    }

    while (!thread->finished) { // Ejecuta otros hilos hasta que termine el hilo especificado
            CEThread_run_next(thread);
    }
}


