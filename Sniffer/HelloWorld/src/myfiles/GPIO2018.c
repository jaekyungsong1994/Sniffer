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

// Sets all GPIOs as inputs

__attribute__((__interrupt__)) static void gpio_int_handler(){
	// General interrupt handler for GPIO interrupt
	// iterates through GPIOs looking for interrupts
	uint32_t pin = -1;
	int pin_mask = 0;
	for(int i = 0; i < 10; i++) {
		switch(i){
			case 0: 
				pin = GPIO0;
				break;
			case 1:
				pin = GPIO1;
				break;
			case 2:
				pin = GPIO2;
				break;
			case 3:
				pin = GPIO3;
				break;
			case 4:
				pin = GPIO4;
				break;
			case 5:
				pin = GPIO5;
				break;
			case 6:
				pin = GPIO6;
				break;
			case 7:
				pin = GPIO7;
				break;
			case 8:
				pin = GPIO8;
				break;
			case 9:
				pin = GPIO9;
				break;
			default:
				return;
		}
		
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