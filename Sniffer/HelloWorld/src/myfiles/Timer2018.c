/*
 * Timer2018.c
 *
 * Created: 5/22/2018 10:07:38 PM
 *  Author: jaekyung
 */ 
#include "Timer2018.h"
#include <user_board.h>
#include <gpio.h>			// For general input/output
#include <asf.h>			// To use ASF
#include <tc.h>

int tick = 0;

__attribute__((__interrupt__)) static void tc_int_handler(){
 	tick++;
	// Clear interrupt
	tc_read_sr(TC_MOD, TC_CHANNEL);
}

int tick_time() {
	return tick;
}

void tc_init()
{
	// Assign interupt handler
	INTC_register_interrupt(&tc_int_handler, TC_IRQ, TC_IRQ_PRIORITY);
	
	// Options for waveform generation.
	static const tc_waveform_opt_t waveform_opt = {
		// Select channel
		.channel  = TC_CHANNEL,
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
		// RA compare effect on TIOA.
		.acpa     = TC_EVT_EFFECT_NOOP,
		// Waveform selection: Up w/ clear on RC match
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
		.tcclks   = TC_CLOCK
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
	tc_init_waveform(TC_MOD, &waveform_opt);

	// sets counter value to 100 ms
	// fPBC / TC_DIVIDER = 12 MHz / 128 = 93750 Hz
	// 16 bit counter, so max time btwn interrupts is 0xFFFF / 93750 Hz = 0.699 s
	tc_write_rc(TC_MOD, TC_CHANNEL, (sysclk_get_pbc_hz() / TC_DIVIDER) / 10);
	
	// configure the timer interrupt (what can cause interrupt, RC match in this case)
	tc_configure_interrupts(TC_MOD, TC_CHANNEL, &tc_interrupt);
	
	// Start the timer/counter.
	tc_start(TC_MOD, TC_CHANNEL);
}