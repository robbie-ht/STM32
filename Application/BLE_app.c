#include "stm32f10x.h"                  // Device header
#include "BLE.h"
#include "track_app.h"
//#include "OLED.h"
#include <stdlib.h>
#include "string.h"
extern int16_t base_speed;
int bstime = 5;
float tvtime = 3.5 ;
void BLE_App_Init()
{
	Ble_Init();
	Ble_SendString("Ready!");
}
void BLE_App_Task()
{

	if (Ble_RxFlag == 1)
		{
//			OLED_ShowString(1,1,Ble_RxPacket);
			char *Tag = strtok(Ble_RxPacket, ",");
			if (strcmp(Tag, "joystick") == 0)
				{
					int8_t LH = atoi(strtok(NULL, ","));
					int8_t LV = atoi(strtok(NULL, ","));
					int8_t RH = atoi(strtok(NULL, ","));
					int8_t RV = atoi(strtok(NULL, ","));
					base_speed = LV * bstime;
					turn_value = RH * tvtime;
//					OLED_ShowNum(3,1,base_speed,6);
				}
			if (strcmp(Tag, "slider") == 0)
				{
					int8_t type = atoi(strtok(NULL, ","));
					int8_t value = atof(strtok(NULL, ","));
					switch (type)
					{
						case 1: bstime = value;break;
						case 2: tvtime = value;break;
						default : break;
					}
				}
					
			Ble_RxFlag = 0;
		}
	if (bstime > 10)
	{
		bstime =10;
	}
	if (tvtime >10)
	{
		tvtime =10;
	}
}


