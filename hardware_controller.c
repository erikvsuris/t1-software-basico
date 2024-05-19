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
   r1 = base_address + 0x02;
   r2 = base_address + 0x04;
   r3 = base_address + 0x06;
   r4 = base_address + 0x08;
   r5 = base_address + 0x0A;
   r6 = base_address + 0x0C;
   r7 = base_address + 0x0E;
   r8 = base_address + 0x10;
   r9 = base_address + 0x12;
   r11 = base_address + 0x16;
   r10 = base_address + 0x14;
   r12 = base_address + 0x18;
   r13 = base_address + 0x1A;
   r14 = base_address + 0x1C;
   r15 = base_address + 0x1E;

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
   return (*r0 >> 0) & 1;
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

   unsigned short mask = *r0 & 256;
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
   unsigned short mask = *r0 & 512;
   return mask >> 9;
}

void set_toggle_operation_LED()
{
   *r0 ^= 1 << 9;
}

unsigned short get_status_LED_color()
{  
   unsigned short mask = *r0 & 4096;
   return mask >> 10;
}

void turn_status_LED_off()
{
   *r0 &= ~(7 << 10);
}

void set_status_LED_color_red()
{
   *r0 |= 1 << 10;
   *r0 &= 0 << 11;
   *r0 &= 0 << 12;
}
void set_status_LED_color_green()
{
   *r0 &= 0 << 10;
   *r0 |= 1 << 11;
   *r0 &= 0 << 12;
}
void set_status_LED_color_blue()
{
   *r0 &= 0 << 10;
   *r0 &= 0 << 11;
   *r0 |= 1 << 12;
}
// Define componente R da color RGB para o display (default: 255).
void set_display_red_color(unsigned short red_range)
{
    if (red_range > 255) return;

   *r1 &= ~(255 << 0);
   *r1 |= (red_range & 255) << 0;
}
// Define componente G da color RGB para o display (default: 255).
void set_display_green_color(unsigned short green_range)
{
   if (green_range > 255) return;

   *r1 &= ~(255 << 8);
   *r1 |= (green_range & 255) << 8;
}
// Define componente B da color RGB para o display (default: 255).
void set_display_blue_color(unsigned short blue_range)
{
   if (blue_range > 255) return;

   *r2 &= ~(255 << 0);
   *r2 |= (blue_range & 255) << 0;
}
/*
Nível da bateria:
00 = crítico
01 = baixo
10 = médio
11 = alto
*/
unsigned short get_battery_level()
{
   return 0;
}
/*
Número de vezes que a mensagem apareceu de
forma completa no display no modo deslizante
*/
unsigned short get_sliding_message_times()
{  
   return 0;
}

/*
Temperatura atual em graus Celsius vezes 10
(por exemplo, valor decimal 323 representa 32,2
graus). Valores negativos são representados em
complemento de 2
*/
unsigned short get_current_celsius_temperature()
{ 
   return 0;
}
// Reseta registradores para padrão de fábrica (default)
void reset_registers()
{
   *r0 &= 0;
   *r0 |= 16;
   // *r1 &= 0;
   // *r1 |= 65535;
   // *r2 &= 0;
   // *r2 |= 255;
   // *r3 &= 0;
   // *r4 &= 0;
   // *r5 &= 0;
   // *r6 &= 0;
   // *r7 &= 0;
   // *r8 &= 0;
   // *r9 &= 0;
   // *r10 &= 0;
   // *r11 &= 0;
   // *r12 &= 0;
   // *r13 &= 0;
   // *r14 &= 0;
   // *r15 &= 0;
}

void print_registers() {
   printf("\n%d",*r0);
   printf("\n%d",*r1);
   printf("\n%d",*r2);
   printf("\n%d",*r3);
   printf("\n%d",*r4);
   printf("\n%d",*r5);
   printf("\n%d",*r6);
   printf("\n%d",*r7);
   printf("\n%d",*r8);
   printf("\n%d",*r9);
   printf("\n%d",*r10);
   printf("\n%d",*r11);
   printf("\n%d",*r12);
   printf("\n%d",*r13);
   printf("\n%d",*r14);
   printf("\n%d",*r15);
}
