#include "S.h"
#include "tm4c123gh6pm.h"
#include "types.h"
#include "bitwise_operation.h"
#include <stdbool.h>
void SysTickDisable(void)
{
  NVIC_ST_CTRL_R =0;
  
}
void SysTickEnable(void)
{
  NVIC_ST_CTRL_R|=0x5;
}

uint32 SysTickPeriodGet(void)
{
  return NVIC_ST_RELOAD_R;
}
void SysTickPeriodSet(uint32 ui32Period)
{
    NVIC_ST_RELOAD_R =ui32Period;
}
uint32 SysTickValueGet(void)
{
    return NVIC_ST_CURRENT_R;
}
boolean SysTick_Is_Time_out(void)
{
  
  if(BIT_IS_SET(NVIC_ST_CTRL_R ,16) )
  {
    return FALSE;
  }
  return TRUE;
}