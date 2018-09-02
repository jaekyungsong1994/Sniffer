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
	- GPIO,n,OCT
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

// Argument struct definition
// holds arguments for passing to functions
typedef struct {
	int arg1;
	int arg2;
} arg_t;


#define DELIMIETER ", \r\n"
// Keywords General
#define INT_ENABLE "INTE"
#define INT_DISABLE "INTD"
#define TERMINATE "\0"

// Modules
#define MODULE_GPIO "GPIO"
#define MODULE_TC "TIMER"

// GPIO Commands
#define GPIO_MODE_IN "IN"
#define GPIO_READ "READ"
#define GPIO_OUTPUT_HIGH "HIGH"
#define GPIO_OUTPUT_LOW "LOW"
#define GPIO_OUTPUT_TOGGLE "TOGGLE"
#define GPIO_PU_ENABLE "PUE"
#define GPIO_PU_DISABLE "PUD"
#define GPIO_OC_HIGH "OCH"
#define GPIO_OC_LOW "OCL"
#define GPIO_OC_TOGGLE "OCT"

// Timer Commands
#define TC_GET_TIME "GETTIME"
#define TC_SET_TIME "SETTIME"
#define TC_GET_INC "GETINC"
#define TC_SET_INC "SETINC"

void menu_interface(char *);

#endif /* MENU2018_H_ */