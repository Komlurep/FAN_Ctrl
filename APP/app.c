/*
 * @Author: Komlurep 123731537+Komlurep@users.noreply.github.com
 * @Date: 2025-10-05 23:07:30
 * @LastEditors: Komlurep 123731537+Komlurep@users.noreply.github.com
 * @LastEditTime: 2025-10-07 14:26:18
 * @FilePath: \FAN_Ctrl\APP\app.c
 * @Description: 主程序
 */

/*--------应用层--------*/
#include "app.h"
#include "re_printf.h"

/*--------驱动层--------*/
#include "FAN_getFG.h"
#include "FAN_Crtl.h"
#include "SMG4.h"


//变量
int fansw=0;
float temp,hum;



//初始化
void Init(void)
{
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);//启用TIM2 CH3 PWM通道
	HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_4);//启用TIM1 CH4 信号捕获
	HAL_TIM_Base_Start_IT(&htim6); //启用TIM6
}



void FAN_Ctrl(void);

//主程序
void app_main(void)
{
	Init();
	
	while(1)
	{
		//打印操作/获取值
		printf("\r\nADC 原始值: %s\n", (char *)ADC_ValueToPS);
		printf("百分比: %d%%\n", percentage);
		char buff[100];
		sprintf(buff, "\r\n频率 = %.2f Hz\r\占空比 = %.2f %%\r\nRPM = %.2f\r\n", frequency, duty_cycle, rpm);
		printf(buff);

		//数码规则
		if(percentage>=2)
		{
			UpdateDisplayBuffer(rpm);
		}
		else
		{
			UpdateDisplayBuffer(0);
		}
		
		//风扇开关规则
		FAN_Ctrl();

		//
		HAL_Delay(500);
	}
}

//继电器控制
void FAN_Ctrl(void)
{
	if(percentage >= 2)//电位器超过2%就开启
	{
		HAL_GPIO_WritePin(FANSW_GPIO_Port, FANSW_Pin, GPIO_PIN_SET);//ON
	}
	else
	{
		HAL_GPIO_WritePin(FANSW_GPIO_Port, FANSW_Pin, GPIO_PIN_RESET);//OFF
	}

}

//定时器回调函数
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM2)//采集定时
    {
        FAN_GetFG_Scan();   

    }

		if(htim->Instance == TIM6)//定时器1秒
    {
				DCP_pwm_FANcrtl();//电位器控制PWM占空比
				get_fan_prm();//获取风扇速度
				flashSMG();//刷新数码管
		}
}



