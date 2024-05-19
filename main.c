#include <stdio.h>
#include "hardware_controller.h"

int main() {
    map_register();

    unsigned short operation = 0;
    do {
        printf("\n---------- CONTROLADOR DE HARDWARE ----------\n\n");
        printf("1 - Ligar/Desligar o display\n");
        printf("2 - Selecionar modo de exibicao\n");
        printf("3 - Definir velocidade de atualizacao\n");
        printf("4 - Ligar/Desligar o LED de operacao\n");
        printf("5 - Ligar/Desligar e definir a cor do LED de status\n");
        printf("6 - Resetar registradores para padrao de fabrica\n");
        printf("7 - Print\n");
        printf("0 - Finalizar o programa\n");
        printf("\nSelecione a operacao que deseja realizar: ");
        scanf("%hu", &operation);
        switch (operation)
        {         
            case 0:
                printf("\nFim do Programa...\n\n");
                break;
  
            case 1:
                set_toggle_display();
                unsigned short display_on = get_toggle_display();
                printf("\nEstado atual do Display: %hu - %s\n", display_on,
                    display_on ? "Ligado." : "Desligado.");
                break;
            
            case 2:
                printf("\n---------- MODO DE EXIBICAO ----------\n\n");
                unsigned short exhibition_mode = get_exhibition_mode();
                printf("Modo de exibicao atual: ");
                switch (exhibition_mode)
                {
                    case 0:
                        printf("00 - Estático.\n\n");
                        break;
                    
                    case 1:
                        printf("01 - Deslizante.\n\n");
                        break;
                    
                    case 2:
                        printf("10 - Piscante.\n\n");
                        break;
                    
                    case 3:
                        printf("11 - Piscante / Deslizante.\n\n");
                        break;
                    
                    default:
                        printf("Modo de exibicao invalido!");
                        break;
                }
                printf("0 - Estatico\n");
                printf("1 - Deslizante\n");
                printf("2 - Piscante\n");
                printf("3 - Piscante / Deslizante\n");
                printf("\nSelecione o novo modo de exibicao do display: ");
                scanf("%hu", &exhibition_mode);

                if (exhibition_mode > 4) printf("Modo de exibicao invalido!");
                    else set_exhibition_mode(exhibition_mode);

                break;

            case 3:
                printf("\n---------- VELOCIDADE DE ATUALIZACAO ----------\n\n");
                unsigned short display_update_speed = get_display_update_speed();
                printf("Velocidade de atualizacao atual: %hu ms.\n\n", display_update_speed * 100);
                printf("Informe a nova velocidade de atualizacao do diplay (1 - 63): ");
                scanf("%hu", &display_update_speed);

                if (display_update_speed == 0 || display_update_speed > 63) printf("Velocidade de atualizacao invalida!");
                    else set_display_update_speed(display_update_speed);

                break;
            
            case 4:
                set_toggle_operation_LED();
                unsigned short operation_LED = get_toggle_operation_LED();
                printf("\nEstado atual do LED de operacao: %hu - %s\n", operation_LED,
                    operation_LED ? "Ligado." : "Desligado.");
                break;

            case 5:
                printf("\n---------- LED DE STATUS ----------\n\n");
                unsigned short status_LED = get_status_LED_color();
                printf("Estado e Cor do LED de status atual: ");
                switch (status_LED)
                {
                    case 0:
                        printf("000 - Desligado.\n\n");
                        break;

                    case 1:
                        printf("001 - Ligado Vermelho.\n\n");
                        break;
                    
                    case 2:
                        printf("010 - Ligado Verde.\n\n");
                        break;
                    
                    case 4:
                        printf("100 - Ligado Azul.\n\n");
                        break;
                    
                    default:
                        printf("Cor do LED de status invalida!\n\n");
                        break;
                }
                printf("1 - Ligar Vermelho\n");
                printf("2 - Ligar Verde\n");
                printf("3 - Ligar Azul\n");
                printf("4 - Desligar\n");
                printf("\nSelecione a operacao que deseja realizar: ");
                scanf("%hu", &status_LED);
                switch (status_LED)
                {
                    case 1:
                        set_status_LED_color_red();
                        break;

                    case 2:
                        set_status_LED_color_green();
                        break;
                    
                    case 3:
                        set_status_LED_color_blue();
                        break;
                    
                    case 4:
                        turn_status_LED_off();
                        break;
                    
                    default:
                        printf("Cor do LED de status invalida!");
                        break;
                }
                break;

            case 6:
                reset_registers();
                break;

            case 7:
                print_registers();
                break;

            default:
                printf("\nOperacao invalida!");
                break;
        }
    } while (operation != 0);

    return map_release();
}