/*
 * @Author: Komlurep 123731537+Komlurep@users.noreply.github.com
 * @Date: 2025-10-05 23:07:32
 * @LastEditors: Komlurep 123731537+Komlurep@users.noreply.github.com
 * @LastEditTime: 2025-10-07 14:26:59
 * @FilePath: \FAN_Ctrl\Modules\FAN_getFG.c
 * @Description: 获取风扇编码器频率和占空比
 */

#include "FAN_getFG.h"


float frequency = 0;		//频率		   
float duty_cycle = 0;		//占空比		
float rpm =0;

//捕获变量
uint16_t ccr1_cnt = 0;      //第一次下降沿捕获时CCR值            
uint16_t ccr2_cnt = 0;		//第一次上升沿捕获时CCR值  		
uint16_t Period_cnt = 0;	//			
uint16_t Period_cnt1 =0;	//发生计数器溢出事件次数		
uint16_t Period_cnt2 = 0;	//			 
uint16_t ic_flag = 0;		//输入捕获标志		
uint16_t end_flag = 0;		//捕获结束标志		


//获取风扇速度
void get_fan_prm(void)
{
	if(end_flag){																											
		duty_cycle=(float)(Period_cnt1 * 65536 + ccr1_cnt + 1) * 100 /(Period_cnt2 * 65536 + ccr2_cnt + 1); //占空比换算
  		frequency=1000000 / (float)(Period_cnt2 * 65536 + ccr2_cnt + 1);// 换算频率
		rpm = frequency * 30; // 普通风扇RPM = freq*30 
		end_flag = 0;	//捕获结束标志
	}
		
}


	
void FAN_GetFG_Scan(void)
{
   Period_cnt ++;	
}


//定时器输入捕获回调
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) 
	{	   
		if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4){		//是否是通道1   
			if(end_flag == 0){							    //判断结束标志是不是0   
				switch(ic_flag){							//判断此时处于捕获第几阶段   
					case 0:									   
					{                                       //第一次捕获到上升沿
						__HAL_TIM_SET_COUNTER(&htim1,0);    //定时器1计数设置为0 
						ccr1_cnt = 0;						//参数设置0
						ccr2_cnt =0;                        
						Period_cnt = 0;                     
						Period_cnt1 = 0;                    
						Period_cnt2 = 0;                      
						__HAL_TIM_SET_CAPTUREPOLARITY(&htim1,TIM_CHANNEL_4,TIM_INPUTCHANNELPOLARITY_FALLING);
						ic_flag = 1;						
						break;
					}
						case 1:							//二阶段第一次捕获到下降沿	
					{
						ccr1_cnt = __HAL_TIM_GET_COMPARE(&htim1,TIM_CHANNEL_4);
                        //获取CCR的值
						Period_cnt1 = 	Period_cnt;	
                        //获取计时器溢出次数1			
						__HAL_TIM_SET_CAPTUREPOLARITY(&htim1,TIM_CHANNEL_4,TIM_INPUTCHANNELPOLARITY_RISING);
                         //设置成上升沿捕获
						ic_flag = 2;							
						break;
					}
					case 2:		//阶段3	第二次捕获到上升沿					
					{
						ccr2_cnt = __HAL_TIM_GET_COMPARE(&htim1,TIM_CHANNEL_4);
                          //获取CCR2
						Period_cnt2 = Period_cnt;
                         //获取计时器溢出次数2		
						ic_flag = 0; //捕获设置为等待第一阶段						
						end_flag = 1;//完成一次捕获，将标志置1			
						break;
					}			
				}
			}
		}
}
	
