// Including libraries
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "uart.h"
#include "softwaredebugger.h"

// Define Baud Rate
#define BAUD_RATE 9600

// Main
int main(void) {

    SDEBUG_Init();
    
    sei();
    
	while (1)
    {
        SDEBUG_MainFunction();
        _delay_ms(1000);
	}
	return 0; // Never reached
}
