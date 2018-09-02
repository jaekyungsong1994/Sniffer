/*
 * Timer2018.h
 *
 * Created: 5/22/2018 10:07:12 PM
 *  Author: jaekyung
 */ 


#ifndef TIMER2018_H_
#define TIMER2018_H_

#include <stdint.h>
#include <user_board.h>
#include <gpio.h>			// For general input/output
#include <asf.h>			// To use ASF
#include <tc.h>

#include "Menu2018.h"

// TC Channel
// TC0 uses Peripheral Bus C clk, while TC1 uses PBA clk
#define TC_CHANNEL 0

// TIMER_CLOCK1 is 32 KHz oscillator, while TIMER_CLOCK2 = PBX / 2, TIMER_CLOCK3 = PBX / 8, etc.
// In this case, TC_CLOCK = TIMER_CLOCK5 = PBC / (128 * 2^(CONFIG_SYSCLK_PBA_DIV)) = PBC / 128
#define TC_CLOCK TC_CLOCK_SOURCE_TC5
#define TC_DIVIDER 128

#define TC_IRQ AVR32_TC0_IRQ0
#define TC_IRQ_PRIORITY AVR32_INTC_INT0

#define TC_MOD (&AVR32_TC0)

void tc_init();
void tc_get_time(arg_t);
void tc_set_time(arg_t);
void tc_get_increment(arg_t);
void tc_set_increment(arg_t);
void tc_inte(arg_t);
void tc_intd(arg_t);



#endif /* TIMER2018_H_ */