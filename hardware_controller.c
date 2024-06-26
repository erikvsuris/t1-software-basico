#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>
#include "hardware_controller.h"

#define FILE_PATH "registers.bin"
#define FILE_SIZE 1024

int fd;
char *map;

unsigned short *r0;
unsigned short *r1;
unsigned short *r2;
unsigned short *r3;
unsigned short *r4;
unsigned short *r5;
unsigned short *r6;
unsigned short *r7;
unsigned short *r8;
unsigned short *r9;
unsigned short *r10;
unsigned short *r11;
unsigned short *r12;
unsigned short *r13;
unsigned short *r14;
unsigned short *r15;

char* registers_map(const char* file_path, int file_size, int* fd) {
   *fd = open(file_path, O_RDWR | O_CREAT, 0666);
   if (*fd == -1) {
      perror("Error opening or creating file");
      return NULL;
   }

   if (ftruncate(*fd, file_size) == -1) {
      perror("Error setting file size");
      close(*fd);
      return NULL;
   }

   char *map = mmap(0, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, *fd, 0);
   if (map == MAP_FAILED) {
      perror("Error mapping file");
      close(*fd);
      return NULL;
   }

   unsigned short *base_address = (unsigned short *)map;

   r0 = base_address + 0x00;
   r1 = base_address + 0x01;
   r2 = base_address + 0x02;
   r3 = base_address + 0x03;
   r4 = base_address + 0x04;
   r5 = base_address + 0x05;
   r6 = base_address + 0x06;
   r7 = base_address + 0x07;
   r8 = base_address + 0x08;
   r9 = base_address + 0x09;
   r11 = base_address + 0x0A;
   r10 = base_address + 0x0B;
   r12 = base_address + 0x0C;
   r13 = base_address + 0x0D;
   r14 = base_address + 0x0E;
   r15 = base_address + 0x0F;

   return map;
}

int map_register()
{
   int fd;
   char *map = registers_map(FILE_PATH, FILE_SIZE, &fd);
   if (map == NULL) {
      return EXIT_FAILURE;
   }
   return 0;
}

int registers_release(void* map, int file_size, int fd)
{
    if (munmap(map, file_size) == -1) {
        perror("Error unmapping the file");
        close(fd);
        return -1;
    }

    if (close(fd) == -1) {
        perror("Error closing file");
        return -1;
    }

    return 0;
}

int map_release()
{
   if (registers_release(map, FILE_SIZE, fd) == -1) {
         return EXIT_FAILURE;
   }

   return EXIT_SUCCESS;
}

unsigned short int get_toggle_display()
{
   return *r0 & 1;
}

void set_toggle_display()
{
   *r0 ^= 1;
}

unsigned short get_exhibition_mode()
{
   unsigned short mask = *r0 & 6;
   return mask >> 1;
}

void set_exhibition_mode(unsigned short new_exhibition_mode)
{
   if (new_exhibition_mode > 3) return;
   *r0 &= ~(3 << 1);
   *r0 |= (new_exhibition_mode & 3) << 1;
}

unsigned short get_display_update_speed()
{
   unsigned short mask = *r0 & (63 << 3);
   return mask >> 3;
}

void set_display_update_speed(unsigned short new_update_speed)
{
   if (new_update_speed == 0 || new_update_speed > 63) return;
   if (get_exhibition_mode() == 0) return;

   *r0 &= ~(63 << 3);
   *r0 |= (new_update_speed & 63) << 3;
}

unsigned short get_toggle_operation_LED() {
   unsigned short mask = *r0 & (1 << 9);
   return mask >> 9;
}

void set_toggle_operation_LED()
{
   *r0 ^= 1 << 9;
}

unsigned short get_status_LED_color()
{
   unsigned short mask = *r0 & (7 << 10);
   return mask >> 10;
}

void turn_status_LED_off()
{
   *r0 &= ~(7 << 10);
}

void turn_status_LED_on()
{
   unsigned int battery_level = get_battery_level();
   switch (battery_level)
   {
      case 0:
         set_status_LED_color_red();
         break;

      case 1:
         set_status_LED_color_yellow();
         break;

      case 2:
         set_status_LED_color_green();
         break;
      
      case 3:
         set_status_LED_color_blue();
         break;
      
      default: break;
   }
}

void set_status_LED_color_red()
{
   *r0 &= ~(1 << 10);
   *r0 &= ~(1 << 11);
   *r0 |= 1 << 12;
}

void set_status_LED_color_yellow()
{
   *r0 &= ~(1 << 10);
   *r0 |= 1 << 11;
   *r0 |= 1 << 12;
}

void set_status_LED_color_green()
{
   *r0 &= ~(1 << 10);
   *r0 |= 1 << 11;
   *r0 &= ~(1 << 12);
}

void set_status_LED_color_blue()
{
   *r0 |= 1 << 10;
   *r0 &= ~(1 << 11);
   *r0 &= ~(1 << 12);
}

void reset_registers()
{
   *r0 &= 0;
   *r0 |= 17;
   *r1 &= 0;
   *r1 |= 65535;
   *r2 &= 0;
   *r2 |= 255;
   *r3 &= 0;
   *r3 |= 22083;
   *r4 &= 0;
   *r4 |= 17736;
   *r5 &= 0;
   *r5 |= 19532;
   *r6 &= 0;
   *r6 |= 8271;
   *r7 &= 0;
   *r7 |= 20311;
   *r8 &= 0;
   *r8 |= 21068;
   *r9 &= 0;
   *r9 |= 68;
   *r10 &= 0;
   *r11 &= 0;
   *r12 &= 0;
   *r13 &= 0;
   *r14 &= 0;
   *r15 &= 0;
}

unsigned short get_display_color_red() {
   unsigned short mask = *r1 & (255 << 0);
   return mask >> 0;
}

unsigned short get_display_color_green() {
   unsigned short mask = *r1 & (255 << 8);
   return mask >> 8;
}

unsigned short get_display_color_blue() {
   unsigned short mask = *r2 & (255 << 0);
   return mask >> 0;
}

void set_display_color_red(unsigned short red_range)
{
   if (red_range > 255) return;

   *r1 &= ~(255 << 0);
   *r1 |= (red_range & 255) << 0;
}

void set_display_color_green(unsigned short green_range)
{
   if (green_range > 255) return;

   *r1 &= ~(255 << 8);
   *r1 |= (green_range & 255) << 8;
}

void set_display_color_blue(unsigned short blue_range)
{
   if (blue_range > 255) return;

   *r2 &= ~(255 << 0);
   *r2 |= (blue_range & 255) << 0;
}

unsigned short get_battery_level()
{
   return *r3 & 3;
}

/*
Número de vezes que a mensagem apareceu de
forma completa no display no modo deslizante
*/
unsigned short get_sliding_message_times()
{  
   unsigned short mask = *r3 & (15 << 2);
   return mask >> 2;
}

float get_current_temperature()
{ 
   unsigned short bin_current_temperature = (*r3 & (1023 << 6)) >> 6;
   double current_temperature = (double)bin_current_temperature / 10;
   if ((bin_current_temperature >> 9) == 1) return -current_temperature;
   else return current_temperature;
}

void print_registers() {
   printf("\n%hu",*r0);
   printf("\n%hu",*r1);
   printf("\n%hu",*r2);
   printf("\n%hu",*r3);
   printf("\n%hu",*r4);
   printf("\n%hu",*r5);
   printf("\n%hu",*r6);
   printf("\n%hu",*r7);
   printf("\n%hu",*r8);
   printf("\n%hu",*r9);
   printf("\n%hu",*r10);
   printf("\n%hu",*r11);
   printf("\n%hu",*r12);
   printf("\n%hu",*r13);
   printf("\n%hu",*r14);
   printf("\n%hu",*r15);
}

void get_display_characters(char display_characters[]) {
   for (int i = 0; i < 24; i++) {
      display_characters[i] = *((char *)r4 + i);
   }
}

void set_display_characters(char new_display_characters[]) {
   for (int i = 0; i < 24; i++) {
      *(r4 + i) = 0; 
      *((char *)r4 + i) = new_display_characters[i];
   }
}