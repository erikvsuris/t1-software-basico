#include <stdio.h>
#include "hardware_controller.h"

int main() {
    // map_register();
    // map_release();

    int operation;
    do {
        printf("\n-- CONTROLADOR DE HARDWARE --\n");
        printf("\n1 - Ligar/Desligar o display\n");
        printf("2 - Selecionar modo de exibicao\n");
        printf("3 - Definir velocidade de atualizacao\n");
        printf("4 - Ligar/Desligar o LED de operacao\n");
        printf("5 - Ligar/Desligar e definir a cor do LED de status\n");
        printf("6 - Resetar registradores para padrao de fabrica\n");
        printf("\n0 - Finalizar o programa\n\n");
        printf("\nSelecione a operacao que deseja realizar:");
        scanf("%d", &operation);
        switch (operation)
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

    return 0;
}