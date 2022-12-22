
#ifndef LED_H_
#define LED_H_
typedef enum
{
  RED_LED=0x02,BLUE_LED=0x04,GREEN_LED=0x08,RB_LED=0x06,RG_LED=0x0A,BG=0x0C,LED_OFF=0x00,WHITE_LED=0x0E
}LED_Color;


void ChangeLEDcolor(LED_Color color);
void LED_init();

#endif