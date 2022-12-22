#ifndef KEYPAD_H_
#define KEYPAD_H_
#include "DIO.h"
#include "tm4c123gh6pm.h"
#include "bitwise_operation.h"
#include "DIO.h"

#define Col0    4
#define Col1    5
#define Col2    6
#define Col3    7
#define PORTCOL PORTCBase

#define Row0    0
#define Row1    1
#define Row2    2
#define Row3    3
#define PORTROW PORTEBase

//initialize the keypad using the keypad.h configuration 
void KEYPAD_init();

//return values if any keys is pressed else return 't' as error character 
uint8 KEYPAD_READ(); 



#endif