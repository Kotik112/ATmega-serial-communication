#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "serial.h"


int main( void ) {
	uart_init();
	char string_buffer[20] = "";
	while(1)
	{
		uart_getstr(string_buffer);
		control_led(string_buffer);
	}
	return 0; 
}