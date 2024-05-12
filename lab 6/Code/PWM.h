

#ifndef PWM_H_
#define PWM_H_

//#include "config.h"

void PWM_init_timer1_oc1a();
void set_duty_oc1a(unsigned char duty);

void PWM_init_timer1_oc1b();
void set_duty_oc1b(unsigned char duty);

void PWM_stop_timer1_oc1b();
void PWM_stop_timer1_oc1a();
void startTimer1();
int readTimer1();

#endif /* PWM_H_ */
