#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
//#include "serial.h"			// import av labbens header.

int main() {

	DDRB |= (1<<1);				// Skriver PB1, alltså Pin 9, som OUTPUT  ("LYS FÖR HELVETE!");																		
	while (1) {
		PORTB |= (1<<1);		// Skriver hög PB1 ("Pin 9").			*
		_delay_ms(500);			// Ligg lågt en halv sekund.
		PORTB &= ~(1<<1);		// Skriver låg PB1 ("Pin 9").			*
		_delay_ms(500);
	} 
}
