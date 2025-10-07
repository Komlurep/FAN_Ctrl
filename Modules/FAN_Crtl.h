#ifndef __FAN_CTRL_H
#define __FAN_CTRL_H


#include "DCP_getADC.h"

extern uint16_t pwmDutyCycle;
extern uint16_t ADC_Value;
extern int ADC_ValueToPS[10]; 
extern uint8_t percentage;

void DCP_pwm_FANcrtl(void);



#endif /* __FAN_CTRL_H */
