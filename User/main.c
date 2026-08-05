#include "stm32f10x.h"
#include "Motor_app.h"
#include "track_app.h"
#include "BLE_app.h"
#include "delay.h"
#include "OLED.h"
extern uint16_t base_speed;
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//	  OLED_Init();
    delay_init();        // 初始化延时函数（必须）
//    Track_App_Init();    // 初始化灰度传感器模块
    Motor_App_Init();    // 初始化电机模块
	BLE_App_Init();
	OLED_Clear();
	
    while (1)
    {
		BLE_App_Task();
//		  OLED_ShowNum(2,1,turn_value,4);
//        Track_App_Task();   // 更新turn_value
		Motor_App_Task();   // 控制电机
		delay_ms(10);       // 稍微延时
    }
}
