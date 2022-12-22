
#include "KEYPAD.h"
uint8 array1[4][4]={{'1','2','3','+'},
{'4','5','6','-'},
{'7','8','9','/'},
{'*','0','#','='}};
void KEYPAD_init()
{
  SYSCTL_RCGCGPIO_R|=0x14;
  DIO_Init_port(PORTCOL,0xF0,0x00,0xF0,0x00);
  DIO_Init_port(PORTROW,0x0F,0x0F,0x00,0x00);
}
void delay3(int delay)
{
  
  for (int i = 0;i<delay;i++)
    for(int j = 0;j<delay;j++);
}

uint8 KEYPAD_READ()
{
  for(int i =0;i<4;i++)
  {
    (*((volatile unsigned long *)(PORTROW + 0x3FCU))) = ~(1<<i);
    for (int j=0;j<4;j++)
    {
      if(BIT_IS_CLEAR(GPIO_PORTC_DATA_R,j+4))
      {
        delay3(100);
        while(BIT_IS_CLEAR(GPIO_PORTC_DATA_R,j+4));
        return array1[i][j];
      }
    }
    
  }
  return 'T';
}
