#ifndef SERIAL_H_
#define SERIAL_H_

//Sets up the correct registeries for serial communication to ATmega328p
void uart_init(void);

//writes a character to uart
void uart_putchar(unsigned char data);

//writes a string of characters to uart
void uart_putstr(char s[]);

//Reads a character from TX on uart
unsigned char uart_getchar( void );

void uart_echo(void);

void handle_newline(void);

#endif

