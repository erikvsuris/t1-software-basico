#include <stdint.h>

#ifndef HARDWARE_CONTROLLER_H
#define HARDWARE_CONTROLLER_H

void toggleDisplay();
void setExhibitionMode(unsigned short int newExhibitionMode);
void setDisplayUpdateSpeed(unsigned short int newUpdateSpeed);
void toggleOperationLED();
void setStatusColorRed();
void setStatusColorGreen();
void setStatusColorBlue();
void resetRegisters();

#endif
