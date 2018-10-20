#include <asf.h>
#include <string.h>

#include "USB2018.h"
#include "Timer2018.h"
#include "GPIO2018.h"
#include "Menu2018.h"
#include "USART2018.h"
#include "SPI2018.h"

int print_time = 0;

int main (void)
{
	// disable interrupts until ready
	cpu_irq_disable();
	
	// initialize and set up interrupts
	INTC_init_interrupts();
	
	/* Insert system clock initialization code here (sysclk_init()). */
	board_init();
	sleepmgr_init();
	sysclk_init();
	usart_init();
	spi_init();
	
	// starts and enables for USB
	stdio_usb_init();
	udc_attach();
	stdio_usb_enable();
	
	// enable TC and USB clock
	sysclk_enable_peripheral_clock(TC_MOD);
	sysclk_enable_peripheral_clock(&AVR32_USBC);
	sysclk_enable_peripheral_clock(SPI_MOD);
	
	// create buffer
	char const usb_buffer[BUFFER_SIZE_TEMP];
	
	// GPIO set up
	gpio_init();
	
	// TC set up
	tc_init();
	
	
	// enable interrupts
	cpu_irq_enable();
	
	// Main code
	while(1) {
		//menu_interface();
		if(get_line(usb_buffer) > 0) {
			menu_interface(usb_buffer);
		}
		usart_poll();
		gpio_poll(); // Moving clear flag in this poll to inside IF statement solved repeated characters issue
		spi_poll();
		
		delay_ms(1); // USB seems to need at least a small delay
	}
	
	return 0;
}
       