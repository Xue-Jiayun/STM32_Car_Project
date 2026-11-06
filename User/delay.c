#include "delay.h"
#include "stm32f10x.h"

static uint8_t  fac_us = 0;
static uint16_t fac_ms = 0;

/**
 * @brief  延时初始化 - 配置SysTick
 * @note   SysTick时钟源为系统时钟的1/8 (72MHz/8 = 9MHz)
 */
void Delay_Init(void)
{
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
    fac_us = SystemCoreClock / 8000000;       /* 9 */
    fac_ms = (uint16_t)fac_us * 1000;          /* 9000 */
}

/**
 * @brief  微秒级延时
 * @param  us: 延时微秒数
 */
void Delay_us(uint32_t us)
{
    uint32_t temp;
    SysTick->LOAD = us * fac_us;
    SysTick->VAL = 0x00;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
    do {
        temp = SysTick->CTRL;
    } while ((temp & 0x01) && !(temp & (1 << 16)));
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    SysTick->VAL = 0x00;
}

/**
 * @brief  毫秒级延时
 * @param  ms: 延时毫秒数
 */
void Delay_ms(uint32_t ms)
{
    uint32_t temp;
    while (ms--) {
        SysTick->LOAD = (uint32_t)fac_ms;
        SysTick->VAL = 0x00;
        SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
        do {
            temp = SysTick->CTRL;
        } while ((temp & 0x01) && !(temp & (1 << 16)));
        SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
        SysTick->VAL = 0x00;
    }
}
