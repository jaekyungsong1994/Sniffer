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

void tc_init()
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
	tc_init_waveform(EXAMPLE_TC, &waveform_opt);

	/*
	 * Set the compare triggers.
	 * We configure it to count every 1 ms.
	 * We want: (1 / (fPBC / 8)) * RC = 1 ms, hence RC = (fPBC / 8) / 1000
	 * to get an interrupt every 1 ms.
	 */
	tc_write_rc(EXAMPLE_TC, EXAMPLE_CHANNEL, (sysclk_get_pbc_hz() / 8) / 1000); // there's an upper limit for time; can't do 1 second, for example; 1 ms works fine.
	// configure the timer interrupt
	tc_configure_interrupts(EXAMPLE_TC, EXAMPLE_CHANNEL, &tc_interrupt);
	// Start the timer/counter.
	tc_start(EXAMPLE_TC, EXAMPLE_CHANNEL);
}