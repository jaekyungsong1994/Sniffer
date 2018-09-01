/*
 * GPIO2018.c
 *
 * Created: 8/13/2018 4:31:05 PM
 *  Author: jaekyung
 */ 
#include <user_board.h>
#include <gpio.h>			// For general input/output
#include <asf.h>			// To use ASF

#include "GPIO2018.h"
#include "Menu2018.h"


void gpio_init()
{
	// set all pins as inputs
	gpio_configure_pin(GPIO0, GPIO_DIR_INPUT);
	gpio_configure_pin(GPIO1, GPIO_DIR_INPUT);
	gpio_configure_pin(GPIO2, GPIO_DIR_INPUT);
	gpio_configure_pin(GPIO3, GPIO_DIR_INPUT);
	gpio_configure_pin(GPIO4, GPIO_DIR_INPUT);
	gpio_configure_pin(GPIO5, GPIO_DIR_INPUT);
	gpio_configure_pin(GPIO6, GPIO_DIR_INPUT);
	gpio_configure_pin(GPIO7, GPIO_DIR_INPUT);
	gpio_configure_pin(GPIO8, GPIO_DIR_INPUT);
	gpio_configure_pin(GPIO9, GPIO_DIR_INPUT);
	
	// set interrupt handlers
	INTC_register_interrupt(&gpio_int_handler, GPIO_0_VECT, AVR32_INTC_INT0);
	INTC_register_interrupt(&gpio_int_handler, GPIO_1_VECT, AVR32_INTC_INT0);
	INTC_register_interrupt(&gpio_int_handler, GPIO_2_VECT, AVR32_INTC_INT0);
	INTC_register_interrupt(&gpio_int_handler, GPIO_3_VECT, AVR32_INTC_INT0);
	INTC_register_interrupt(&gpio_int_handler, GPIO_4_VECT, AVR32_INTC_INT0);
	INTC_register_interrupt(&gpio_int_handler, GPIO_5_VECT, AVR32_INTC_INT0);
	INTC_register_interrupt(&gpio_int_handler, GPIO_6_VECT, AVR32_INTC_INT0);
	INTC_register_interrupt(&gpio_int_handler, GPIO_7_VECT, AVR32_INTC_INT0);
	INTC_register_interrupt(&gpio_int_handler, GPIO_8_VECT, AVR32_INTC_INT0);
	INTC_register_interrupt(&gpio_int_handler, GPIO_9_VECT, AVR32_INTC_INT0);
	
}

static uint32_t int_to_pin(int pin) {
	switch(pin) {
		case 0: 
			return GPIO0;
		case 1:
			return GPIO1;
		case 2:
			return GPIO2;
		case 3:
			return GPIO3;
		case 4:
			return GPIO4;
		case 5:
			return GPIO5;
		case 6:
			return GPIO6;
		case 7:
			return GPIO7;
		case 8:
			return GPIO8;
		case 9:
			return GPIO9;
		default:
			return -1;
	}
}

__attribute__((__interrupt__)) static void gpio_int_handler(){
	// General interrupt handler for GPIO interrupt
	// iterates through GPIOs looking for interrupts
	uint32_t pin = -1;
	int pin_mask = 0;
	for(int i = 0; i < 10; i++) {
		pin = int_to_pin(i);
		if(pin < 0)
		return;
		
		// get pin mask; eg. pin 2 is 0b100
		pin_mask = 1 << (pin & 0x1F);
		
		// check if interrupt flag is set
		if(AVR32_GPIO.port[pin >> 5].ifr & pin_mask) {
			printf("GPIO%d was triggered. Currently %s.\n\r", i, gpio_get_pin_value(pin) ? "high" : "low");
			
			// clear flag
			AVR32_GPIO.port[pin >> 5].ifrc = pin_mask;
		}
	}
}

void gpio_mode_in (arg_t arg){
	uint32_t pin = int_to_pin(arg.arg1);
	if(pin < 0){
		printf("Invalid pin (%d).\n\r", arg.arg1);
		return;
	}
	gpio_configure_pin(pin, GPIO_DIR_INPUT);
	printf("GPIO%d = %s.\n\r", arg.arg1, gpio_get_pin_value(pin) ? "HIGH" : "LOW");
	return;
}

void gpio_mode_out (arg_t arg){
	uint32_t pin = int_to_pin(arg.arg1);
	if(pin < 0){
		printf("Invalid pin (%d).\n\r", arg.arg1);
		return;
	}
	gpio_configure_pin(pin, GPIO_DIR_OUTPUT);
	return;
}

void gpio_output_high (arg_t arg){
	uint32_t pin = int_to_pin(arg.arg1);
	if(pin < 0){
		printf("Invalid pin (%d).\n\r", arg.arg1);
		return;
	}
	gpio_set_gpio_pin(pin);
	return;
}

void gpio_output_low (arg_t arg){
	uint32_t pin = int_to_pin(arg.arg1);
	if(pin < 0){
		printf("Invalid pin (%d).\n\r", arg.arg1);
		return;
	}
	gpio_clr_gpio_pin(pin);
	return;
}

void gpio_output_toggle (arg_t arg){
	uint32_t pin = int_to_pin(arg.arg1);
	if(pin < 0){
		printf("Invalid pin (%d).\n\r", arg.arg1);
		return;
	}
	gpio_tgl_gpio_pin(pin);
	return;
}


void gpio_pu_enable (arg_t arg){
	uint32_t pin = int_to_pin(arg.arg1);
	if(pin < 0){
		printf("Invalid pin (%d).\n\r", arg.arg1);
		return;
	}
	gpio_enable_pin_pull_up(pin);
	return;
}


void gpio_pu_disable (arg_t arg){
	uint32_t pin = int_to_pin(arg.arg1);
	if(pin < 0){
		printf("Invalid pin (%d).\n\r", arg.arg1);
		return;
	}
	gpio_disable_pin_pull_up(pin);
	return;
}


void gpio_oc_high (arg_t arg){
	uint32_t pin = int_to_pin(arg.arg1);
	if(pin < 0){
		printf("Invalid pin (%d).\n\r", arg.arg1);
		return;
	}
	gpio_set_gpio_open_drain_pin(pin);
	return;
}


void gpio_oc_low (arg_t arg){
	uint32_t pin = int_to_pin(arg.arg1);
	if(pin < 0){
		printf("Invalid pin (%d).\n\r", arg.arg1);
		return;
	}
	gpio_clr_gpio_open_drain_pin(pin);
	return;
}

void gpio_oc_toggle (arg_t arg){
	uint32_t pin = int_to_pin(arg.arg1);
	if(pin < 0){
		printf("Invalid pin (%d).\n\r", arg.arg1);
		return;
	}
	gpio_tgl_gpio_open_drain_pin(pin);
	return;
}

void gpio_inte (arg_t arg){
	uint32_t pin = int_to_pin(arg.arg1);
	if(pin < 0){
		printf("Invalid pin (%d).\n\r", arg.arg1);
		return;
	}
	gpio_enable_pin_interrupt(pin, GPIO_PIN_CHANGE);
	return;
}

void gpio_intd (arg_t arg){
	uint32_t pin = int_to_pin(arg.arg1);
	if(pin < 0){
		printf("Invalid pin (%d).\n\r", arg.arg1);
		return;
	}
	gpio_disable_pin_interrupt(pin);
	return;
}

