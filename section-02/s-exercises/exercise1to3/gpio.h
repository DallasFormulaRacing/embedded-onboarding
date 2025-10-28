#ifndef MYGPIO_H
#define MYGPIO_H

#include <stdint.h>

void my_gpio_init(uint32_t port, uint32_t pin, uint32_t mode);
void my_gpio_toggle(uint32_t port, uint32_t pin);
void my_hal_delay(uint32_t delay);

#endif