#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "Structs/Boat.h"       // Asegúrate de incluir los encabezados necesarios
#include "Structs/NodeList.h"
#include "Passage.h"

int main() {
    // Inicializar la lista de barcos
    struct NodeList *boatList = malloc(sizeof(struct NodeList));
    if (boatList == NULL) {
        fprintf(stderr, "Error allocating memory for boat list.\n");
        return EXIT_FAILURE;
    }
    boatList->head = NULL; // Asegúrate de inicializar la lista adecuadamente

    // Crear un barco
    struct Boat *myBoat = malloc(sizeof(struct Boat));
    if (myBoat == NULL) {
        fprintf(stderr, "Error allocating memory for boat.\n");
        free(boatList); // Limpiar antes de salir
        return EXIT_FAILURE;
    }
    myBoat->position = 0; // Posición inicial
    myBoat->velocity = 1; // Velocidad (puedes ajustarlo según sea necesario)

    // Crear los datos para el hilo
    struct ThreadData data;
    data.boat = myBoat;
    data.list = boatList;

    // Crear hilos
    pthread_t threadL, threadR;

    // Lanzar hilos para pasar a la izquierda y a la derecha
    if (pthread_create(&threadL, NULL, thread_functionL, (void *)&data) != 0) {
        fprintf(stderr, "Error creating left thread.\n");
        free(myBoat);
        free(boatList);
        return EXIT_FAILURE;
    }

    if (pthread_create(&threadR, NULL, thread_functionR, (void *)&data) != 0) {
        fprintf(stderr, "Error creating right thread.\n");
        free(myBoat);
        free(boatList);
        return EXIT_FAILURE;
    }

    // Esperar a que los hilos terminen
    pthread_join(threadL, NULL);
    pthread_join(threadR, NULL);

    // Limpiar
    free(myBoat);
    free(boatList);

    return EXIT_SUCCESS; // Indica que todo terminó correctamente
}
