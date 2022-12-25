#include "main.h"

int mode = 0;
int Stop_sec;
uint8 Stop__mode = 0x00;
int Timer_sec;
int Timer_Count = 0;
int st = 0;
uint8 Timer_c = '0';
uint8 Timer__mode = 0x00;
uint8 a;

void Timer_LCD()
{
  int m, s;
  m = (Timer_sec) / 60;
  s = (Timer_sec - (m * 60));
  uint8 str[32];
  snprintf(str, 32, "%02d:%02d", m, s);
  LCD_clear_screen();
  LCD_Displaystring("Timer Mode");
  LCD_Command(Begin_At_Second);
  LCD_Displaystring(str);
}
void Stop_LCD()
{
  int m, s;
  m = (Stop_sec) / 60;
  s = (Stop_sec - (m * 60));
  uint8 str[32];
  snprintf(str, 32, "%02d:%02d", m, s);
  LCD_clear_screen();
  LCD_Displaystring("Stop Mode");
  LCD_Command(Begin_At_Second);
  LCD_Displaystring(str);
}
void Timer_Display(void)
{
  
  Timer_sec--;
  if(Timer_sec <= 0)
  {
    Timer_sec=0;
    if (st == 0)
    {
      Timer_c = '0';
      Timer_Count = 0;
      Timer__mode = 0x00;
      Toggle_LED();
      st++;
      
    }
    else if(st==1)
    {
      TimerDisable(TIMER0_BASE, TIMER_BOTH);
      Timer__mode = 0x0;
      Toggle_LED();
      st = 0;  
    }
  }
  
}
void Stop_Display(void)
{
  Stop_sec++;
}

void TimerHandler(void)
{
  TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
  Timer_Display();
}

void delay2(int delay)
{
  
  for (int i = 0; i < delay; i++)
    for (int j = 0; j < delay; j++)
      ;
}

void Toggle_LED()
{
  
  if (st==0)
  {
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x02);
  }
  else if(st==1)
  {
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x00);
  }
  
}

void Timer_init(void)
{
  SysTickDisable();
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
  TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
  TimerLoadSet(TIMER0_BASE, TIMER_A, 16000000 - 1);
  SysTickPeriodSet(16000000 - 1);
  IntRegister(INT_TIMER0A, TimerHandler);
  SysTickIntRegister(Stop_Display);
}

void Timer_enable(void)
{
  TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
  
  IntEnable(INT_TIMER0A);
  
  IntMasterEnable();
}

void Calculator(void)
{
  uint8 Calc_var1[8] = "";
  uint8 Calc_var2[8] = "";
  uint8 op;
  LCD_clear_screen();
  int count_var = 0;
  int count_len = 0;
  LCD_Displaystring("mode 1 Calc");
  LCD_Command(Begin_At_Second);
  while (mode == 1)
  {
    
    // read keypad
    a = KEYPAD_READ();
    // delay2(500);
    
    // getting the first number and waiting for the equal command to go to second phase
    
    if (count_var == 0)
    {
      if (isdigit(a) && count_var == 0)
      {
        if (count_len < 4)
        {
          LCD_Data(a);
          Calc_var1[count_len] = a;
          count_len++;
          // printf("%s",Calc_var1);
        }
      }
      else if ((strchr("+-/*", a) != NULL)&& count_len>0)
      {
        LCD_Data(a);
        op = a;
        count_len = 0;
        count_var++;
      }
    }
    // getting the second number and waiting for the equal command to go to third phase
    if (count_var == 1)
    {
      if (isdigit(a))
      {
        if (count_len < 4)
        {
          LCD_Data(a);
          Calc_var2[count_len] = a;
          count_len++;
        }
      }
      else if ((strchr("=", a) != NULL))
      {
        count_var++;
      }
    }
    // caculate final result and print
    if (count_var == 2)
    {
      int v1, v2, result;
      
      v1 = atoi(Calc_var1);
      v2 = atoi(Calc_var2);
      
      switch (op)
      {
      case '+':
        result = v1 + v2;
        break;
      case '-':
        result = v1 - v2;
        
        break;
      case '/':
        if(v2>0)
          result = v1 / v2;
        else
        {
          LCD_clear_screen();
          LCD_Displaystring("Error cant divide by zero");
          delay2(2000);
          return;
        }
        break;
      case '*':
        result = v1 * v2;
        break;
      }
      LCD_clear_screen();
      uint8 str[32];
      snprintf(str, 32, "the result is :\n%d ", result);
      LCD_Displaystring(str);
      count_var++;
    }
    
    if (count_var == 3)
    {
      if (a == '#')
      {
        return;
      }
    }
  }
}

void Timer_mode(void)
{
  Timer_LCD();
  while (mode == 2)
  {
    a = KEYPAD_READ();
    if (Timer_Count == 0)
    {
      if (isdigit(a))
      {
        
        switch (Timer_c)
        {
        case '0':
          Timer_sec = atoi(&a) * 60 * 10;
          Timer_c++;
          break;
        case '1':
          Timer_sec += atoi(&a) * 60;
          Timer_c++;
          break;
        case '2':
          Timer_sec += atoi(&a) * 10;
          Timer_c++;
          break;
        case '3':
          Timer_sec += atoi(&a);
          Timer_Count++;
          break;
        }
        Timer_LCD();
      }
    }
    if (Timer_Count == 1)
    {
      
      if ((strchr("#*", a) != NULL))
      {
        // reset
        if (a == '#')
        {
          Timer_c = '0';
          Timer_Count = 0;
          Timer__mode = 0x00;
          Timer_sec=0;
          TimerDisable(TIMER0_BASE, TIMER_BOTH);
          Timer_LCD();
        }
        else if (a == '*')
        {
          Timer__mode ^= 0x01;
          if (Timer__mode == 0x01)
          {
            
            TimerEnable(TIMER0_BASE, TIMER_BOTH);
          }
          else
          {
            
            TimerDisable(TIMER0_BASE, TIMER_BOTH);
          }
        }
      }
      }
    Timer_LCD();
  }
}
void Stop_mode(void)
{
  
  Stop_LCD();
  while (mode==0)
  {
    a = KEYPAD_READ();
    if ((strchr("#*", a) != NULL))
    {
      // reset
      if (a == '#')
      {
        
        Stop__mode = 0x00;
        Stop_sec = -1;
        Stop_Display();
        SysTickDisable();
      }
      else if (a == '*')
      {
        
        Stop__mode ^= 0x01;
        if (Stop__mode == 0x01)
        {
          SysTickEnable();
        }
        else
        {
          SysTickDisable();
        }
      }
    }
     Stop_LCD();
  }
}

void TivaIntButtons(void)
{
  DIO_Init_port(PORTFBase, 0x1F, 0x0E, 0x11, 0x00);
  GPIOIntRegister(GPIO_PORTF_BASE, Change_mode);
  GPIOIntTypeSet(GPIO_PORTF_BASE, 0x10, GPIO_FALLING_EDGE);
  //GPIOIntTypeSet(GPIO_PORTF_BASE, 0x01, GPIO_RISING_EDGE);
  GPIOIntEnable(GPIO_PORTF_BASE, GPIO_INT_PIN_4 );
}
void Change_mode(void)
{
  if (GPIOIntStatus(GPIO_PORTF_BASE, 0x10) == 0x10)
  {
    mode++;
    if (mode == 3)
    {
      mode = 0;
    }
    LCD_clear_screen();
    GPIOIntClear(GPIO_PORTF_BASE, GPIO_INT_PIN_4);
    
  }
}

int main()
{
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  
  while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    ;
  DIO_Init_port(PORTFBase,0xFF,0x02,0x11,0x00);
  
  LCD_init();
  KEYPAD_init();
  LCD_clear_screen();
  Timer_init();
  Timer_enable();
  TivaIntButtons();
  while (1)
  {
    if (mode == 0)
    {
      Stop_mode();
    }
    else if (mode == 1)
    {
      Calculator();
    }
    else if (mode == 2)
    {
      Timer_mode();
    }
  }
}
