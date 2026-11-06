/**
 ******************************************************************************
 * @file    main.c
 * @brief   STM32F103C8 智能车主程序
 * @note    功能模块: LED亮灯 + OLED显示 + 舵机控制
 ******************************************************************************
 */

#include "stm32f10x.h"
#include "led.h"
#include "oled.h"
#include "servo.h"
#include "delay.h"

int main(void)
{
    uint8_t angle = 0;
    uint8_t dir = 1;

    /* 初始化延时模块 */
    Delay_Init();

    /* 初始化LED */
    LED_Init();

    /* 初始化OLED显示屏 */
    OLED_Init();

    /* 初始化舵机 */
    Servo_Init();

    /* OLED显示开机信息 */
    OLED_ShowString(0, 0, "STM32 Car Ready!");
    OLED_ShowString(0, 2, "LED: OK");
    OLED_ShowString(0, 3, "OLED: OK");
    OLED_ShowString(0, 4, "Servo: OK");
    OLED_ShowString(0, 6, "Angle:");

    while (1) {
        /* LED闪烁 */
        LED_Toggle();

        /* 舵机扫描 0~180~0 */
        Servo_SetAngle(angle);

        /* OLED显示当前角度 */
        OLED_ShowNum(48, 6, angle, 3);

        /* 角度递增/递减 */
        if (dir) {
            angle += 5;
            if (angle >= 180) {
                angle = 180;
                dir = 0;
            }
        } else {
            if (angle <= 5) {
                angle = 0;
                dir = 1;
            } else {
                angle -= 5;
            }
        }

        /* 延时200ms */
        Delay_ms(200);
    }
}
