/**
 ******************************************************************************
 * @file    main.c
 * @brief   STM32F103C8 智能车主程序
 * @note    功能模块: LED亮灯 + OLED显示
 ******************************************************************************
 */

#include "stm32f10x.h"
#include "led.h"
#include "oled.h"
#include "delay.h"

int main(void)
{
    uint8_t cnt = 0;

    /* 初始化延时模块 */
    Delay_Init();

    /* 初始化LED */
    LED_Init();

    /* 初始化OLED显示屏 */
    OLED_Init();

    /* OLED显示开机信息 */
    OLED_ShowString(0, 0, "STM32 Car Ready!");
    OLED_ShowString(0, 2, "LED: OK");
    OLED_ShowString(0, 3, "OLED: OK");
    OLED_ShowString(0, 6, "Count:");

    while (1) {
        /* LED闪烁 */
        LED_Toggle();

        /* OLED显示计数器 */
        OLED_ShowNum(48, 6, cnt, 3);
        cnt++;

        /* 延时500ms */
        Delay_ms(500);
    }
}
