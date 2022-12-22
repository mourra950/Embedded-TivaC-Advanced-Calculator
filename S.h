#ifndef S_H_
#define S_H_
#include "types.h"

void SysTickDisable(void);
void SysTickEnable(void);
uint32 SysTickPeriodGet(void);
void SysTickPeriodSet(uint32 ui32Period);
uint32 SysTickValueGet(void);
boolean SysTick_Is_Time_out(void);
#endif