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
	- GPIO,IN,n		: Set GPIO n as input (all GPIO are input by default)
	- GPIO,OUT,n	: Set GPIO n as output
	- GPIO,INTE,n	: enable GPIO n interrupt
	- GPIO,INTD,n	: disable GPIO n interrupt (default)
	- GPIO,PUE,n	: GPIO n has pull up
	- GPIO,PUD,n	: GPIO n has no pull up
	- GPIO,OCE,n	: GPIO n is open collector
	- GPIO,OCD,n	: GPIO n is push-pull
	- GPIO,HIGH,n	: GPIO n outputs high
	- GPIO,LOW,n	: GPIO n outputs low
	- GPIO,TOGGLE	: GPIO n outputs low
-TIMER
	- TIMER,INTE		: Enable interrupt
	- TIMER,INTD		: Disable interrupt (default)
	- TIMER,GETTIME		: Get current counter value
	- TIMER,SETTIME,n	: Set counter value
	- TIMER,GETINC		: Get time between increments
	- TIMER,SETINC,n	: Set time between increments (0.1 sec by default, 0.699 sec max)
- USART:
	- USART,INTE	: Enable interrupt
	- USART,INTD	: Disable interrupt (default)
	- USART,SERIAL	: Disable RS232 XCVR
	- USART,RS232	: Enable RS232 XCVR
	- USART,SEND	: Send message typed after command
	- USART,FORMAT	: Format USART (8N1 by default)
- SPI:
	- SPI,INTE		: Enable interrupt for Receive Data Register; existing flags are cleared before enable
	- SPI,INTD		: Disable interrupt for Receive Data Register
	- SPI,WRITE,n,m	: Send data m to chip n (decimal) in master mode, writes data to Transmit Data Register in slave mode
	- SPI,READ		: Read data from Receive Data Register
	- SPI,MASTER	: Puts sniffer into master mode
	- SPI,SLAVE		: Puts sniffer into slave mode (default); only NPCS0 can be used, other NPCS set to input
	- SPI,SIZE,n,m	: Sets data size of chip n to m, from 8 to 16
	- SPI,MODE,n,m	: Sets mode of chip n to m
	- SPI,FREQ,n,m	: Sets freq of chip n to m, prints closest possible freq
*/

#ifndef MENU2018_H_
#define MENU2018_H_

#include <asf.h>
#include <conf_board.h>
#include <stdio.h>
#include <string.h>

#include "GPIO2018.h"
#include "SPI2018.h"
#include "Timer2018.h"
#include "USART2018.h"
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
#define MODULE_USART "USART"
#define MODULE_SPI "SPI"

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

// USART Commands
#define USART_SERIAL "SERIAL"
#define USART_RS232 "RS232"
#define USART_SEND "SEND"
#define USART_FORMAT "FORMAT"

// SPI Commands
#define SPI_WRITE "WRITE"
#define SPI_READ "READ"
#define SPI_MASTER "MASTER"
#define SPI_SLAVE "SLAVE"
#define SPI_SIZE "SIZE"
#define SPI_MODE "MODE"
#define SPI_FREQ "FREQ"

void menu_interface(char *);

#endif /* MENU2018_H_ */