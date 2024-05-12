#include "UART.h"


void Uart_init(){
	// baud rate
	UBRRL = 51;// baud rate 9600, F_CPU = 8Mhz

	/* Enable receiver and transmitter */
	UCSRB = (1<<3) | (1<<4);
	UCSRC = (1<<7)| (1<<1)|(1<<2); // 8 bit data transfer
}

void Uart_Write(u8 data){
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) );
	UDR = data;
}

void Uart_Write_string(u8 *data){
	for(u8 i = 0; data[i] != '\0'; i++)
		Uart_Write(data[i]);
}

u8 Uart_Read(){
	while ( !(UCSRA & (1<<RXC)) );
	return UDR;
}
