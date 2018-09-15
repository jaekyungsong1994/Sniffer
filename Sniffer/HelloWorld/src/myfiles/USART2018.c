/*
 * USART2018.c
 *
 * Created: 9/1/2018 11:21:23 PM
 *  Author: jaekyung
 */ 
#include "USART2018.h"

int usart_tx_buffer[BUFFER_SIZE], usart_rx_buffer[BUFFER_SIZE];
int usart_rx_position = 0, usart_nl_flag = 0;

__attribute__((__interrupt__)) static void usart_int_handler(){
	// reading char clears interrupt
	int c;
	usart_read_char(USART_MOD, &c);
	usart_rx_buffer[usart_rx_position++] = c;
	usart_rx_position = (usart_rx_position == BUFFER_SIZE) ? BUFFER_SIZE - 1 : usart_rx_position;
	// if character is new line, then set flag
	if(c == '\n') {
		usart_nl_flag = 1;
	}
}

void usart_init(){
	// Set RS232 XCVR enable pin high
	gpio_configure_pin(SERIAL_ENABLE, GPIO_DIR_OUTPUT);
	gpio_set_gpio_pin(SERIAL_ENABLE);
	
	// Assign pin functions
	static const gpio_map_t USART_GPIO_MAP =
	{
		{USART_TX, AVR32_USART1_TXD_1_FUNCTION},
		{USART_RX, AVR32_USART1_RXD_1_FUNCTION}
	};

	// USART options
	// 8N1 by default @ 9600 baud
	static const usart_options_t USART_OPTIONS =
	{
		.baudrate     = 9600,
		.charlength   = 8,
		.paritytype   = USART_NO_PARITY,
		.stopbits     = USART_1_STOPBIT,
		.channelmode  = USART_NORMAL_CHMODE
	};

	// Assign GPIO to USART.
	gpio_enable_module(USART_GPIO_MAP,sizeof(USART_GPIO_MAP) / sizeof(USART_GPIO_MAP[0]));
	
	// Initialize USART in RS232 mode.
	usart_init_rs232(USART_MOD, &USART_OPTIONS, sysclk_get_pba_hz());
	
	// USART interrupt handler
	INTC_register_interrupt(&usart_int_handler, USART_VECT, AVR32_INTC_INT0);
	
	usart_rx_position = 0;
	USART_MOD->idr |= AVR32_USART_IDR_RXRDY_MASK;
	USART_MOD->cr |= AVR32_USART_CR_RXDIS_MASK;
	
}

void usart_poll(){
	if(usart_nl_flag) {
		printf("USART:" );
		for(int i = 0; i < usart_rx_position; i++) {
			printf("%c", usart_rx_buffer[i]);
		}
		printf("\r");
		usart_rx_position = 0;
		usart_nl_flag = 0;
	}
}

void usart_inte(arg_t arg){
	// Enable interrupt + receiver, and reset position
 	usart_rx_position = 0;
	USART_MOD->ier |= AVR32_USART_IER_RXRDY_MASK;
	USART_MOD->cr |= AVR32_USART_CR_RXEN_MASK;
}

void usart_intd(arg_t arg){
	// Disable interrupt + receiver
	USART_MOD->idr |= AVR32_USART_IDR_RXRDY_MASK;
	USART_MOD->cr |= AVR32_USART_CR_RXDIS_MASK;
}

void usart_serial(arg_t arg){
	gpio_set_gpio_pin(SERIAL_ENABLE);
}

void usart_rs232(arg_t arg){
	gpio_clr_gpio_pin(SERIAL_ENABLE);
}

void usart_send(arg_t arg){
	printf("Please type message to send.\r\n");
	while(get_line(usart_tx_buffer) < 1);
	usart_write_line(USART_MOD, usart_tx_buffer);
}

void usart_format(arg_t arg){
	// TODO: make USART format updatable
}