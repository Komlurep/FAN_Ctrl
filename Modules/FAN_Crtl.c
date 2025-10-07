/*
 * @Author: Komlurep 123731537+Komlurep@users.noreply.github.com
 * @Date: 2025-10-05 23:07:32
 * @LastEditors: Komlurep 123731537+Komlurep@users.noreply.github.com
 * @LastEditTime: 2025-10-07 14:27:45
 * @FilePath: \FAN_Ctrl\Modules\FAN_Crtl.c
 * @Description: 控制风扇
 */

#include "FAN_Crtl.h"

//ADC全局变量
uint16_t pwmDutyCycle =0; 
uint16_t ADC_Value=0;

uint8_t percentage;
int ADC_ValueToPS[10]; 

//发送pwm占空比
void pwm_send(uint8_t ch)
{
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, ch);
}


//电位器控制PWM占空比
void DCP_pwm_FANcrtl(void)
{
		ADC_Value=dong_get_adc();//获取ADC
		sprintf((char *)ADC_ValueToPS, "%d", ADC_Value); //化整		
		percentage = (ADC_Value * 100) / 4095;//ADC换算为百分比
		pwm_send(percentage);
}
