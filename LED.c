#include "LED.h"
#include "tm4c123gh6pm.h"
#include "DIO.h"

void LED_init()
{
  SYSCTL_RCGCGPIO_R|=0x20;
  GPIO_PORTF_DATA_R=0x00U;
}

void ChangeLEDcolor(LED_Color color)
{
   DIO_WritePort((PORTFBase+0x3FC),color);
}