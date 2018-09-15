/*
 * SPI2018.c
 *
 * Created: 9/10/2018 9:28:32 PM
 *  Author: jaekyung
 */ 
#include "SPI2018.h"

void spi_init(){
// 	static const gpio_map_t spi_gpio_map =
// 	{
// 		{SPI_SCK,  AVR32_SPI0_SCK_FUNCTION },  // SPI Clock.
// 		{SPI_MISO, AVR32_SPI0_MISO_FUNCTION},  // MISO.
// 		{SPI_MOSI, AVR32_SPI0_MOSI_FUNCTION},  // MOSI.
// 		{SPI_NPCS0, AVR32_SPI0_NPCS_0_FUNCTION},   // Chip Select NPCS0
// 		{SPI_NPCS1, AVR32_SPI0_NPCS_1_4_FUNCTION},	// Chip Select NPCS1
// 		{SPI_NPCS2, AVR32_SPI0_NPCS_2_3_FUNCTION},	// Chip Select NPCS2
// 		{SPI_NPCS3, AVR32_SPI0_NPCS_3_2_FUNCTION}	// Chip Select NPCS3
// 	};
	
	static const gpio_map_t spi_gpio_map =
	{
		{SPI_SCK,  AVR32_SPI0_SCK_FUNCTION },  // SPI Clock.
		{SPI_MISO, AVR32_SPI0_MISO_FUNCTION},  // MISO.
		{SPI_MOSI, AVR32_SPI0_MOSI_FUNCTION},  // MOSI.
		{SPI_NPCS0, AVR32_SPI0_NPCS_0_FUNCTION}   // Chip Select NPCS0
	};


	// SPI options for channel 0
	spi_options_t spi_options_0 =
	{
		.reg          = NPCS0,		// channel
		.baudrate     = 1000000,	// CLK freq
		.bits         = 8,			// data length
		.spck_delay   = 0,			// delay between CS falling edge and start of CLK
		.trans_delay  = 0,			// delay between clusters of CLKs
		.stay_act     = 0,			// stay active after completion
		.spi_mode     = SPI_MODE_0,	// SPI mode
		.modfdis      = 1			// Mode fault detection disable
	};
	
// 	spi_options_t spi_options_1 =
// 	{
// 		.reg          = NPCS1,		// channel
// 		.baudrate     = 1000000,	// CLK freq
// 		.bits         = 8,			// data length
// 		.spck_delay   = 0,			// delay between CS falling edge and start of CLK
// 		.trans_delay  = 0,			// delay between clusters of CLKs
// 		.stay_act     = 0,			// stay active after completion
// 		.spi_mode     = SPI_MODE_0,	// SPI mode
// 		.modfdis      = 1			// Mode fault detection disable
// 	};
// 	
// 	spi_options_t spi_options_2 =
// 	{
// 		.reg          = NPCS2,		// channel
// 		.baudrate     = 1000000,	// CLK freq
// 		.bits         = 8,			// data length
// 		.spck_delay   = 0,			// delay between CS falling edge and start of CLK
// 		.trans_delay  = 0,			// delay between clusters of CLKs
// 		.stay_act     = 0,			// stay active after completion
// 		.spi_mode     = SPI_MODE_0,	// SPI mode
// 		.modfdis      = 1			// Mode fault detection disable
// 	};
// 	
// 	spi_options_t spi_options_3 =
// 	{
// 		.reg          = NPCS3,		// channel
// 		.baudrate     = 1000000,	// CLK freq
// 		.bits         = 8,			// data length
// 		.spck_delay   = 0,			// delay between CS falling edge and start of CLK
// 		.trans_delay  = 0,			// delay between clusters of CLKs
// 		.stay_act     = 0,			// stay active after completion
// 		.spi_mode     = SPI_MODE_0,	// SPI mode
// 		.modfdis      = 1			// Mode fault detection disable
// 	};
	// Assign I/Os to SPI.
	gpio_enable_module(spi_gpio_map, sizeof(spi_gpio_map) / sizeof(spi_gpio_map[0]));
	
	// Initialize all Chip selects
// 	spi_setupChipReg(SPI_MOD, &spi_options_0, sysclk_get_pba_hz());
// 	spi_setupChipReg(SPI_MOD, &spi_options_1, sysclk_get_pba_hz());
// 	spi_setupChipReg(SPI_MOD, &spi_options_2, sysclk_get_pba_hz());
// 	spi_setupChipReg(SPI_MOD, &spi_options_3, sysclk_get_pba_hz());
	
	// Initialize as master.
	//spi_initMaster(SPI_MOD, &spi_options_0);
	
	// Set SPI selection mode: variable_ps, pcs_decode, delay.
	// spi_selectionMode(SPI_MOD, 0, 0, 0);
	
	// Initialize as slave.
	spi_initSlave(SPI_MOD, 8, SPI_MODE_0);
	
	// Enable SPI module.
	spi_enable(SPI_MOD);
	
// 	USEFUL FUNCTIONS
// 	spi_selectChip
// 	spi_unselectChip
// 	spi_setupChipReg
// 	spi_write
// 	spi_read
}