/*
 * USB2018.h
 *
 * Created: 5/22/2018 10:06:59 PM
 *  Author: jaekyung
 */ 


#ifndef USB2018_H_
#define USB2018_H_

#include "stdio_usb.h"

#define BUFFER_SIZE (50)

int read_usb_chars(char *ch);

int get_line(char *buff_ptr);



#endif /* USB2018_H_ */