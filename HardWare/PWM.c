#include "pwm.h"

void PWM_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_BaseInit;
    TIM_OCInitTypeDef TIM_OCInit;

    /* 开启时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO | RCC_APB2Periph_TIM1, ENABLE);

    /* PWM 引脚配置：PA8 (CH1), PA11 (CH4) */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  // 复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* TIM1 基本配置 */
    TIM_BaseInit.TIM_Period = 1000 - 1;      // PWM周期（1kHz）
    TIM_BaseInit.TIM_Prescaler = 72 - 1;     // 1MHz时基
    TIM_BaseInit.TIM_ClockDivision = 0;
    TIM_BaseInit.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM1, &TIM_BaseInit);

    /* PWM 模式配置 (CH1 -> PWMB, CH4 -> PWMA) */
    TIM_OCInit.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInit.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInit.TIM_OCPolarity = TIM_OCPolarity_High;

    // CH1 - PWMB
    TIM_OCInit.TIM_Pulse = 0;
    TIM_OC1Init(TIM1, &TIM_OCInit);
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);

    // CH4 - PWMA
    TIM_OCInit.TIM_Pulse = 0;
    TIM_OC4Init(TIM1, &TIM_OCInit);
    TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);

    TIM_ARRPreloadConfig(TIM1, ENABLE);
    TIM_CtrlPWMOutputs(TIM1, ENABLE);
    TIM_Cmd(TIM1, ENABLE);
}

void PWM_SetCompare1(uint16_t value)
{
    TIM_SetCompare1(TIM1, value);
}

void PWM_SetCompare4(uint16_t value)
{
    TIM_SetCompare4(TIM1, value);
}
