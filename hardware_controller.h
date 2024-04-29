#include <stdint.h>

#ifndef HARDWARE_CONTROLLER_H
#define HARDWARE_CONTROLLER_H

void toggleDisplay(unsigned int *reg);
void setExhibitionMode(unsigned short int *reg, unsigned int newExhibitionMode);
void setDisplayUpdateSpeed();
void toggleOperationLED();
void toggleStatusLEDColor();
void resetRegisters();

#endif