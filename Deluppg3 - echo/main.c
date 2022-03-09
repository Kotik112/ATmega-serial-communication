#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "serial.h"


int main( void ) {
	uart_init();
		
	while(1)
	{
		uart_echo();
	}
	return(0); 
}