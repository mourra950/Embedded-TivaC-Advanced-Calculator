#include "DIO.h"
void DIO_Init_port (uint32 portbase,uint8 cr,uint8 pd,uint8 pur,uint8 pdr)
{
  //LOCK key
  (*((volatile unsigned long *)(portbase+0x520U))) = GPIO_LOCK_KEY;
  //commit registry
  (*((volatile unsigned long *)(portbase+0x524U))) = cr;
  //port direction
  (*((volatile unsigned long *)(portbase+0x400U))) = pd; 
  //pull up resistor
  (*((volatile unsigned long *)(portbase+0x510U))) = pur;
  //pull down resistor
  (*((volatile unsigned long *)(portbase+0x514U))) = pdr;
  //digital enabler
  (*((volatile unsigned long *)(portbase+0x51CU)))= cr;
}


void DIO_WritePort(uint32 portbase, uint8 value)
{
  (*((volatile unsigned long *)(portbase)))=value;
}

void DIO_WritePin (uint32 port_num, uint8 pin_num, uint8 value)
{
  if (value == LOGIC_HIGH)
    SET_BIT((*((volatile unsigned long *)(port_num))),pin_num);
  else
    CLEAR_BIT((*((volatile unsigned long *)(port_num))),pin_num);
}


uint8 DIO_ReadPin (uint32 port_num, uint8 pin_num)
{
  return GET_BIT((*((volatile unsigned long *)(port_num))),pin_num);
  
}

uint8 DIO_ReadPort (uint32 port_num) 
{
  return (*((volatile unsigned long *)(port_num)));
  
}
