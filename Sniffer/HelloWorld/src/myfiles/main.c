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
	udc_start();
	stdio_usb_init();
	stdio_usb_enable();
	
	// enable TC and USB clock
	sysclk_enable_peripheral_clock(TC_MOD);
	sysclk_enable_peripheral_clock(&AVR32_USBC);
	
	// create buffer
	char const usb_buffer[BUFFER_SIZE_TEMP];
	
	// GPIO set up
	gpio_init();
	
	// TC set up
	tc_init();
	
	// enable interrupts
	cpu_irq_enable();
	
	uint16_t spi_send_data = 0, spi_receive_data;
	
	printf("\n\r"); // helps reduce repeated characters coming up on console
	while(1) {
		//menu_interface();
		if(get_line(usb_buffer) > 0) {
			menu_interface(usb_buffer);
		}
		
		usart_poll();
		gpio_poll();
		
// 		spi_write(SPI_MOD, spi_send_data);
// 		spi_receive_data = SPI_MOD->rdr;
// 		printf("Sent %d, received %d\r\n", spi_send_data, spi_receive_data);
// 		spi_send_data++;
// 		delay_ms(999);
		delay_ms(1); // USB seems to need at least a small delay
	}
	
	return 0;
}
       