#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>
#include "hardware_controller.h"

#define FILE_PATH "registers.bin"
#define FILE_SIZE 1024  // Same size as used in the first program

int fd;
char *map;

unsigned short int *r0;
unsigned short int *r1;
unsigned short int *r2;
unsigned short int *r3;
unsigned short int *r4;
unsigned short int *r5;
unsigned short int *r6;
unsigned short int *r7;
unsigned short int *r8;
unsigned short int *r9;
unsigned short int *r10;
unsigned short int *r11;
unsigned short int *r12;
unsigned short int *r13;
unsigned short int *r14;
unsigned short int *r15;

// Function to open or create the file and map it into memory
char* registers_map(const char* file_path, int file_size, int* fd) {
   *fd = open(file_path, O_RDWR | O_CREAT, 0666);
   if (*fd == -1) {
      perror("Error opening or creating file");
      return NULL;
   }

   // Ensure the file is of the correct size
   if (ftruncate(*fd, file_size) == -1) {
      perror("Error setting file size");
      close(*fd);
      return NULL;
   }

    // Map the file into memory
   char *map = mmap(0, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, *fd, 0);
   if (map == MAP_FAILED) {
      perror("Error mapping file");
      close(*fd);
      return NULL;
   }

   unsigned short *base_address = (unsigned short *)map;

   *r0 = *base_address + 0x00;
   *r1 = *base_address + 0x02;
   *r2 = *base_address + 0x04;
   *r3 = *base_address + 0x06;
   *r4 = *base_address + 0x08;
   *r5 = *base_address + 0x0A;
   *r6 = *base_address + 0x0C;
   *r7 = *base_address + 0x0E;
   *r8 = *base_address + 0x10;
   *r9 = *base_address + 0x12;
   *r10 = *base_address + 0x14;
   *r11 = *base_address + 0x16;
   *r12 = *base_address + 0x18;
   *r13 = *base_address + 0x1A;
   *r14 = *base_address + 0x1C;
   *r15 = *base_address + 0x1E;

   return map;
}

// Function to release mapped memory and file descriptor
int registers_release(void* map, int file_size, int fd) {
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

int map_register() {
   int fd;
   // Open the file and map it into memory
   char *map = registers_map(FILE_PATH, FILE_SIZE, &fd);
   if (map == NULL) {
      return EXIT_FAILURE;
   }
   return 0;
}

int map_release() {
   if (registers_release(map, FILE_SIZE, fd) == -1) {
         return EXIT_FAILURE;
   }

   return EXIT_SUCCESS;
}

/*
Liga/Desliga o display:
0 = desligado
1 = ligado
*/
void toggleDisplay()
{
    *r0 ^= 1;
}

/*
Seleciona o modo de exibição:
00 = estático (default)
01 = deslizante
10 = piscante
11 = deslizante/piscante
*/
unsigned short int getExhibitionMode(unsigned short int *reg) {
   return 0;
}

void setExhibitionMode(unsigned short int newExhibitionMode)
{
   if (newExhibitionMode > 3) return;

   *r0 &= ~(3 << 1);
   *r0 |= (newExhibitionMode & 3) << 1;
}

/*
Define velocidade de atualização do display em
valores múltiplos de 100 milisegundos para modo
de exibição não estático (default: 2).
Exemplo: valor 2 representa 200 ms 
*/
void setDisplayUpdateSpeed(unsigned short int newUpdateSpeed)
{
   if (newUpdateSpeed > 63) return;
   // Verificar se modo de exibição é não estático
   
   *r0 &= ~(63 << 3);
   *r0 |= (newUpdateSpeed & 63) << 3;
}

// Liga/Desliga o LED de operação (default: 0)
void toggleOperationLED()
{
   *r0 ^= 1;
}

/*
Liga/Desliga o LED de status e define cor:
bit 10 = R
bit 11 = G
bit 12 = B
*/
void setStatusColorRed()
{
   *r0 |= 1 << 10;
   *r0 &= 0 << 11;
   *r0 &= 0 << 12;
}

void setStatusColorGreen()
{
   *r0 &= 0 << 10;
   *r0 |= 1 << 11;
   *r0 &= 0 << 12;
}

void setStatusColorBlue()
{
   *r0 &= 0 << 10;
   *r0 &= 0 << 11;
   *r0 |= 1 << 12;
}

// Define componente R da color RGB para o display (default: 255).
void setDisplayRedColor(unsigned short int redRange)
{
    if (redRange > 255) return;
   
   *r1 &= ~(255 << 0);
   *r1 |= (redRange & 255) << 0;
}

// Define componente G da color RGB para o display (default: 255).
void setDisplayGreenColor(unsigned short int greenRange)
{
   if (greenRange > 255) return;
   
   *r1 &= ~(255 << 8);
   *r1 |= (greenRange & 255) << 8;
}

// Define componente B da color RGB para o display (default: 255).
void setDisplayBlueColor(unsigned short int blueRange)
{
   if (blueRange > 255) return;
   
   *r2 &= ~(255 << 0);
   *r2 |= (blueRange & 255) << 0;
}

/*
Nível da bateria:
00 = crítico
01 = baixo
10 = médio
11 = alto
*/
unsigned short int getBatteryLevel()
{
   return 0;
}

/*
Número de vezes que a mensagem apareceu de
forma completa no display no modo deslizante
*/
unsigned short int getTimesMessageDisplaySliding()
{  
   return 0;
}

/*
Temperatura atual em graus Celsius vezes 10
(por exemplo, valor decimal 323 representa 32,2
graus). Valores negativos são representados em
complemento de 2
*/
unsigned short int getCurrentCelsiusTemperature()
{ 
   return 0;
}

// Reseta registradores para padrão de fábrica (default)
void resetRegisters()
{
}
