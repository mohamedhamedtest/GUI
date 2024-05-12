
#ifndef UART_H_
#define UART_H_
#include "config.h"

void Uart_init();
void Uart_Write(u8);
u8 Uart_Read();
void Uart_Write_string(u8 *data);
#define UartIsAvailable() (UCSRA & (1<<RXC))

#endif /* UART_H_ */
