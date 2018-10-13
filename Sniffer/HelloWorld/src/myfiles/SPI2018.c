/*
 * SPI2018.c
 *
 * Created: 9/10/2018 9:28:32 PM
 *  Author: jaekyung
 */ 
#include "SPI2018.h"

int spi_poll_flag = 0;
int spi_buffer[BUFFER_SIZE];
int spi_buffer_length = 0;

void spi_poll(){
	if(spi_poll_flag){
		printf("SPI int triggered (%d): ", spi_buffer_length);
		for(int i = 0; i < spi_buffer_length; i++){
			printf("%d ", spi_buffer[i]);
		}
		printf("\r\n");
		
		spi_buffer_length = 0;
		spi_poll_flag = 0;
	}
}

__attribute__((__interrupt__)) static void spi_int_handler(){
	spi_buffer[spi_buffer_length++] = spi_get(SPI_MOD);
	spi_buffer_length = (spi_buffer_length >= BUFFER_SIZE) ? (BUFFER_SIZE - 1) : spi_buffer_length;
	spi_poll_flag = 1;
}

void spi_init(){	
	static const gpio_map_t spi_gpio_map =
	{
		{SPI_SCK,  AVR32_SPI0_SCK_FUNCTION },	// SPI Clock.
		{SPI_MISO, AVR32_SPI0_MISO_FUNCTION},	// MISO.
		{SPI_MOSI, AVR32_SPI0_MOSI_FUNCTION},	// MOSI.
		{SPI_NPCS0, AVR32_SPI0_NPCS_0_FUNCTION},	// Chip Select NPCS0
		{SPI_NPCS1, AVR32_SPI0_NPCS_1_4_FUNCTION},  // Chip Select NPCS1
		{SPI_NPCS2, AVR32_SPI0_NPCS_2_3_FUNCTION},  // Chip Select NPCS2
		{SPI_NPCS3, AVR32_SPI0_NPCS_3_2_FUNCTION}	// Chip Select NPCS3
	};
	
	// Initialize all Chip selects
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
	
	// Assign I/Os to SPI.
	gpio_enable_module(spi_gpio_map, sizeof(spi_gpio_map) / sizeof(spi_gpio_map[0]));
	
	// Configure Interrupt
	INTC_register_interrupt(&spi_int_handler, SPI_VECT, AVR32_INTC_INT3);
	
	// Initialize as slave.
	arg_t dummy_arg;
	spi_slave(dummy_arg);
}

void spi_inte(arg_t arg){
	// clear existing interrupt before enabling
	spi_get(SPI_MOD);
	SPI_MOD->ier = AVR32_SPI_IER_RDRF_MASK;
}

void spi_intd(arg_t arg){
	SPI_MOD->idr = AVR32_SPI_IER_RDRF_MASK;
}

void spi_write_print(arg_t arg){
	// Write data to Transmit Data Register
	// Note that nothing will be sent in slave mode until master selects Sniffer and provides clock
	if(arg.arg1 > 3 || arg.arg1 < 0){
		printf("Invalid channel number (%d).\r\n", arg.arg1);
		return;
	}
	spi_selectChip(SPI_MOD, (uint8_t) arg.arg1);
	spi_write(SPI_MOD, (uint16_t) arg.arg2);
	spi_unselectChip(SPI_MOD, (uint8_t) arg.arg1);
	printf("Wrote %d to CS%d's Transmit Data Register\r\n", arg.arg2, arg.arg1);
}

void spi_read_print(arg_t arg){
	// Read data from Receive Data Register
	printf("Read %d\r\n", spi_get(SPI_MOD));
}

void spi_master(arg_t arg){	
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
	spi_options_t spi_options_1 =
	{
		.reg          = NPCS1,		// channel
		.baudrate     = 1000000,	// CLK freq
		.bits         = 8,			// data length
		.spck_delay   = 0,			// delay between CS falling edge and start of CLK
		.trans_delay  = 0,			// delay between clusters of CLKs
		.stay_act     = 0,			// stay active after completion
		.spi_mode     = SPI_MODE_0,	// SPI mode
		.modfdis      = 1			// Mode fault detection disable
	};
	spi_options_t spi_options_2 =
	{
		.reg          = NPCS2,		// channel
		.baudrate     = 1000000,	// CLK freq
		.bits         = 8,			// data length
		.spck_delay   = 0,			// delay between CS falling edge and start of CLK
		.trans_delay  = 0,			// delay between clusters of CLKs
		.stay_act     = 0,			// stay active after completion
		.spi_mode     = SPI_MODE_0,	// SPI mode
		.modfdis      = 1			// Mode fault detection disable
	};
	spi_options_t spi_options_3 =
	{
		.reg          = NPCS3,		// channel
		.baudrate     = 1000000,	// CLK freq
		.bits         = 8,			// data length
		.spck_delay   = 0,			// delay between CS falling edge and start of CLK
		.trans_delay  = 0,			// delay between clusters of CLKs
		.stay_act     = 0,			// stay active after completion
		.spi_mode     = SPI_MODE_0,	// SPI mode
		.modfdis      = 1			// Mode fault detection disable
	};
	spi_reset(SPI_MOD);
	spi_initMaster(SPI_MOD, &spi_options_0);
	// Set up options
	spi_setupChipReg(SPI_MOD, &spi_options_0, sysclk_get_pbc_hz());
	spi_setupChipReg(SPI_MOD, &spi_options_1, sysclk_get_pbc_hz());
	spi_setupChipReg(SPI_MOD, &spi_options_2, sysclk_get_pbc_hz());
	spi_setupChipReg(SPI_MOD, &spi_options_3, sysclk_get_pbc_hz());
	// Enable SPI module.
	spi_enable(SPI_MOD);
}

void spi_slave(arg_t arg){
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
	spi_reset(SPI_MOD);
	spi_initSlave(SPI_MOD, 8, SPI_MODE_0);
	spi_setupChipReg(SPI_MOD, &spi_options_0, sysclk_get_pbc_hz());
	gpio_configure_pin(NPCS1, GPIO_DIR_INPUT);
	gpio_configure_pin(NPCS2, GPIO_DIR_INPUT);
	gpio_configure_pin(NPCS3, GPIO_DIR_INPUT);
	spi_enable(SPI_MOD);
}

void spi_size(arg_t arg){
	if(arg.arg1 > 3 || arg.arg1 < 0){
		printf("Invalid channel number (%d).\r\n", arg.arg1);
		return;
	}
	if(arg.arg2 > 16 || arg.arg2 < 8){
		printf("Invalid data size (%d).\r\n", arg.arg2);
		return;
	}
	spi_set_bits_per_transfer(SPI_MOD, arg.arg1, arg.arg2);
}

void spi_mode(arg_t arg){
	if(arg.arg1 > 3 || arg.arg1 < 0){
		printf("Invalid channel number (%d).\r\n", arg.arg1);
		return;
	}
	if(arg.arg2 > 3 || arg.arg2 < 0){
		printf("Invalid SPI mode (%d).\r\n", arg.arg2);
		return;
	}
	spi_set_mode(SPI_MOD, arg.arg1, arg.arg2);
}

void spi_freq(arg_t arg){
	if(arg.arg1 > 3 || arg.arg1 < 0){
		printf("Invalid channel number (%d).\r\n", arg.arg1);
		return;
	}
	if(arg.arg2 < 0){
		printf("Invalid frequency (%d Hz).\r\n", arg.arg2);
		return;
	}
	int baud_div = getBaudDiv(arg.arg2, sysclk_get_pba_hz());
	spi_set_baudrate_register(SPI_MOD, arg.arg1, baud_div);
	printf("Channel %d set to %d Hz.\r\n", arg.arg1, sysclk_get_pba_hz() / baud_div);
}