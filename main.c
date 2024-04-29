#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>
// #include "hardware_controller.h"

#define FILE_PATH "registers.bin"
#define FILE_SIZE 1024  // Same size as used in the first program

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

int main() {
    int fd;
    // Open the file and map it into memory
    char* map = registers_map(FILE_PATH, FILE_SIZE, &fd);
    if (map == NULL) {
        return EXIT_FAILURE;
    }

    unsigned short *base_address = (unsigned short *)map;
    unsigned short *r0 = base_address + 0x00;
    unsigned short *r1 = base_address + 0x02;
    unsigned short *r2 = base_address + 0x04;
    unsigned short *r3 = base_address + 0x06;
    unsigned short *r4 = base_address + 0x08;
    // unsigned short *r5 = base_address + 0x0A;
    // unsigned short *r6 = base_address + 0x0C;
    // unsigned short *r7 = base_address + 0x0E;
    // unsigned short *r8 = base_address + 0x10;
    // unsigned short *r9 = base_address + 0x12;
    // unsigned short *r10 = base_address + 0x14;
    // unsigned short *r11 = base_address + 0x16;
    // unsigned short *r12 = base_address + 0x18;
    // unsigned short *r13 = base_address + 0x1A;
    // unsigned short *r14 = base_address + 0x1C;
    // unsigned short *r15 = base_address + 0x1E;

    toggleDisplay(r0);
    defineExhibitionMode(r0, 2);

    short int operation;

    do {
        printf("\n-- CONTROLADOR DE HARDWARE --\n");
        printf("1 - Ligar/Desligar o display\n");
        printf("2 - Selecionar modo de exibição\n");
        printf("3 - Definir velocidade de atualização\n");
        printf("4 - Ligar/Desligar o LED de operação\n");
        printf("5 - Ligar/Desligar e definir a cor do LED de status\n");
        printf("6 - Resetar registradores para padrão de fábrica\n");
        printf("\n0 - Finalizar o programa\n");

        switch (expression)
        {
            case 0:
                printf("Fim");
                break;
            
            case 1:
                break;
            
            case 2:
                break;

            case 3:
                break;
            
            case 4:
                break;

            case 5:
                break;

            case 6:
                break;

            default:
                break;
        }
    } while (operation != 0);

    printf("Valor atual de R0: 0x%02x\n", *r0);
    printf("Valor atual de R1: 0x%02x\n", *r1);
    printf("Valor atual de R2: 0x%02x\n", *r2);
    printf("Valor atual de R3: 0x%02x\n", *r3);
    printf("Valor atual de R4: 0x%02x\n", *r4);
    // printf("Valor atual de R5: 0x%02x\n", *r5);
    // printf("Valor atual de R6: 0x%02x\n", *r6);
    // printf("Valor atual de R7: 0x%02x\n", *r7);
    // printf("Valor atual de R8: 0x%02x\n", *r8);
    // printf("Valor atual de R9: 0x%02x\n", *r9);
    // printf("Valor atual de R10: 0x%02x\n", *r10);
    // printf("Valor atual de R11: 0x%02x\n", *r11);
    // printf("Valor atual de R12: 0x%02x\n", *r12)
    // printf("Valor atual de R13: 0x%02x\n", *r13);
    // printf("Valor atual de R14: 0x%02x\n", *r14);
    // printf("Valor atual de R15: 0x%02x\n", *r15);

    // Release resources
    if (registers_release(map, FILE_SIZE, fd) == -1) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}