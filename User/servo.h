#ifndef __SERVO_H
#define __SERVO_H

#include "stm32f10x.h"

/* 舵机引脚定义 - 使用TIM2_CH1 (PA0) */
#define SERVO_TIM           TIM2
#define SERVO_TIM_CLK       RCC_APB1Periph_TIM2
#define SERVO_GPIO_PORT     GPIOA
#define SERVO_GPIO_PIN      GPIO_Pin_0
#define SERVO_GPIO_CLK      RCC_APB2Periph_GPIOA
#define SERVO_CHANNEL       1

/* 舵机角度范围 */
#define SERVO_ANGLE_MIN     0
#define SERVO_ANGLE_MAX     180

/* 函数声明 */
void Servo_Init(void);
void Servo_SetAngle(uint8_t angle);

#endif /* __SERVO_H */
