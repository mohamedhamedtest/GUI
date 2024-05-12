
 /* Description: 
  * Control the DC Motor direction using L293D H-bridge.
  * Control The DC Motor Speed using PWM from MC. connect the
  * PWM PIN of Timer0 OC0(PB3) to the enable of the Motor. 
  */
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

void PWM_Timer0_Init(unsigned char set_duty_cycle)
{
	
	TCNT0 = 0; //Set Timer Initial value
	
	OCR0  = set_duty_cycle; // Set Compare Value
	
	DDRB  = DDRB | (1<<PB3); //set PB3/OC0 as output pin --> pin where the PWM signal is generated from MC.
	
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);
}
void Increase_Speed(unsigned char duty_cycle)
{
	 _delay_ms(500);
	 if(duty_cycle < 255)
	duty_cycle+=(duty_cycle*0.5);
	OCR0 = duty_cycle;
	
}
void Decrease_Speed(unsigned char duty_cycle)
{
	 _delay_ms(500);
	 if(duty_cycle > 0)
	duty_cycle-=(duty_cycle*0.5);
	 OCR0 = duty_cycle;
}

int main(void)
{ 
	PWM_Timer0_Init(128); //generate duty cycle 50% to get half motor speed
	
	/* configure pin PA0, PA1 and PA2 as input pins */
	DDRA &= 0xF8;

	/* configure pin PC0 and PC1 as output pins */
	DDRC |= 0x03;
	
	/* Motor is stop at the beginning */
	PORTC &= 0xFC;
	 
    while(1)
    {
		/* check if the first push button at PA0 is pressed/not */
		if(PINA & (1<<PA0))
		{
			// Rotate the motor --> clock wise
			PORTC &= (~(1<<PC0));
			PORTC |= (1<<PC1);
		}
		
		/* check if the second push button at PA1 is pressed/not */
		else if(PINA & (1<<PA1))
		{
			// Rotate the motor --> anti-clock wise
			PORTC |= (1<<PC0);
			PORTC &= (~(1<<PC1));
		}
				
		/* check if the third push button at PA2 is pressed/not */
		else if(PINA & (1<<PA2))
		{
			// Stop the motor
			PORTC &= (~(1<<PC0));
			PORTC &= (~(1<<PC1));
		}		
		else if(PINA & (1<<PA3))
		{
			// increase speed
			 Increase_Speed(128);
		}	
		else if(PINA & (1<<PA4))
		{
			// decrease speed
			Decrease_Speed(128);
		}	    
    }
}
	


