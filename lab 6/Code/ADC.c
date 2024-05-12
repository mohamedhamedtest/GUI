#include "ADC.h"
#include "config.h"


void ADC_init(void){
	ADMUX = 1<<REFS0;
	ADCSRA = 1<<ADEN | 1<<ADPS0 | 1<<ADPS1 | 1<<ADPS2;
}



u32 ADC(u8 ch){
	ADMUX = ch | 1<<REFS0;
	SETBIT(ADCSRA,ADSC); // start conversion
	while(READBIT(ADCSRA,ADSC) == 1){}
//	while(READBIT(ADCSRA,ADIF) == 0){}
	u32 ADCVal= ADCL;
		ADCVal|=(ADCH<<8);
		return ADCVal;
}

