/*
 * GPIO2018.c
 *
 * Created: 8/13/2018 4:31:05 PM
 *  Author: jaekyung
 */ 
#include "GPIO2018.h"

static char pin_to_char(int pin);

int gpio_poll_flag = 0;
int gpio_int_flag[] = {0, 0, 0, 0}; 

__attribute__((__interrupt__)) static void gpio_int_handler(){
	// Iterate through ports and get all interrupt flags, then clear flags
	// Set poll flag
	for(int cur_port = 0; cur_port < 4; cur_port++) {
		gpio_int_flag[cur_port] = AVR32_GPIO.port[cur_port].ifr;
		AVR32_GPIO.port[cur_port].ifrc = 0xFFFFFFFF;
	}
	gpio_poll_flag = 1;
}

void gpio_poll(){
	if(gpio_poll_flag){
		// interrupt was triggered
		int cur_reg = 0;
		for(int cur_port = 0; cur_port < 4; cur_port++){
			cur_reg = gpio_int_flag[cur_port];
			for(int cur_pin = 0; cur_pin < 32; cur_pin++){
				// see if specific pin on specific port has flag set
				if(cur_reg & (1 << cur_pin)){
					int gpio_pin = (cur_port << 5) + cur_pin;
					printf("GPIO%c was triggered. Currently %s.\r\n", pin_to_char(gpio_pin), gpio_get_pin_value(gpio_pin) ? "HIGH" : "LOW");
				}
			}
		}
	}
	gpio_poll_flag = 0;
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
	INTC_register_interrupt(&gpio_int_handler, GPIO_10_VECT, AVR32_INTC_INT0);
	INTC_register_interrupt(&gpio_int_handler, GPIO_11_VECT, AVR32_INTC_INT0);
	INTC_register_interrupt(&gpio_int_handler, GPIO_12_VECT, AVR32_INTC_INT0);
	INTC_register_interrupt(&gpio_int_handler, GPIO_13_VECT, AVR32_INTC_INT0);
	INTC_register_interrupt(&gpio_int_handler, GPIO_14_VECT, AVR32_INTC_INT0);
	INTC_register_interrupt(&gpio_int_handler, GPIO_15_VECT, AVR32_INTC_INT0);
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

static char pin_to_char(int pin){
	switch(pin){
		case GPIO0:
			return '0';
		case GPIO1:
			return '1';
		case GPIO2:
			return '2';
		case GPIO3:
			return '3';
		case GPIO4:
			return '4';
		case GPIO5:
			return '5';
		case GPIO6:
			return '6';
		case GPIO7:
			return '7';
		case GPIO8:
			return '8';
		case GPIO9:
			return '9';
		default:
			return '\0';
		
	}
}

void gpio_mode_in (arg_t arg){
	uint32_t pin = int_to_pin(arg.arg1);
	if(pin < 0){
		printf("Invalid pin (%d).\n\r", arg.arg1);
		return;
	}
	gpio_configure_pin(pin, GPIO_DIR_INPUT);
	return;
}

void gpio_read (arg_t arg){
	uint32_t pin = int_to_pin(arg.arg1);
	if(pin < 0){
		printf("Invalid pin (%d).\n\r", arg.arg1);
		return;
	}
	printf("GPIO%d = %s.\n\r", arg.arg1, gpio_get_pin_value(pin) ? "HIGH" : "LOW");
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

