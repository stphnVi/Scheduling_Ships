#include "interfaceRasp.h"

// Definir los pines de los LEDs
const int leds[2] = {17, 23}; // Pines GPIO de los LEDs

// Configura los pines de los LEDs
void setup_leds(void)
{
    wiringPiSetupGpio(); // Inicializa el GPIO
    for (int i = 0; i < sizeof(leds) / sizeof(leds[0]); i++)
    {
        pinMode(leds[i], OUTPUT);
        delay(5);
    }
}

// Usa LEDs para representar el estado de la tarea
void blink_led(task_t *task)
{
    int led = leds[task->task_id % 2]; // Asigna el LED según el ID de la tarea
    digitalWrite(led, HIGH); // Enciende el LED

    // Simula el parpadeo según el estado de la tarea
    delay(1000); // Parpadeo de 1 segundo
    digitalWrite(led, LOW); // Apaga el LED

    printf("LED %d parpadeó para la tarea con ID: %d\n", led, task->task_id);
}
