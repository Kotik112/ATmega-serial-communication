#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "serial.h"

int main( void ) {

	char my_name[] = "Arman Iqbal";
	uart_init();
		
	while(1)
	{
		uart_putstr(my_name);
		_delay_ms(1000);
	}
	return(0); 
}