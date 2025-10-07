/*
 * @Author: Komlurep 123731537+Komlurep@users.noreply.github.com
 * @Date: 2025-10-07 01:26:25
 * @LastEditors: Komlurep 123731537+Komlurep@users.noreply.github.com
 * @LastEditTime: 2025-10-07 14:28:11
 * @FilePath: \FAN_Ctrl\Modules\DCP_getADC.c
 * @Description: 获取电位器ADC值
 */

#include "DCP_getADC.h"

//获取ADC数值
uint16_t dong_get_adc(void)
{
    //开启ADC1
		HAL_ADC_Start(&hadc1);
    //等待ADC转换完成，超时为100ms
    HAL_ADC_PollForConversion(&hadc1,100);
    //判断ADC是否转换成功
    if(HAL_IS_BIT_SET(HAL_ADC_GetState(&hadc1),HAL_ADC_STATE_REG_EOC)){
         //读取值
       return HAL_ADC_GetValue(&hadc1);
    }
    return 0;
}
