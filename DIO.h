

#ifndef DIO_H_
#define DIO_H_

#include "types.h"
#include "DIO.h"
#include "tm4c123gh6pm.h"
#include "bitwise_operation.h"
/*******************************************************************************
*                                Definitions                                  *
*******************************************************************************/
#define PORTABase	    	        0x40004000
#define PORTBBase   	                0x40005000
#define PORTCBase       	        0x40006000
#define PORTDBase                 	0x40007000
#define PORTEBase			0x40024000
#define PORTFBase			0x40025000




#define PIN0                	0
#define PIN1                	1
#define PIN2                	2
#define PIN3                	3
#define PIN4            	4
#define PIN5        	        5
#define PIN6    	        6
#define PIN7	                7



typedef enum
{
	PIN_INPUT,PIN_OUTPUT
}GPIO_PinDirectionType;

void DIO_Init_port (uint32 portbase,uint8 cr,uint8 pd,uint8 pur,uint8 pdr);
void DIO_WritePort(uint32 portbase, uint8 value);
void DIO_WritePin (uint32 port_num, uint8 pin_num, uint8 value);
uint8 DIO_ReadPin (uint32 port_num, uint8 pin_num);
uint8 DIO_ReadPort (uint32 port_num);

#endif /* DIO_H_ */