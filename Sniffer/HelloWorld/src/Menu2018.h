/*
 * Menu2018.h
 *
 * Created: 8/13/2018 5:18:53 PM
 *  Author: jaekyung
 */ 

/*
Commands are sent in a comma delimited format with no spaces. Not case sensitive

Modules are: ADC, GPIO, DAC, UART0, UART1, SPI, I2C, PWM, and CAN

Commands:
- GPIO:
	- GPIO,n,IN		: Set GPIO n as input
	- GPIO,n,OUT	: Set GPIO n as output
	- GPIO,n,INTE	: enable GPIO n interrupt
	- GPIO,n,INTD	: disable GPIO n interrupt
	- GPIO,n,PUE	: GPIO n has pull up
	- GPIO,n,PUD	: GPIO n has no pull up
	- GPIO,n,OCE	: GPIO n is open collector
	- GPIO,n,OCD	: GPIO n is push-pull
	- GPIO,n,HIGH	: GPIO n outputs high
	- GPIO,n,LOW	: GPIO n outputs low
	- GPIO,n,TOGGLE	: GPIO n outputs low
*/

#ifndef MENU2018_H_
#define MENU2018_H_

#include <stdio.h>
#include <string.h>

#include "USB2018.h"

#define BUFFER_SIZE 50

// Keywords General
#define INT_ENABLE "INTE"
#define INT_DISABLE "INTD"

// Keywords GPIO
#define MODULE_GPIO "GPIO"
#define GPIO_MODE_IN "IN"
#define GPIO_MODE_OUT "OUT"
#define GPIO_OUTPUT_HIGH "HIGH"
#define GPIO_OUTPUT_LOW "LOW"
#define GPIO_OUTPUT_TOGGLE "TOGGLE"
#define GPIO_PU_ENABLE "PUE"
#define GPIO_PU_DISABLE "PUD"
#define GPIO_OC_HIGH "OCH"
#define GPIO_OC_LOW "OCL"
#define GPIO_OC_TOGGLE "OCT"

static uint32_t string_to_pin(char *chr);
static char pin_to_string(uint32_t pin);
void menu_interface();

#endif /* MENU2018_H_ */