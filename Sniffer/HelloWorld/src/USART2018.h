/*
 * USART2018.h
 *
 * Created: 9/1/2018 11:14:40 PM
 *  Author: jaekyung
 */ 

#ifndef USART2018_H_
#define USART2018_H_

#include <asf.h>			// To use ASF

#include "Menu2018.h"

#define USART_MOD (&AVR32_USART1)
#define USART_VECT AVR32_USART1_IRQ

void usart_init();

void usart_inte(arg_t);
void usart_intd(arg_t);
void usart_serial(arg_t);
void usart_rs232(arg_t);
void usart_send(arg_t);
void usart_format(arg_t);
void usart_poll_read();

#endif