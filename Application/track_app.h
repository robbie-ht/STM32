#ifndef __TRACK_APP_H
#define __TRACK_APP_H

#include "stm32f10x.h"

extern int16_t turn_value;

void Track_App_Init(void);
void Track_App_Task(void);

#endif
