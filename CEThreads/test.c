#include <stdio.h>
#include "CEThreads.c"

void *function() {
    printf("Hola Mundo\n"); // Imprimir la cadena recibida
    return 0;
}

int main() {
    CEThread my_thread;
    int thread_id = 1; // ID del hilo
    const char *str = "hola mundo"; // Usar puntero a char

    // Crear un hilo con ID 1, especificar la función y el argumento
    if (CEThread_create(&my_thread, thread_id, function, NULL) != 0) {
        fprintf(stderr, "No se pudo crear el hilo\n");
        return EXIT_FAILURE;
    }

    while (!my_thread.finished) {
        // Esperar a que el hilo termine 
    }

    printf("Hilo ID %d ha terminado.\n", my_thread.id);

    return EXIT_SUCCESS;
}
