#include "track_app.h"
#include "sensor.h"
//#include "OLED.h"
int16_t turn_value = 0;
static int16_t last_turn_value = 0;
void Track_App_Init(void)
{
    Senser_Init();
}

/*
 * turn_value > 0 ：左偏，需左转
 * turn_value < 0 ：右偏，需右转
 */
void Track_App_Task(void)
{
    uint8_t sensor = Senser_ReadData();
													 // 模块输出逻辑反转：黑线=1 → 白底=0
    sensor = ~sensor & 0x0F; 						 // 只保留低4位反转结果
//	char bin_str[5];                                                            //debug代码,用来显示循迹模块输入结果
//	for (int i = 0; i < 4; i++)
//	{
//		bin_str[i] = (sensor & (1 << (3 - i))) ? '1' : '0';
//	}
//	bin_str[4] = '\0';  							 // 结束符
//	OLED_ShowString(1, 1, bin_str);

  /*
       bit3 bit2 bit1 bit0
       L2  L1  R1  R2
       黑线=1 白底=0
  */
switch (sensor)
    {
        case 0b0110: turn_value = 0;  break;
		case 0b0010: turn_value = 23; break;
		case 0b0001: turn_value = 45; break;
		case 0b0100: turn_value = -23;break;
		case 0b1000: turn_value = -45;break;
		case 0b1111: turn_value = 0;  break;
		case 0b0000: 
            if (last_turn_value > 0)
					turn_value = 35;                      // 向左微调找线
            else if (last_turn_value < 0)
					turn_value = -35;                     // 向右微调找线
            else
					turn_value = 0;                       // 初始直行
            break;
		default:turn_value = last_turn_value;break;
    }

last_turn_value = turn_value;
}
