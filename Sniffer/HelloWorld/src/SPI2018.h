/*
 * SPI2018.h
 *
 * Created: 9/10/2018 9:28:18 PM
 *  Author: jaekyung
 */ 
#ifndef SPI2018_H_
#define SPI2018_H_

#include <asf.h>			// To use ASF

#include "Menu2018.h"
#include "spi.h"

#define SPI_MOD (&AVR32_SPI0)
#define SPI_VECT AVR32_SPI0_IRQ
#define NPCS0 0
#define NPCS1 1
#define NPCS2 2
#define NPCS3 3

void spi_init();


#endif /* SPI2018_H_ */