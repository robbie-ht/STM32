#include "sensor.h"

/*************************************
* 函数名称：SENSOR_GPIO_Config
* 函数功能：配置灰度传感器输入引脚
* 引脚分配：PA4 左外, PA5 左内, PA0 右内, PA1 右外
**************************************/
void Senser_Init(void)
{
     GPIO_InitTypeDef GPIO_InitStructure;

    /* 开启 GPIOA、GPIOB 时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);

    /* 配置 GPIOA */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  // 上拉输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* 配置 GPIOB */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  // 上拉输入
    GPIO_Init(GPIOB, &GPIO_InitStructure);

}

/*************************************
* 函数名称：SENSOR_ReadData
* 函数功能：读取4路灰度传感器信号
* 返回值：bit3~bit0 对应 L2,L1,R1,R2（左外到右外）
**************************************/
uint8_t Senser_ReadData(void)
{
    uint8_t value = 0;
    if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4)) value |= (1 << 0); // 左外
    if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5)) value |= (1 << 1); // 左内
    if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0)) value |= (1 << 3); // 右内
    if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1)) value |= (1 << 2); // 右外
    return value;
}
