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

#define BUFFER_SIZE (50)

int read_usb_chars(char *ch) {
	// grab single USB character if possible
	// input: *ch - address to place gotten character
	// output: int - non-negative if successfully gets character
	int to_return = -1;
	if (udi_cdc_is_rx_ready()) {
		to_return = scanf("%c", ch);
		//if(to_return > 0) {
			//printf("user typed \t%c\n\r", *ch);	
		//}
	}
	
	return to_return;
}

int get_line(char *buff_ptr) {
	// grabs up to 50 characters of new line terminated string (49 + new line char) 
	// and converts to null terminated string in given buffer
	// incorrect termination will override buffer but will return -1
	// input: *ch - address to buffer of size BUFFER_SIZE to write to
	// output: non-negative if buffer is of size greater than 0 and string is properly terminated
	int string_length = 0;
	int is_NL = 0;
	int to_return = -1;
	char* cur_char;
	while((read_usb_chars(cur_char) > 0) && (string_length < BUFFER_SIZE) && (!is_NL)) {
		// ch now points to gotten letter from USB
		// check if it's new line char
		(*cur_char == 10) ? (is_NL = 1) : (is_NL = is_NL);
		// write char to buffer; increment pointer and string length
		*buff_ptr = *cur_char;
		buff_ptr++;
		string_length++;
	}
	// check for proper termination
	if(is_NL) {
		to_return = 1;
	}
	// add null termination
	if(string_length > 0) {
		buff_ptr--;
		*buff_ptr = 0;
	}
	return to_return;
}

static void tc_init(volatile avr32_tc_t *tc)
{
	// Options for waveform generation.
	static const tc_waveform_opt_t waveform_opt = {
		// Use channel 0
		.channel  = EXAMPLE_CHANNEL,
		// Software trigger effect on TIOB.
		.bswtrg   = TC_EVT_EFFECT_NOOP,
		// External event effect on TIOB.
		.beevt    = TC_EVT_EFFECT_NOOP,
		// RC compare effect on TIOB.
		.bcpc     = TC_EVT_EFFECT_NOOP,
		// RB compare effect on TIOB.
		.bcpb     = TC_EVT_EFFECT_NOOP,
		// Software trigger effect on TIOA.
		.aswtrg   = TC_EVT_EFFECT_NOOP,
		// External event effect on TIOA.
		.aeevt    = TC_EVT_EFFECT_NOOP,
		// RC compare effect on TIOA.
		.acpc     = TC_EVT_EFFECT_NOOP,
		/*
		 * RA compare effect on TIOA.
		 * (other possibilities are none, set and clear).
		 */
		.acpa     = TC_EVT_EFFECT_NOOP,
		/*
		 * Waveform selection: Up mode with automatic trigger(reset)
		 * on RC compare.
		 */
		.wavsel   = TC_WAVEFORM_SEL_UP_MODE_RC_TRIGGER,
		// External event trigger enable.
		.enetrg   = false,
		// External event selection.
		.eevt     = 0,
		// External event edge selection.
		.eevtedg  = TC_SEL_NO_EDGE,
		// Counter disable when RC compare.
		.cpcdis   = false,
		// Counter clock stopped with RC compare.
		.cpcstop  = false,
		// Burst signal selection.
		.burst    = false,
		// Clock inversion.
		.clki     = false,
		// Internal source clock 3; connects to fPBC/8
		.tcclks   = TC_CLOCK_SOURCE_TC3
	};

	// Options for enabling TC interrupts
	static const tc_interrupt_t tc_interrupt = {
		.etrgs = 0,
		.ldrbs = 0,
		.ldras = 0,
		.cpcs  = 1, // Enable interrupt on RC compare alone
		.cpbs  = 0,
		.cpas  = 0,
		.lovrs = 0,
		.covfs = 0
	};
	// Initialize the timer/counter.
	tc_init_waveform(tc, &waveform_opt);

	/*
	 * Set the compare triggers.
	 * We configure it to count every 1 ms.
	 * We want: (1 / (fPBC / 8)) * RC = 1 ms, hence RC = (fPBC / 8) / 1000
	 * to get an interrupt every 1 ms.
	 */
	tc_write_rc(tc, EXAMPLE_CHANNEL, (sysclk_get_pbc_hz() / 8) / 1000); // there's an upper limit for time; can't do 1 second, for example; 1 ms works fine.
	// configure the timer interrupt
	tc_configure_interrupts(tc, EXAMPLE_CHANNEL, &tc_interrupt);
	// Start the timer/counter.
	tc_start(tc, EXAMPLE_CHANNEL);
}

int print_time = 0;

__attribute__((__interrupt__)) static void tc_irq(void)
{
	gpio_tgl_gpio_pin(GPIO0);
	print_time = 1;
	tc_read_sr(&AVR32_TC0, EXAMPLE_CHANNEL);
}

int main (void)
{
	// disable interrupts until ready
	cpu_irq_disable();
	
	// initialize and set up interrupts
	INTC_init_interrupts();
	INTC_register_interrupt(&tc_irq, AVR32_TC0_IRQ0, AVR32_INTC_INT1);
	
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
	//sysclk_enable_peripheral_clock(&AVR32_USBC);
	
	// GPIO set up
	gpio_configure_pin(GPIO0, GPIO_DIR_OUTPUT);
	
	// create buffer
	char usb_buffer[BUFFER_SIZE];
	
	// initialize TC
	volatile avr32_tc_t *tc = EXAMPLE_TC;
	tc_init(tc);
	
	// enable interrupts
	cpu_irq_enable();
	
	while(1) {
		if(get_line(usb_buffer) > 0) {
			printf("typed: %s\n\r", usb_buffer);
		}
		if(print_time) {
			printf("1 ms has passed.\n\r");
			print_time = 0;
		}
		delay_ms(1); // USB seems to need at least a small delay
	}
	
	return 0;
}
