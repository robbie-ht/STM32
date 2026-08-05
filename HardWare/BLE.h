#ifndef __SERIAL_H
#define __SERIAL_H

#include <stdio.h>

extern char Ble_RxPacket[];
extern uint8_t Ble_RxFlag;

void Ble_Init(void);
void Ble_SendByte(uint8_t Byte);
void Ble_SendArray(uint8_t *Array, uint16_t Length);
void Ble_SendString(char *String);
void Ble_SendNumber(uint32_t Number, uint8_t Length);
void Ble_Printf(char *format, ...);

#endif
