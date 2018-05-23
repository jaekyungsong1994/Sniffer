/**
 * \file
 *
 * \brief User board configuration template
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#ifndef CONF_BOARD_H
#define CONF_BOARD_H

#define GPIO0 AVR32_PIN_PA19

#define EXAMPLE_CHANNEL 0 // Want TC0
#define EXAMPLE_TC                 (&AVR32_TC0)

#endif // CONF_BOARD_H
