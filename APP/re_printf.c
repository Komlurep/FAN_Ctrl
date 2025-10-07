/*
 * @Author: Komlurep 123731537+Komlurep@users.noreply.github.com
 * @Date: 2025-10-05 23:07:30
 * @LastEditors: Komlurep 123731537+Komlurep@users.noreply.github.com
 * @LastEditTime: 2025-10-07 14:29:29
 * @FilePath: \FAN_Ctrl\APP\re_printf.c
 * @Description: 重构printf
 */

#include "re_printf.h"


// 重写fputc函数
int fputc(int ch, FILE *f) {
    // 发送一个字符
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    return ch; // 返回写入的字符
}
