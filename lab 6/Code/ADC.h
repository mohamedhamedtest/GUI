

#ifndef ADC_H_
#define ADC_H_

#include "config.h"

/*****************************************************************************
* Function Name: ADC_Init
* Purpose      : Initialize ADC with AVCC, single conversion mode and ADC_freq = 125 Khz
* Parameters   : void
* Return value : void
*****************************************************************************/
void ADC_init(void);

u32 ADC(u8 ch);



#endif /* ADC_H_ */
