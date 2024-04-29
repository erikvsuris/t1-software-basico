#include <stdint.h>

#ifndef HARDWARE_CONTROLLER_H
#define HARDWARE_CONTROLLER_H

unsigned short *base_address = (unsigned short *)map;
unsigned short *r0 = base_address + 0x00;
unsigned short *r1 = base_address + 0x02;

void toggleDisplay(unsigned int *reg);
void setExhibitionMode(unsigned int newExhibitionMode);
void setDisplayUpdateSpeed();
void toggleOperationLED();
void toggleStatusLEDColor();
void resetRegisters();

#endif