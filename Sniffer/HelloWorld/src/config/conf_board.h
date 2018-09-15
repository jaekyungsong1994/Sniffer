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
#define GPIO1 AVR32_PIN_PA22
#define GPIO2 AVR32_PIN_PA23
#define GPIO3 AVR32_PIN_PC03
#define GPIO4 AVR32_PIN_PD13
#define GPIO5 AVR32_PIN_PD14
#define GPIO6 AVR32_PIN_PD21
#define GPIO7 AVR32_PIN_PD29
#define GPIO8 AVR32_PIN_PD30
#define GPIO9 AVR32_PIN_PB00

#define USART_TX AVR32_PIN_PD11
#define USART_RX AVR32_PIN_PD12
#define SERIAL_ENABLE AVR32_PIN_PB01

#define SPI_MOSI AVR32_PIN_PD00
#define SPI_MISO AVR32_PIN_PD01
#define SPI_SCK AVR32_PIN_PD02
#define SPI_NPCS0 AVR32_PIN_PD03
#define SPI_NPCS1 AVR32_PIN_PC16
#define SPI_NPCS2 AVR32_PIN_PC17
#define SPI_NPCS3 AVR32_PIN_PC02

#endif // CONF_BOARD_H
