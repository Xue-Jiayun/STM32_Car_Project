#include "servo.h"
#include "stm32f10x.h"

/**
 * @brief  舵机初始化 - 配置TIM2_CH1输出PWM
 * @note   舵机要求50Hz PWM信号(20ms周期)
 *         控制脉冲宽度 0.5ms~2.5ms 对应 0~180度
 *
 *         TIM2配置:
 *         时钟源 = 72MHz (APB1 x2)
 *         预分频 = 72-1 → 计数频率 = 1MHz (1us/tick)
 *         自动重装载 = 20000-1 → 周期 = 20ms = 50Hz
 *         CCR范围: 500~2500 → 0.5ms~2.5ms → 0~180度
 */
void Servo_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

    /* 使能时钟 */
    RCC_APB1PeriphClockCmd(SERVO_TIM_CLK, ENABLE);
    RCC_APB2PeriphClockCmd(SERVO_GPIO_CLK, ENABLE);

    /* 配置PA0为复用推挽输出 */
    GPIO_InitStructure.GPIO_Pin = SERVO_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SERVO_GPIO_PORT, &GPIO_InitStructure);

    /* 配置TIM时基 */
    TIM_TimeBaseStructure.TIM_Period = 20000 - 1;        /* 20ms周期 → 50Hz */
    TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1;        /* 72MHz/72 = 1MHz, 1us/tick */
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(SERVO_TIM, &TIM_TimeBaseStructure);

    /* 配置PWM输出通道 */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 1500;                 /* 初始角度: 90度 (1.5ms) */
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

#if SERVO_CHANNEL == 1
    TIM_OC1Init(SERVO_TIM, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(SERVO_TIM, TIM_OCPreload_Enable);
#elif SERVO_CHANNEL == 2
    TIM_OC2Init(SERVO_TIM, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(SERVO_TIM, TIM_OCPreload_Enable);
#elif SERVO_CHANNEL == 3
    TIM_OC3Init(SERVO_TIM, &TIM_OCInitStructure);
    TIM_OC3PreloadConfig(SERVO_TIM, TIM_OCPreload_Enable);
#elif SERVO_CHANNEL == 4
    TIM_OC4Init(SERVO_TIM, &TIM_OCInitStructure);
    TIM_OC4PreloadConfig(SERVO_TIM, TIM_OCPreload_Enable);
#endif

    /* 使能TIM预装载寄存器 */
    TIM_ARRPreloadConfig(SERVO_TIM, ENABLE);

    /* 启动定时器 */
    TIM_Cmd(SERVO_TIM, ENABLE);
}

/**
 * @brief  设置舵机角度
 * @param  angle: 0~180度
 *         公式: CCR = 500 + (angle / 180.0) * 2000
 *         0度 → 500 (0.5ms)
 *         90度 → 1500 (1.5ms)
 *         180度 → 2500 (2.5ms)
 */
void Servo_SetAngle(uint8_t angle)
{
    uint16_t ccr;

    if (angle < SERVO_ANGLE_MIN)
        angle = SERVO_ANGLE_MIN;
    if (angle > SERVO_ANGLE_MAX)
        angle = SERVO_ANGLE_MAX;

    /* 角度转PWM比较值 */
    ccr = (uint16_t)(500 + ((uint32_t)angle * 2000 / 180));

#if SERVO_CHANNEL == 1
    TIM_SetCompare1(SERVO_TIM, ccr);
#elif SERVO_CHANNEL == 2
    TIM_SetCompare2(SERVO_TIM, ccr);
#elif SERVO_CHANNEL == 3
    TIM_SetCompare3(SERVO_TIM, ccr);
#elif SERVO_CHANNEL == 4
    TIM_SetCompare4(SERVO_TIM, ccr);
#endif
}
