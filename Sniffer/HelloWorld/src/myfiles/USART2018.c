/*
 * USART2018.c
 *
 * Created: 9/1/2018 11:21:23 PM
 *  Author: jaekyung
 */ 
#include "USART2018.h"

void usart_init(){
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
	gpio_enable_module(USART_GPIO_MAP,
	sizeof(USART_GPIO_MAP) / sizeof(USART_GPIO_MAP[0]));

	// Initialize USART in RS232 mode.
	usart_init_rs232(USART_MOD, &USART_OPTIONS, sysclk_get_pba_hz());

	// Hello world!
	usart_write_line(USART_MOD, "Hello, this is the AVR UC3 MCU saying hello! (press enter)\r\n");
}

void usart_helloworld(){
	usart_write_line(USART_MOD, "Hello, this is the AVR UC3 MCU saying hello! (press enter)\r\n");
}

void usart_inte(arg_t arg){
	
}

void usart_intd(arg_t arg){
	
}

void usart_serial(arg_t arg){
	
}

void usart_rs232(arg_t arg){
	
}

void usart_send(arg_t arg){
	
}

void usart_format(arg_t arg){
	
}