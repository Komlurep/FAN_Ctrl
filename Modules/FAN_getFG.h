#ifndef __FAN_GETFG_H
#define __FAN_GETFG_H

#include "tim.h"

extern float frequency;     // 频率 (Hz)
extern float duty_cycle;    // 占空比 (%)
extern float rpm;           // 转速 (RPM)


void FAN_GetFG_Scan(void);
void get_fan_prm(void);



#endif /* __FAN_GETFG */
