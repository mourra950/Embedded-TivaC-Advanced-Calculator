#include "lcd.h"


int d=50;
void delay(int delay)
{
  
  for (int i =0;i<delay;i++)
    for(int j=0;j<delay;j++);
  
}

void LCD_init()
{
  SYSCTL_RCGCGPIO_R |= 0x03;
  DIO_Init_port(DataPortBase, 0xFF, 0xFF, 0x00, 0x00);
  DIO_Init_port(ModePortBase, 0xFF, 0xFF, 0x00, 0x00);
  LCD_Command(Display_On_Cursor_Off);
  LCD_clear_screen();
  LCD_Command(ACTIVATE_SECOND_LINE);
  LCD_Command(Display_On_Cursor_Blinking_Off);
}

void LCD_Command(LCD_COMMANDS Command)
{
  delay(d);
  DIO_WritePin(ModePort, 7, LOGIC_LOW);  
  delay(d);
  DIO_WritePin(ModePort, 6, LOGIC_HIGH);
  delay(d);
  DIO_WritePort(DataPort, Command);
  delay(d);
  DIO_WritePin(ModePort, 6, LOGIC_LOW);
}
void LCD_Data(uint8 Data)
{
  delay(d);
  DIO_WritePin(ModePort, 7, LOGIC_HIGH);  // see here
  delay(d);
  DIO_WritePin(ModePort, 6, LOGIC_HIGH);
  delay(d);
  DIO_WritePort(DataPort, Data);
  delay(d);
  DIO_WritePin(ModePort, 6, LOGIC_LOW);
}

void LCD_Displaystring(const char *Str)
{
  uint8 i = 0;
  while(Str[i] != '\0')
  {       
    if(i==16)
      LCD_Command(Begin_At_Second);
    LCD_Data(Str[i]);
    i++;
  }
  
}
void LCD_Intgertostring(int Data,char *string)
{
  snprintf(string, 16, "%d", Data);
}

void LCD_clear_screen(void){
  LCD_Command(CLEAR_DISPLAY); 
  
}
