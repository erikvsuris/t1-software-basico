#include <stdint.h>

#ifndef HARDWARE_CONTROLLER_H
#define HARDWARE_CONTROLLER_H

void toggleDisplay(unsigned int *reg);
void setExhibitionMode(unsigned short int *reg, unsigned int newExhibitionMode);
void setDisplayUpdateSpeed(unsigned short int *reg);
void toggleOperationLED(unsigned short int *reg);
void setStatusColorRed(unsigned short int *reg);
void setStatusColorGreen(unsigned short int *reg);
void setStatusColorBlue(unsigned short int *reg);
void resetRegisters(unsigned short int *reg);

#endif
