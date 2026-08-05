#include "PWM.h"

void Motor_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* 开启控制引脚时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    /* 控制引脚配置 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // 推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* 初始化PWM模块 */
    PWM_Init();

    /* 默认关闭电机 */
    GPIO_ResetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
}

void Motor_SetSpeed(int16_t leftSpeed, int16_t rightSpeed)
{
    /* 左电机方向控制 (AIN1, AIN2) */
    if (leftSpeed >= 0) {
        GPIO_SetBits(GPIOB, GPIO_Pin_13);
        GPIO_ResetBits(GPIOB, GPIO_Pin_12);
    } else {
        GPIO_SetBits(GPIOB, GPIO_Pin_12);
        GPIO_ResetBits(GPIOB, GPIO_Pin_13);
        leftSpeed = -leftSpeed;
    }

    /* 右电机方向控制 (BIN1, BIN2) */
    if (rightSpeed >= 0) {
        GPIO_ResetBits(GPIOB, GPIO_Pin_15);
        GPIO_SetBits(GPIOB, GPIO_Pin_14);
    } else {
        GPIO_ResetBits(GPIOB, GPIO_Pin_14);
        GPIO_SetBits(GPIOB, GPIO_Pin_15);
        rightSpeed = -rightSpeed;
    }

    /* 限幅处理 */
    if (leftSpeed > 1000) leftSpeed = 1000;
    if (rightSpeed > 1000) rightSpeed = 1000;

    PWM_SetCompare4(leftSpeed);  // PWMA
    PWM_SetCompare1(rightSpeed); // PWMB
}
