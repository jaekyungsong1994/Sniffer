/*
 * GPIO2018.h
 *
 * Created: 8/13/2018 4:33:22 PM
 *  Author: jaekyung
 */ 

#ifndef GPIO2018_H_
#define GPIO2018_H_

#include <stdint.h>

#define GPIO_0_VECT AVR32_GPIO_IRQ_0
#define GPIO_1_VECT AVR32_GPIO_IRQ_1
#define GPIO_2_VECT AVR32_GPIO_IRQ_2
#define GPIO_3_VECT AVR32_GPIO_IRQ_3
#define GPIO_4_VECT AVR32_GPIO_IRQ_4
#define GPIO_5_VECT AVR32_GPIO_IRQ_5
#define GPIO_6_VECT AVR32_GPIO_IRQ_6
#define GPIO_7_VECT AVR32_GPIO_IRQ_7
#define GPIO_8_VECT AVR32_GPIO_IRQ_8
#define GPIO_9_VECT AVR32_GPIO_IRQ_9

static void gpio_int_handler();
static void gpio_int_handler_2();
static void gpio_int_handler_3();

void gpio_init();



#endif /* GPIO2018_H_ */