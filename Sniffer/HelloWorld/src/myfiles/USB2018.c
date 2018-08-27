/*
 * USB2018.c
 *
 * Created: 5/22/2018 10:07:27 PM
 *  Author: jaekyung
 */ 
#include "USB2018.h"

int read_usb_chars(char *ch) {
	// grab single USB character if possible
	// input: *ch - address to place gotten character
	// output: int - non-negative if successfully gets character
	int to_return = -1;
	if (udi_cdc_is_rx_ready()) {
		to_return = scanf("%c", ch);
	}
	
	return to_return;
}

int get_line(char *buff_ptr) {
	// grabs up to 50 characters of new line terminated string (49 + new line char)
	// and converts to null terminated string in given buffer
	// incorrect termination will override buffer but will return -1
	// input: *ch - address to buffer of size BUFFER_SIZE to write to
	// output: non-negative if buffer is of size greater than 0 and string is properly terminated
	int string_length = 0;
	int is_NL = 0;
	int to_return = -1;
	char* cur_char;
	while((read_usb_chars(cur_char) > 0) && (string_length < BUFFER_SIZE_TEMP) && (!is_NL)) {
		// ch now points to gotten letter from USB
		// check if it's new line char
		(*cur_char == 10) ? (is_NL = 1) : (is_NL = is_NL);
		// write char to buffer; increment pointer and string length
		*buff_ptr = (toupper(*cur_char));
		buff_ptr++;
		string_length++;
	}
	// check for proper termination
	if(is_NL) {
		to_return = 1;
	}
	// add null termination
	if(string_length > 0) {
		buff_ptr--;
		*buff_ptr = 0;
	}
	return to_return;
}