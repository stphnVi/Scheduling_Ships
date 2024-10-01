#include <stdio.h>
#include "CEThreads.c"

// Ejemplo de funcion que se ejecutará en el hilo
void *function(void *arg) {
    for (int i = 0; i < 5; i++) {
        printf("Hola desde el hilo! Argumento: %s (Iteración %d)\n", (char *)arg, i);
    }
    return NULL;
}

// Ejemplo de uso
int main() {
    CEThread thread1;
    CEThread thread2;

    // Crear dos hilos
    CEThread_create(&thread1, 1, function, "Hilo 1");
    CEThread_create(&thread2, 2, function, "Hilo 2");

    // Iniciar la ejecucion de hilos
    CEThread_run(&thread1);
    CEThread_run(&thread2);

    // Esperar a que thread1 termine
    CEThread_join(&thread1);
    printf("Thread 1 ha terminado.\n");

    // Esperar a que thread2 termine
    CEThread_join(&thread2);
    printf("Thread 2 ha terminado.\n");

    return 0;
}
