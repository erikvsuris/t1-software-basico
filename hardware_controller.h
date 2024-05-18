#include <stdint.h>

#ifndef HARDWARE_CONTROLLER_H
#define HARDWARE_CONTROLLER_H

// Function to open or create the file and map it into memory
char* registers_map(const char* file_path, int file_size, int* fd);
int registers_release(void* map, int file_size, int fd);
int map_register();
int map_release();

unsigned short get_toggle_display();
void set_toggle_display();

unsigned short get_exhibition_mode();
void set_exhibition_mode(unsigned short newExhibitionMode);

void set_display_update_speed(unsigned short newUpdateSpeed);

void toggle_operation_LED();

unsigned short get_status_color();
void set_status_color_red();
void set_status_color_green();
void set_status_color_blue();

void set_display_red_color(unsigned short red_range);
void set_display_green_color(unsigned short green_range);
void set_display_blue_color(unsigned short blue_range);

unsigned short get_battery_level();

unsigned short get_sliding_message_times();

unsigned short get_current_celsius_temperature();

void reset_registers();

#endif
