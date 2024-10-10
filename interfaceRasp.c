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

void animate_leds(task_t *task, int delay_time)
{
    int led_colors[3] = {0}; // Arreglo para almacenar el tipo de tarea en cada LED
    int next_led_colors[3];

    task_t *current_task = task;
    int num_tasks = 0;

    while (current_task != NULL)
    {
        num_tasks++;
        current_task = current_task->next;
    }

    // Apagar todos los LEDs inicialmente
    for (int i = 0; i < 3; i++)
    {
        led_colors[i] = 0;
        set_led_color(i, led_colors[i]); // Asegurar que todos estén apagados
    }

    // Animar el desplazamiento de las tareas
    for (int step = 0; step < num_tasks + 3; step++)
    {
        delay(delay_time);

        // Copiar los colores actuales a un nuevo arreglo
        for (int i = 0; i < 3; i++)
        {
            next_led_colors[i] = led_colors[i];
        }

        // Desplazar los valores de los LEDs hacia la derecha
        for (int i = 2; i > 0; i--)
        {
            next_led_colors[i] = led_colors[i - 1];
        }

        // Asignar una nueva tarea al primer LED
        if (step < num_tasks)
        {
            next_led_colors[0] = task->type;
            task = task->next;
        }
        else
        {
            next_led_colors[0] = 0;
        }

        for (int i = 0; i < 3; i++)
        {
            led_colors[i] = next_led_colors[i];
            set_led_color(i, led_colors[i]);
        }
    }

    printf("Animación completada para las tareas\n");
}

void blink_led(task_t *task)
{
    task_t *current_task = task;

    printf("Lista de tareas:\n");

    while (current_task != NULL)
    {

        printf("Tarea ID: %d, Tipo: %d\n", current_task->task_id, current_task->type);

        // Avanzar a la siguiente tarea
        current_task = current_task->next;
    }
    animate_leds(task, 1000);
}
