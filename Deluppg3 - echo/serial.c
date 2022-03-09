#include <avr/io.h>
#include <util/delay.h>
#include "serial.h"

#define F_OSC 	16000000 // Clock Speed
#define BAUD 	38400

#define MAX_STR_LEN 20

char string_buffer[MAX_STR_LEN];

/* Initializes the UART/USART port for serial communication. */
void uart_init(void) {
	// Enable receiver
	UCSR0B |= _BV(RXEN0);
	
	// Enable transmitter
	UCSR0B |= _BV(TXEN0);

	//8N1 Mode, controlled by USR0C Register
	//8 bit data
	UCSR0C |= _BV(UCSZ01);
	UCSR0C |= _BV(UCSZ00);

	//No parity
	UCSR0C &= ~_BV(UPM01) & ~_BV(UPM00);

	//1 stop bit
    UCSR0C &= ~_BV(USBS0);

	/* Set baud rate */
	uint16_t ubbrn = (F_OSC/(16*BAUD))-1;
	UBRR0L = ubbrn;
	UBRR0H = (ubbrn >> 8);
}

/* Prints the functions argument character to the output buffer (URD0). */
void uart_putchar( unsigned char data ) {
// 	/* Wait for empty transmit buffer */
	while (!(UCSR0A & (1 << UDRE0))); 
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

/* Prints a complete string of characters with the help of uart_putchar() */
void uart_putstr(char string[MAX_STR_LEN]) {
	int i =0;
	
	while (string[i] != 0x00) {
		uart_putchar(string[i]);
		i++;
		if (i >= MAX_STR_LEN) {
			break;
		}
	}
	handle_newline();
}

/* Sending '\n'  '\r' */
/* Character pair helps to format the output properly on console putty Screen */
void handle_newline(void) {	
	/* Send "\n" Character */
		while (!( UCSR0A & (1<<UDRE0)));   /* Wait for empty transmit buffer       */
		UDR0 = '\n';					    /* Put data into buffer, sends the data */
	
	/* Send "\r" Character */
		while (!( UCSR0A & (1<<UDRE0)));   /* Wait for empty transmit buffer       */
		UDR0 = '\r';					    /* Put data into buffer, sends the data */
}


unsigned char uart_getchar( void ) {
	/* Wait for data to be received */
	while (!(UCSR0A & (1 << RXC0)));
	/* Get and return received data from buffer */
	return UDR0;
}

void uart_echo(void) {	
	int i = 0;

	if (UCSR0A & (1 << RXC0)) {
		string_buffer[i] = (unsigned char) uart_getchar();
		
		if (i >= MAX_STR_LEN) {
			uart_putstr("Mem overflow.\n");
		}
		if(string_buffer[i] == '\0') {
			handle_newline();
		}
		uart_putchar(string_buffer[i]);  //maybe a print array function.
		i++;
	}
	
}
