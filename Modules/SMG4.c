/*
 * @Author: Komlurep 123731537+Komlurep@users.noreply.github.com
 * @Date: 2025-10-05 23:07:32
 * @LastEditors: Komlurep 123731537+Komlurep@users.noreply.github.com
 * @LastEditTime: 2025-10-07 14:28:32
 * @FilePath: \FAN_Ctrl\Modules\SMG4.c
 * @Description: 4位数码管显示驱动
 */

#include "SMG4.h"

uint8_t g_display_digits[4] = {0, 0, 0, 0}; // 显示缓冲区，初始全为1
uint8_t g_digit_index = 0; // 当前刷新的位索引



void Write595(uint8_t sel, uint8_t num, uint8_t bdot)
{
    // 共阴数码管段码表
    static const uint8_t TAB[16] = {
        0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 
        0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71
    };
    
    // 先关闭所有位选（根据你的硬件，A3可能控制总使能）
    HAL_GPIO_WritePin(A3_GPIO_Port, A3_Pin, GPIO_PIN_RESET);
    
    uint8_t dat;
    // 判断是否需要熄灭该位数码管
    if (num == BLANK_CODE) {
        dat = 0x00; // 发送全0，共阴数码管所有段都不亮
    } else {
        dat = TAB[num & 0x0F] | (bdot ? 0x80 : 0x00); // 正常显示数字，并处理小数点
    }
    
    // 将数据移位输出到74HC595
    uint8_t i;
    for (i = 0; i < 8; ++i) {
        HAL_GPIO_WritePin(SCK_GPIO_Port, SCK_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(SER_GPIO_Port, SER_Pin, (dat & 0x80) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        dat <<= 1;
        HAL_GPIO_WritePin(SCK_GPIO_Port, SCK_Pin, GPIO_PIN_SET);
    }
    
    // 锁存数据，使输出生效
    HAL_GPIO_WritePin(DISLK_GPIO_Port, DISLK_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DISLK_GPIO_Port, DISLK_Pin, GPIO_PIN_SET);
    
    // 控制74HC138译码器进行位选
    HAL_GPIO_WritePin(A0_GPIO_Port, A0_Pin, (sel & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(A1_GPIO_Port, A1_Pin, (sel & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(A2_GPIO_Port, A2_Pin, GPIO_PIN_RESET); 
    HAL_GPIO_WritePin(A3_GPIO_Port, A3_Pin, GPIO_PIN_SET);   
}



/**
  * @brief  更新显示缓冲区
  * @param  number: 要显示的4位数 (0-9999)
  * @param  dotPos: 小数点位置 (0-3, 0xFF表示无小数点)
  * @retval None
  */
void UpdateDisplayBuffer(uint16_t number) {
    /* 分解数字到缓冲区 */
    g_display_digits[0] = number / 1000;          // 千位
    g_display_digits[1] = (number / 100) % 10;     // 百位
    g_display_digits[2] = (number / 10) % 10;      // 十位
    g_display_digits[3] = number % 10;             // 个位

		/* 处理前导零：如果千位为0，则熄灭它 */
    if (g_display_digits[0] == 0) {
        g_display_digits[0] = BLANK_CODE; // 用特殊值表示熄灭
        
        /* 可选：如果百位也是0，且数字小于100，则也熄灭百位 */
        if (number < 100 && g_display_digits[1] == 0) {
            g_display_digits[1] = BLANK_CODE;
            
            /* 可选：如果十位也是0，且数字小于10，则也熄灭十位 */
            if (number < 10 && g_display_digits[2] == 0) {
                g_display_digits[2] = BLANK_CODE;
            }
        }
    }
}


void flashSMG(void)
{
	HAL_GPIO_WritePin(A3_GPIO_Port, A3_Pin, GPIO_PIN_RESET);
        
        // 刷新当前位
        Write595(g_digit_index, g_display_digits[g_digit_index], 0);
        
	
        // 移动到下一位，实现循环扫描
        g_digit_index++;
        if (g_digit_index >= 4) {
            g_digit_index = 0; 
				}
}

