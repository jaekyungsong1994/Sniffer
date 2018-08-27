#include <asf.h>
#include <string.h>

#include "USB2018.h"
#include "Timer2018.h"
#include "GPIO2018.h"
#include "Menu2018.h"

int print_time = 0;

//__attribute__((__interrupt__)) static void tc_irq(void)
//{
	//gpio_tgl_gpio_pin(GPIO0);
	//print_time = 1;
	//tc_read_sr(&AVR32_TC0, EXAMPLE_CHANNEL);
//}

int main (void)
{
	// disable interrupts until ready
	cpu_irq_disable();
	
	// initialize and set up interrupts
	INTC_init_interrupts();
	//INTC_register_interrupt(&tc_irq, AVR32_TC0_IRQ0, AVR32_INTC_INT1);
	
	/* Insert system clock initialization code here (sysclk_init()). */
	board_init();
	sleepmgr_init();
	sysclk_init();
	
	// starts and enables for USB
	udc_start();
	stdio_usb_init();
	stdio_usb_enable();
	
	// enable TC and USB clock
	sysclk_enable_peripheral_clock(EXAMPLE_TC);
	sysclk_enable_peripheral_clock(&AVR32_USBC);
	
	// create buffer
	char usb_buffer[BUFFER_SIZE_TEMP];
	
	// initialize TC
	//tc_init();
	
	// GPIO set up
	gpio_init();
	
	// enable interrupts
	cpu_irq_enable();
	
	// gpio_enable_module - used to assign pins to modules eg. UART
	
	while(1) {
		menu_interface();
		delay_ms(1); // USB seems to need at least a small delay
	}
	
	return 0;
}
