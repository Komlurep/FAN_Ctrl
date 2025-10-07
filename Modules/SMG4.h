#ifndef __SMG4_H
#define __SMG4_H

#include "main.h"
#include "gpio.h"



//#define SER_Pin GPIO_PIN_8
//#define SER_GPIO_Port GPIOC
//#define DISEN_Pin GPIO_PIN_9
//#define DISEN_GPIO_Port GPIOC
//#define DISLK_Pin GPIO_PIN_8
//#define DISLK_GPIO_Port GPIOA
//#define SCK_Pin GPIO_PIN_11
//#define SCK_GPIO_Port GPIOA
//#define A3_Pin GPIO_PIN_12
//#define A3_GPIO_Port GPIOA
//#define A0_Pin GPIO_PIN_15
//#define A0_GPIO_Port GPIOA
//#define A1_Pin GPIO_PIN_10
//#define A1_GPIO_Port GPIOC
//#define A2_Pin GPIO_PIN_11
//#define A2_GPIO_Port GPIOC

#define BLANK_CODE 0xFF // 定义一个特殊的熄灭码

void Write595(uint8_t sel, uint8_t num, uint8_t bdot);
void UpdateDisplayBuffer(uint16_t number);
void flashSMG(void);



#endif
