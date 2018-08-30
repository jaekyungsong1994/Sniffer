/*
 * Menu2018.c
 *
 * Created: 8/13/2018 5:18:06 PM
 *  Author: jaekyung
 */ 
#include <conf_board.h>
#include <asf.h>

#include "Timer2018.h"
#include "Menu2018.h"

static uint32_t string_to_pin(char *chr) {
	// takes in character pointer to buffer containing pin number in ASCII
	// returns pin corresponding to string
	uint32_t pin = -1;
	switch(atoi(chr)) {
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
			printf("Invalid argument to GPIO command.\n\r");
			return;
	}
	return pin;
}

static char pin_to_string(uint32_t pin){
	// takes in pin for GPIO
	// returns character
	char chr;
	switch(pin) {
		case GPIO0:
			chr = '0';
			break;
		case GPIO1:
			chr = '1';
			break;
		case GPIO2:
			chr = '2';
			break;
		case GPIO3:
			chr = '3';
			break;
		case GPIO4:
			chr = '4';
			break;
		case GPIO5:
			chr = '5';
			break;
		case GPIO6:
			chr = '6';
			break;
		case GPIO7:
			chr = '7';
			break;
		case GPIO8:
			chr = '8';
			break;
		case GPIO9:
			chr = '9';
			break;
		default:
			chr = '\0';
			break;
	}
	return chr;
}

// AVR32_GPIO_IRQ_n, where n = [0, 15]
void menu_interface(){
	char usb_buffer[BUFFER_SIZE];
	// Get line from USB interface
	if(get_line(usb_buffer) > 0) {
		// tokenize text
		char *token = strtok(usb_buffer, ", \r\n");
		while(token) {
			// GPIO pin request
			if(!strcmp(token, MODULE_GPIO)) {
				// get requested pin
				uint32_t pin;
				token = strtok(NULL, ", \r\n");
				// check for valid argument (48 = '0', 57 = '9')
				if(*token < 48 || *token > 57) {
					printf("Invalid argument to GPIO command.\n\r");
					return;
				}
				// get pin
				pin = string_to_pin(token);
				if(pin < 0) {
					printf("Invalid argument to GPIO command.\n\r");
					return;
				}
				// Get what to do with pin
				token = strtok(NULL, ", \r\n");
				if(!strcmp(token, GPIO_MODE_IN)) {
					gpio_configure_pin(pin, GPIO_DIR_INPUT);
					printf("GPIO%c set to input (%c).\n\r", pin_to_string(pin), gpio_get_pin_value(pin) ? 'H' : 'L');
				} else if(!strcmp(token, GPIO_MODE_OUT)) {
					gpio_configure_pin(pin, GPIO_DIR_OUTPUT);
					printf("GPIO%c set to input.\n\r", pin_to_string(pin));
				// Interrupt
				} else if(!strcmp(token, INT_ENABLE)) {
					gpio_enable_pin_interrupt(pin, GPIO_PIN_CHANGE);
					printf("GPIO%c interrupt enabled.\n\r", pin_to_string(pin));
				} else if(!strcmp(token, INT_DISABLE)) {
					gpio_disable_pin_interrupt(pin);
					printf("GPIO%c interrupt disabled.\n\r", pin_to_string(pin));
				// Push Pull
				} else if(!strcmp(token, GPIO_OUTPUT_HIGH)) {
					gpio_set_gpio_pin(pin);
					printf("GPIO%c pin set high.\n\r", pin_to_string(pin));
				} else if(!strcmp(token, GPIO_OUTPUT_LOW)) {
					gpio_clr_gpio_pin(pin);
					printf("GPIO%c pin set low.\n\r", pin_to_string(pin));
				} else if(!strcmp(token, GPIO_OUTPUT_TOGGLE)) {
					gpio_tgl_gpio_pin(pin);
					printf("GPIO%c pin toggled.\n\r", pin_to_string(pin));
				// Open Collector
				} else if(!strcmp(token, GPIO_PU_ENABLE)) {
					gpio_enable_pin_pull_up(pin);
					printf("GPIO%c pull up enabled.\n\r", pin_to_string(pin));
				} else if(!strcmp(token, GPIO_PU_DISABLE)) {
					gpio_disable_pin_pull_up(pin);
					printf("GPIO%c pull up disabled.\n\r", pin_to_string(pin));
				} else if(!strcmp(token, GPIO_OC_HIGH)) {
 					gpio_set_gpio_open_drain_pin(pin);
 					printf("GPIO%c set high (OC).\n\r", pin_to_string(pin));
 				} else if(!strcmp(token, GPIO_OC_LOW)) {
 					gpio_clr_gpio_open_drain_pin(pin);
 					printf("GPIO%c set low (OC).\n\r", pin_to_string(pin));
				} else if(!strcmp(token, GPIO_OC_TOGGLE)) {
					gpio_tgl_gpio_open_drain_pin(pin);
					printf("GPIO%c toggled (OC). Currently %s.\n\r", pin_to_string(pin), gpio_get_pin_value(pin) ? "high" : "low");
				} else {
					printf("Invalid command.\n\r");
					return;
				}
			} else if(!strcmp(token, "TIME")) {
				printf("Time: %d s\n\r", tick_time() / 10);
			}
			else {
				// Invalid command
				printf("Token: %s\n\r", token);
			}
			
			
			
			// get next token
			token = strtok(NULL, ",");
		}
	}
}