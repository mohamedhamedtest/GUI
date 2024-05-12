#include "config.h"
#include "PWM.h"
#include "UART.h"
#include "ADC.h"
#include <util/delay.h>

int main(void)
{
	ADC_init();
	Uart_init();
	u8 x;
	float y;
	int t;
	float tim;
	startTimer1();
while (1){
	t=readTimer1();
	tim=(t/65535.0)*255.0;
	t=(int)tim;
	y= ADC(5);
	y=y/1023.0*255;
	x=(u8)y;
	Uart_Write('@');
	Uart_Write(x);
	Uart_Write(t);


	}
return 0;
}
