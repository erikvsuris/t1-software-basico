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

void toggleDisplay(unsigned short int *reg)
{
    *reg ^= 1;
}

void defineExhibitionMode(unsigned short int *reg, unsigned short int newExhibitionMode)
{
    if (newExhibitionMode < 0 || newExhibitionMode > 3) return;

    unsigned short int mask = newExhibitionMode << 2;
    printf("%04x\n", mask);
    // short unsigned int bit_1 = 0, bit_2 = 0;
    
    // *reg |= (bit_1 << 1);
    // *reg |= (bit_2 << 2);
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

    toggleDisplay(r0);
    defineExhibitionMode(r0, 2);

    printf("Current value of R0: 0x%02x\n", *r0);
    printf("Current value of R1: 0x%02x\n", *r1);

    // Release resources
    if (registers_release(map, FILE_SIZE, fd) == -1) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}