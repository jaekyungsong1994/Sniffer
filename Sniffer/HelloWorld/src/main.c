/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>

uint8_t ch;

void read_usb_chars(void) {
	// Read in USB chars and act on them, if there are any
	/*
		* r: Reset to bootloader
		*/
	if (udi_cdc_is_rx_ready()) {
		if(scanf("%c",&ch) > 0) {
			printf("user typed \t%c\n\r", ch);	
		}
	}
}

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */

	board_init();
	irq_initialize_vectors();
	cpu_irq_enable();
	//INTC_init_interrupts();
	sleepmgr_init();
	sysclk_init();
	
	udc_start();
	stdio_usb_init();
	stdio_usb_enable();
	
	gpio_configure_pin(AVR32_PIN_PA19, GPIO_DIR_OUTPUT);

	/* Insert application code here, after the board has been initialized. */
	
	while(1) {
		gpio_set_gpio_pin(AVR32_PIN_PA19);
		delay_ms(50);
		gpio_clr_gpio_pin(AVR32_PIN_PA19);
		delay_ms(50);	
		read_usb_chars();
	}
}
