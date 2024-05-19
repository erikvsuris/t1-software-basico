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
void set_exhibition_mode(unsigned short new_exhibition_mode);

unsigned short get_display_update_speed();
void set_display_update_speed(unsigned short new_update_speed);

unsigned short get_toggle_operation_LED();
void set_toggle_operation_LED();

unsigned short get_status_LED_color();
void turn_status_LED_off();
void set_status_LED_color_red();
void set_status_LED_color_green();
void set_status_LED_color_blue();

void set_display_red_color(unsigned short red_range);
void set_display_green_color(unsigned short green_range);
void set_display_blue_color(unsigned short blue_range);

unsigned short get_battery_level();

unsigned short get_sliding_message_times();

unsigned short get_current_celsius_temperature();

void reset_registers();

void print_registers();

#endif
