#include "PWM.h"
#include <avr/io.h>
#include "config.h"

/*

non inverting
10 bit fast PWM
oc1a
*/



void PWM_init_timer1_oc1a(){
	DDRD|=(1<<5);
	TCCR1A |= ((1<<WGM11)|(1<<WGM10)|(1<<COM1A1)); // Fast PWM PWM at OC1A
	TCCR1B = 1<<WGM12 | 1<<CS10;
}


/*
duty = (ocr1a / 1023) * 100
OCR1A = duty* 10.23;
*/


void set_duty_oc1a(unsigned char duty){
	OCR1A = duty* 10.23;
}



void PWM_init_timer1_oc1b(){
	DDRD|=(1<<4);
	TCCR1A |= 1<<COM1B1 | 1<<WGM10 | 1<<WGM11;
	TCCR1B = 1<<WGM12 | 1<<CS10;
}

void set_duty_oc1b(unsigned char duty){
	OCR1B = duty* 10.23;
}
void startTimer1(){
	DDRD|=(1<<5);
	TCCR1A |= 0; // Fast PWM PWM at OC1A
	TCCR1B = 3;
}

int readTimer1(){
	return (TCNT1H<<8)|(TCNT1L);
}
