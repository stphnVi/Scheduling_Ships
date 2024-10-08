#ifndef INTERFACE_RASP_H
#define INTERFACE_RASP_H

#include <wiringPi.h>
#include "scheduling.h" // Asegúrate de que 'task_t' esté declarado

// Definir los pines de los LEDs
extern const int leds[2];

// Prototipos de las funciones
void setup_leds(void);
void blink_led(task_t *task);

#endif // INTERFACE_RASP_H
