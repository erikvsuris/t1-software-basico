#include <stdint.h>

#ifndef HARDWARE_CONTROLLER_H
#define HARDWARE_CONTROLLER_H

// Function to open or create the file and map it into memory
char* registers_map(const char* file_path, int file_size, int* fd);
int registers_release(void* map, int file_size, int fd);
int map_register();
int map_release();

void toggleDisplay();
void setExhibitionMode(unsigned short int newExhibitionMode);
void setDisplayUpdateSpeed(unsigned short int newUpdateSpeed);
void toggleOperationLED();
void setStatusColorRed();
void setStatusColorGreen();
void setStatusColorBlue();
void resetRegisters();

#endif
