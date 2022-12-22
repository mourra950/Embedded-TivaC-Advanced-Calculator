#ifndef Seg_H_
#define Seg_H_
#include "types.h"
#include "DIO.h"

#define SegPort 0x40005000


void Seg_init();
void Seg_Write(uint8 value);

#endif