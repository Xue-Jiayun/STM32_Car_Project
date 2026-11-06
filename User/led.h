#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"

/* LED引脚定义 - 根据实际硬件修改 */
#define LED_GPIO_PORT       GPIOA
#define LED_GPIO_PIN        GPIO_Pin_8
#define LED_GPIO_CLK        RCC_APB2Periph_GPIOA

/* 函数声明 */
void LED_Init(void);
void LED_On(void);
void LED_Off(void);
void LED_Toggle(void);
void LED_Blink(uint32_t period_ms);

#endif /* __LED_H */
