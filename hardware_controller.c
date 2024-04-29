#include <stdint.h>
#include "hardware_controller.h"

void toggleDisplay(unsigned int *reg)
{
    *reg ^= 1;
}

void setExhibitionMode(unsigned int newExhibitionMode)
{
    if () return;
    
    mask = newExhibitionMode;

    uint16_t register = *REGISTER_R0;
    register &= ~(1 << 1);
    register &= ~(1 << 2);
    
    register |= (bit_1 << 1);
    register |= (bit_2 << 2);
    
    *REGISTER_R0 = register;
}

/*
Define velocidade de atualização do display em
valores múltiplos de 100 milisegundos para modo
de exibição não estático (default: 2).
Exemplo: valor 2 representa 200 ms 

*/

int displayUpdateSpeed = 2;

void setDisplayUpdateSpeed()
{
    
}

// Liga/Desliga o LED de operação (default: 0)

void toggleOperationLED()
{
    *REGISTER_R0 ^= 1;
}

/*

Liga/Desliga o LED de status e define cor:
bit 10 = R
bit 11 = G
bit 12 = B

*/

void toggleStatusLEDColor()
{

}

// Reseta registradores para padrão de fábrica (default)

void resetRegisters()
{
    *REGISTER_R0 =
    *REGISTER_R1 =
    *REGISTER_R2 =
    *REGISTER_R3 =
    *REGISTER_R4 =
    *REGISTER_R5 =
    *REGISTER_R6 =
    *REGISTER_R7 =
    *REGISTER_R8 =
    *REGISTER_R9 =
    *REGISTER_R10 =
    *REGISTER_R11 =
    *REGISTER_R12 =
    *REGISTER_R13 =
    *REGISTER_R14 =
    *REGISTER_R15 =
}
