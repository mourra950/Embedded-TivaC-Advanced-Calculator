#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "DIO.h"
#include "tm4c123gh6pm.h"
//commands for the LCD from the datasheet
typedef enum
{   
  CLEAR_DISPLAY = 0x01,
  RETURN_HOME = 0x02,
  CURSOR_LEFT = 0x04,
  SHIFT_RIGHT = 0x05,
  CURSOR_RIGHT = 0x06,
  SHIFT_LEFT = 0x07,
  Display_Off_Cursor_Off=0x08,
  LCD_ON_CURSOR_ON = 0x0F,
  Display_On_Cursor_Off=0x0C,
  Display_On_Cursor_Blinking_Off=0x0E,
  Display_On_Cursor_Blinking_On=0x0F,
  FORCE_AT_BEGIN = 0x80,
  TWO_LINES5x7 = 0x38,
  ACTIVATE_SECOND_LINE = 0x3C,
  Begin_At_First=0x80,
  Begin_At_Second=0xC0
} LCD_COMMANDS;
// for data from d0 to d7 in the lcd display
#define DataPortBase PORTBBase  
//mode and enable
#define ModePortBase PORTABase  
// for data from d0 to d7 in the lcd display
#define DataPort DataPortBase+0x3fc  
//mode and enable
#define ModePort ModePortBase+0x3fc  
//function to initialize the lcd
void LCD_init();
//function to excute commands
void LCD_Command(LCD_COMMANDS Command);
//function to print one character
void LCD_Data(uint8 Data);
//function used to print strings by sending one character by time to print one after another after 15 char the lcd goes to the second line auto
void LCD_Displaystring(const char *Str);
//to clear the display
void LCD_clear_screen(void);