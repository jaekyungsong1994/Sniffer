/*
 * GPIO2018.h
 *
 * Created: 8/13/2018 4:33:22 PM
 *  Author: jaekyung
 */ 

#ifndef GPIO2018_H_
#define GPIO2018_H_

#include <stdint.h>
#include <user_board.h>
#include <gpio.h>			// For general input/output
#include <asf.h>			// To use ASF

#include "Menu2018.h"

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
#define GPIO_10_VECT AVR32_GPIO_IRQ_10
#define GPIO_11_VECT AVR32_GPIO_IRQ_11
#define GPIO_12_VECT AVR32_GPIO_IRQ_12
#define GPIO_13_VECT AVR32_GPIO_IRQ_13
#define GPIO_14_VECT AVR32_GPIO_IRQ_14
#define GPIO_15_VECT AVR32_GPIO_IRQ_15

void gpio_init();
void gpio_poll();

void gpio_inte (arg_t);
void gpio_intd (arg_t);	
void gpio_mode_in (arg_t);
void gpio_read (arg_t);
void gpio_output_high (arg_t);
void gpio_output_low (arg_t);
void gpio_output_toggle (arg_t);
void gpio_pu_enable (arg_t);
void gpio_pu_disable (arg_t);
void gpio_oc_high (arg_t);
void gpio_oc_low (arg_t);
void gpio_oc_toggle (arg_t);



#endif /* GPIO2018_H_ */