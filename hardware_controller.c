#include <stdint.h>
#include "hardware_controller.h"

/**/
Liga/Desliga o display:
0 = desligado
1 = ligado
*/
void toggleDisplay(unsigned int *reg)
{
    *reg ^= 1;
}

/*
Seleciona o modo de exibição:
00 = estático (default)
01 = deslizante
10 = piscante
11 = deslizante/piscante
*/
void setExhibitionMode(unsigned short int *reg, unsigned short int newExhibitionMode)
{
    if (newExhibitionMode > 3) return;

    *reg &= ~(3 << 1);
    *reg |= (newExhibitionMode & 3) << 1;
}

/*
Define velocidade de atualização do display em
valores múltiplos de 100 milisegundos para modo
de exibição não estático (default: 2).
Exemplo: valor 2 representa 200 ms 
*/
void setDisplayUpdateSpeed(unsigned short int *reg, unsigned short int newUpdateSpeed)
{
   if (newExhibitionMode > 63) return;
   // Verificar se modo de exibição é não estático
   
   *reg &= ~(63 << 3);
   *reg |= (newUpdateSpeed & 63) << 3;
}

// Liga/Desliga o LED de operação (default: 0)
void toggleOperationLED(unsigned short int *reg)
{
    *reg ^= 1;
}

/*
Liga/Desliga o LED de status e define cor:
bit 10 = R
bit 11 = G
bit 12 = B
*/
void setStatusColorRed(unsigned short int *reg)
{
   *reg |= 1 << 10;
   *reg &= 0 << 11;
   *reg &= 0 << 12;
}

void setStatusColorGreen(unsigned short int *reg)
{
   *reg &= 0 << 10;
   *reg |= 1 << 11;
   *reg &= 0 << 12;
}

void setStatusColorBlue(unsigned short int *reg)
{
   *reg &= 0 << 10;
   *reg &= 0 << 11;
   *reg |= 1 << 12;
}

// Define componente R da color RGB para o display (default: 255).
void setDisplayRedColor(unsigned short int *reg, unsigned short int redRange)
{
    if (newExhibitionMode > 255) return;
   
   *reg &= ~(255 << 0);
   *reg |= (newUpdateSpeed & 255) << 0;
}

// Define componente G da color RGB para o display (default: 255).
void setDisplayGreenColor(unsigned short int *reg, runsigned short int greenRange)
{
   if (newExhibitionMode > 255) return;
   
   *reg &= ~(255 << 8);
   *reg |= (newUpdateSpeed & 255) << 8;
}

// Define componente B da color RGB para o display (default: 255).
void setDisplayBlueColor(unsigned short int *reg, unsigned short int blueRange)
{
   if (newExhibitionMode > 255) return;
   
   *reg &= ~(255 << 0);
   *reg |= (newUpdateSpeed & 255) << 0;
}

/*
Nível da bateria:
00 = crítico
01 = baixo
10 = médio
11 = alto
*/
void getBatteryLevel(unsigned short int *reg)
{
}

/*
Número de vezes que a mensagem apareceu de
forma completa no display no modo deslizante
*/
void timesMessageDisplaySliding(unsigned short int *reg)
{  
}

/*
Temperatura atual em graus Celsius vezes 10
(por exemplo, valor decimal 323 representa 32,2
graus). Valores negativos são representados em
complemento de 2
*/
void currentCelsiusTemperature(unsigned short int *reg)
{  
}

// Reseta registradores para padrão de fábrica (default)
void resetRegisters(unsigned short int *reg)
{
}
