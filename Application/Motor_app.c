#include "stm32f10x.h"
#include "Motor.h"
extern int16_t turn_value;
int16_t base_speed;
void Motor_App_Init(void)
{
    Motor_Init();
}

/*
 * turn_value > 0 => ×ó×ª£¨×óÂÖÂı£©
 * turn_value < 0 => ÓÒ×ª£¨ÓÒÂÖÂı£©
 */
void Motor_App_Task(void)
{
    int16_t leftSpeed  = base_speed + turn_value;
    int16_t rightSpeed = base_speed - turn_value;
	
    if (leftSpeed > 1000) leftSpeed = 1000;
    if (rightSpeed > 1000) rightSpeed = 1000;
    if (leftSpeed < -1000) leftSpeed = -1000;
    if (rightSpeed < -1000) rightSpeed = -1000;

    Motor_SetSpeed(leftSpeed, rightSpeed);
}

