#include "interfaceRasp.h"

// Definir los pines de los LEDs
// fila x colmun
const int leds[3][3] = {
    {17, 23, 24}, // Pines GPIO para el primer LED RGB (Rojo, Verde, Azul)
    {14, 15, 18},
    {25, 8, 7}};

void setup_leds(void)
{
    wiringPiSetupGpio();
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            pinMode(leds[i][j], OUTPUT);
        }
    }
}

void set_led_color(int led_index, int task_type)
{

    for (int j = 0; j < 3; j++)
    {
        digitalWrite(leds[led_index][j], LOW);
    }

    switch (task_type)
    {
    case 1: // Tipo de tarea 1: Verde
        digitalWrite(leds[led_index][1], HIGH);
        break;
    case 2: // Tipo de tarea 2: Rojo
        digitalWrite(leds[led_index][0], HIGH);
        break;
    case 3: // Tipo de tarea 3: Azul
        digitalWrite(leds[led_index][2], HIGH);
        break;
    case 0: // Tipo de tarea 0: Apagar
    default:
        break;
    }
}

int led_colors[3] = {0, 0, 0}; // Colores de los 3 LEDs

void animate_leds(task_t *task, int delay_time)
{
    int current_task_color = task->type; // Color de la tarea actual

    // Desplazar los colores de los leds
    for (int i = 2; i > 0; i--)
    {
        led_colors[i] = led_colors[i - 1]; // Desplazar el estado de los LEDs
    }

    // Asignar la nueva tarea al primer LED
    led_colors[0] = current_task_color;

    // Mostrar el estado actual de los LEDs
    for (int i = 0; i < 3; i++)
    {
        set_led_color(i, led_colors[i]);
    }

    delay(delay_time);
}

void blink_led(task_t *task)
{
    task_t *current_task = task;

    // printf("Lista de tareas leds:\n");

    printf("Task type: %d\n", task->type);
    while (current_task != NULL)
    {

        // printf("Tarea ID: %d, Tipo: %d\n", current_task->task_id, current_task->type);

        // Avanzar a la siguiente tarea
        current_task = current_task->next;
    }

    animate_leds(task, 1000);
}
