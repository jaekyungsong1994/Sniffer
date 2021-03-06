/**
 * \file
 *
 * \brief Chip-specific system clock manager configuration
 *
 * Copyright (c) 2014-2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#ifndef CONF_CLOCK_H_INCLUDED
#define CONF_CLOCK_H_INCLUDED

// Initialize Masks; unused in this case
//#define CONFIG_SYSCLK_INIT_CPUMASK  (1 << SYSCLK_SYSTIMER)
//#define CONFIG_SYSCLK_INIT_PBAMASK  (1 << SYSCLK_USART0)
//#define CONFIG_SYSCLK_INIT_PBBMASK  (1 << SYSCLK_HMATRIX)
//#define CONFIG_SYSCLK_INIT_HSBMASK  (1 << SYSCLK_MDMA_HSB)

// Choose 12 MHz oscillator, OSC0
// 12 MHz (on board osc. frq) too slow for dealing with SPI interrupts
#define CONFIG_SYSCLK_SOURCE        SYSCLK_SRC_OSC0

/* Fbus = Fsys / (2 ^ BUS_div) */
// Divide down CPU or Peripheral Buses for time saving; 8 max
#define CONFIG_SYSCLK_CPU_DIV         0
#define CONFIG_SYSCLK_PBA_DIV         0
#define CONFIG_SYSCLK_PBB_DIV         0
#define CONFIG_SYSCLK_PBC_DIV         0

// USB uses oscillator or PLL; choose one; need 48 MHz at the end
#define   CONFIG_USBCLK_SOURCE        USBCLK_SRC_PLL0

/* Fusb = Fsys / USB_div */
#define CONFIG_USBCLK_DIV             1

/* Fpll0 = (Fclk * PLL_mul) / PLL_div */
#define CONFIG_PLL0_SOURCE            PLL_SRC_OSC0
#define CONFIG_PLL0_MUL               (48000000UL / BOARD_OSC0_HZ)
#define CONFIG_PLL0_DIV               1

// PLL1 isn't used
//#define CONFIG_PLL1_SOURCE          PLL_SRC_OSC0

/* Fpll1 = (Fclk * PLL_mul) / PLL_div */
#define CONFIG_PLL1_SOURCE            PLL_SRC_OSC0
#define CONFIG_PLL1_MUL               (48000000UL / BOARD_OSC0_HZ)
#define CONFIG_PLL1_DIV               1

#endif /* CONF_CLOCK_H_INCLUDED */
