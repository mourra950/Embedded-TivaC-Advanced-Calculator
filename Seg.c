#include "tm4c123gh6pm.h"
#include "Seg.h"
uint8 arr[3][3]={{0x06,0x5b,0x4f},{0x66,0x6d,0x7d},{0x07,0x7f,0x6f}};
void Seg_init()
{

    SYSCTL_RCGCGPIO_R|=0x02;
    (*((volatile unsigned long *)(SegPort + 0x520U))) = GPIO_LOCK_KEY;
    // commit registry
    (*((volatile unsigned long *)(SegPort + 0x524U))) = 0xFF;
    // port direction
    (*((volatile unsigned long *)(SegPort + 0x400U))) = 0xFF;
    // pull up 
    (*((volatile unsigned long *)(SegPort + 0x510U))) = 0xFF;
    // digital enabler
    (*((volatile unsigned long *)(SegPort + 0x51CU))) = 0xFF;
    
}

void Seg_Write(uint8 value)
{
  uint8 num=0,num1=1;
  if(value==1)
  {
    num=0;
    num1=0;
  }
  else if(value==2)
  {
    num=0;
    num1=1;
  }
  else if(value==3)
  {
    num=0;
    num1=2;
  }
  else if(value==4)
  {
    num=1;
    num1=0;
  }
  else if(value==5)
  {
    num=1;
    num1=1;
  }
  else if(value==6)
  {
    num=1;
    num1=2;
  }
  else if(value==7)
  {
    num=2;
    num1=0;
  }
  else if(value==8)
  {
    num=2;
    num1=1;
  }else if(value==9)
  {
    num=2;
    num1=2;
  }
    (*((volatile unsigned long *)(SegPort+0x3fc))) =arr[num][num1];
}

