#include <stdio.h>
#include "hardware_controller.h"

int main() {
    map_register();
    reset_registers();

    int operation;
    do {
        printf("\n\n---------- CONTROLADOR DE HARDWARE ----------\n\n");
        printf("1 - Ligar/Desligar o display\n");
        printf("2 - Selecionar modo de exibicao\n");
        printf("3 - Definir velocidade de atualizacao\n");
        printf("4 - Ligar/Desligar o LED de operacao\n");
        printf("5 - Ligar/Desligar e definir a cor do LED de status\n");
        printf("6 - Resetar registradores para padrao de fabrica\n");
        printf("0 - Finalizar o programa\n");
        printf("\nSelecione a operacao que deseja realizar: ");
        scanf("%d", &operation);
        switch (operation)
        {           
            case 1:
                set_toggle_display();
                unsigned short display_on = get_toggle_display();
                printf("\nEstado atual do registrador: %u. %s\n", display_on,
                    display_on ? "Display ligado." : "Display desligado.");
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

            case 0:
                printf("\nFim do Programa...\n\n");
                break;

            default:
                printf("\nOperação inválida!");
                break;
        }
    } while (operation != 0);

    return map_release();
}