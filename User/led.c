#include "led.h"
#include "stm32f10x.h"

/**
 * @brief  LED初始化 - 配置GPIO为推挽输出
 * @note   STM32F103C8 标准库方式配置GPIO
 */
void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* 使能GPIO时钟 */
    RCC_APB2PeriphClockCmd(LED_GPIO_CLK, ENABLE);

    /* 配置GPIO为推挽输出模式，50MHz */
    GPIO_InitStructure.GPIO_Pin = LED_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);

    /* 初始状态：LED熄灭 */
    LED_Off();
}

/**
 * @brief  点亮LED
 */
void LED_On(void)
{
    GPIO_SetBits(LED_GPIO_PORT, LED_GPIO_PIN);
}

/**
 * @brief  熄灭LED
 */
void LED_Off(void)
{
    GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN);
}

/**
 * @brief  翻转LED状态
 */
void LED_Toggle(void)
{
    if (GPIO_ReadOutputDataBit(LED_GPIO_PORT, LED_GPIO_PIN)) {
        LED_Off();
    } else {
        LED_On();
    }
}

/**
 * @brief  LED闪烁
 * @param  period_ms: 闪烁周期(粗略延时，基于SysTick)
 */
void LED_Blink(uint32_t period_ms)
{
    LED_On();
    Delay_ms(period_ms);
    LED_Off();
    Delay_ms(period_ms);
}
