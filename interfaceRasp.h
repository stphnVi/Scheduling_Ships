#ifndef INTERFACE_RASP_H
#define INTERFACE_RASP_H

#include <wiringPi.h>
#include "scheduling.h"

void blink_led(task_t *task);
// Definir los pines de los LEDs
extern const int leds[3][3];

void setup_leds(void);

void animate_leds(task_t *task, int delay_time);
void set_led_color(int led_index, int task_type);

#endif // INTERFACE_RASP_H
