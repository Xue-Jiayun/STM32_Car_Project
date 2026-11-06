#ifndef __OLED_H
#define __OLED_H

#include "stm32f10x.h"

/* OLED引脚定义 - I2C软件模拟方式 */
#define OLED_SCL_PORT      GPIOB
#define OLED_SCL_PIN       GPIO_Pin_6
#define OLED_SDA_PORT      GPIOB
#define OLED_SDA_PIN       GPIO_Pin_7
#define OLED_GPIO_CLK      RCC_APB2Periph_GPIOB

/* OLED地址 */
#define OLED_ADDRESS       0x78

/* 函数声明 */
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DisplayOn(void);
void OLED_DisplayOff(void);
void OLED_SetCursor(uint8_t x, uint8_t y);
void OLED_ShowChar(uint8_t x, uint8_t y, char ch);
void OLED_ShowString(uint8_t x, uint8_t y, const char *str);
void OLED_ShowNum(uint8_t x, uint8_t y, uint32_t num, uint8_t len);

#endif /* __OLED_H */
