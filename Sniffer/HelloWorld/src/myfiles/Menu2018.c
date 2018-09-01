/*
 * Menu2018.c
 *
 * Created: 8/13/2018 5:18:06 PM
 *  Author: jaekyung
 */ 
#include <conf_board.h>
#include <asf.h>

#include "GPIO2018.h"
#include "Timer2018.h"
#include "Menu2018.h"
	
// GPIO array
char* gpio_cmd[] = {
	INT_ENABLE, INT_DISABLE,
	GPIO_MODE_IN, GPIO_MODE_OUT, 
	GPIO_OUTPUT_HIGH, GPIO_OUTPUT_LOW,GPIO_OUTPUT_TOGGLE,
	GPIO_PU_ENABLE,GPIO_PU_DISABLE,
	GPIO_OC_HIGH,GPIO_OC_LOW,GPIO_OC_TOGGLE, 
	TERMINATE};

void (* gpio_func[]) (arg_t arg) = {
	gpio_inte, gpio_intd, 
	gpio_mode_in, gpio_mode_out, 
	gpio_output_high, gpio_output_low, gpio_output_toggle, 
	gpio_pu_enable, gpio_pu_disable, 
	gpio_oc_high, gpio_oc_low, gpio_oc_toggle
};

// Module arrays
char* mod_string[] = {MODULE_GPIO, "TC", "SPI", "I2C", "UART", "422", "CAN", "ADC", "DAC", "PWM", TERMINATE};
char** cmd_string[] = {gpio_cmd, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
void (** func_array[]) (arg_t) = {gpio_func, NULL};


static int string_search_array(char* key, char** array) {
	// iterates through string array, array, looking for given string, key
	// array must be terminated by TERMINATE
	// returns index of array @ match, -1 otherwise
	int to_return = 0;
	char *element = *array;
	while(strcmp(TERMINATE, element)) {
		if(!strcmp(element, key)){
			return to_return;
		}
		element = *(++array);
		to_return++;
	}
	// reached end of array without a match
	return -1;
}

static arg_t parse_args(char* input_string) {
	// takes string and parses to extract arguments
	// not all commands use all arguments, so unused and invalid field(s) are set to 0
	
	//printf("DEBUG: input string = %s\n\r", input_string);
	char* str1 = strtok(NULL, DELIMIETER);
	char* str2 = strtok(NULL, DELIMIETER);
	arg_t to_return = {atoi(str1), atoi(str2)};
	//printf("DEBUG: Arg1 = %d, Arg2 = %d\n\r", atoi(str1), atoi(str2));
	return to_return;
}

void menu_interface(char* input_string) {
	// takes string, input_string, and then executes function associated with string
	// string must be of format MODULE, COMMAND[, ARG]
	// MODULE is used to get array of commands
	// COMMAND is used to find function to execute
	// ARG is passed to the function
	
	// 1. Use MODULE to get command array (array of strings) and function array (array of func ptrs)
	char *mod_token = strtok(input_string, DELIMIETER);
	if(mod_token == NULL) {
		printf("Invalid format at 1st token.\n\r");
		return;
	}
	int mod_index = string_search_array(mod_token, mod_string);
	if(mod_index < 0) {
		printf("Invalid module (%s).\n\r", mod_token);
		return;
	}
	//printf("DEBUG: Module %d selected (%s).\n\r", mod_index, mod_string[mod_index]);
	char** cmd_array = cmd_string[mod_index];
	void (** func) (arg_t) = func_array[mod_index];
	
	// 2. Use COMMAND and command array to get function from function array
	char *cmd_token = strtok(NULL, DELIMIETER);
	if(cmd_token == NULL) {
		printf("Invalid format at 2nd token.\n\r");
		return;
	}
	int cmd_index = string_search_array(cmd_token, cmd_array);
	if(cmd_index < 0) {
		printf("Invalid command (%s).\n\r", cmd_token);
		return;
	}
	//printf("DEBUG: Command %d selected (%s).\n\r", cmd_index, cmd_array[cmd_index]);
	for(int i = 0; i < cmd_index; i++) {
		func++;
	}
	
	// 3. Parse + pass argument to function
	//printf("DEBUG: Executing function...\n\r");
	(**func)(parse_args(input_string));
}