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
        printf("7 - Definir cor do display\n");
        printf("8 - Obter nivel da bateria\n");
        printf("9 - Obter temperatura atual\n");
        printf("10 - Obter numero de vezes que a mensagem apareceu\n");
        printf("11 - Definir caracteres do display\n");
        printf("12 - Print\n");
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
                        printf("00 - Estatico.\n\n");
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
                printf("Estado atual do LED de status: ");
                switch (status_LED)
                {
                    case 0:
                        printf("Desligado.\n\n");
                        break;

                    case 1:
                        printf("Ligado Azul.\n\n");
                        break;
                    
                    case 2:
                        printf("Ligado Verde.\n\n");
                        break;

                    case 3:
                        printf("Ligado Amarelo.\n\n");
                        break;
                    
                    case 4:
                        printf("Ligado Vermelho.\n\n");
                        break;
                    
                    default:
                        printf("Cor do LED de status invalida!\n\n");
                        break;
                }
                printf("1 - Ligar\n");
                printf("2 - Desligar\n");
                printf("\nSelecione a operacao que deseja realizar: ");
                scanf("%hu", &status_LED);
                switch (status_LED)
                {
                    case 1:
                        turn_status_LED_on();
                        break;

                    case 2:
                        turn_status_LED_off();
                        break;
                    
                    default:
                        printf("Operacao invalida!\n");
                        break;
                }
                break;

            case 6:
                reset_registers();
                break;

            case 7:
                printf("\n---------- DISPLAY ----------\n\n");
                unsigned short red_color = get_display_color_red();
                unsigned short green_color = get_display_color_green();
                unsigned short blue_color = get_display_color_blue();
                printf("Cor do display:\nR=%hu\nG=%hu\nB=%hu\n", red_color, green_color, blue_color);
                
                printf("\nDefina a faixa de cor vermelha do display (0-255): ");
                scanf("%hu", &red_color);
                if (red_color > 255) printf("Faixa de cor invalida!\n");
                else set_display_color_red(red_color);

                printf("\nDefina a faixa de cor verde do display (0-255): ");
                scanf("%hu", &green_color);
                if (green_color > 255) printf("Faixa de cor invalida!\n");
                else set_display_color_green(green_color);

                printf("\nDefina a faixa de cor azul do display (0-255): ");
                scanf("%hu", &blue_color);
                if (blue_color > 255) printf("Faixa de cor invalida!\n");
                else set_display_color_blue(blue_color);

                break;

            case 8:
                unsigned short battery_level = get_battery_level();
                printf("\nNivel de bateria: ");
                switch (battery_level)
                {
                case 0:
                    printf("00 - Critico.\n");
                    break;
                
                case 1:
                    printf("01 - Baixo.\n");
                    break;
                
                case 2:
                    printf("10 - Medio.\n");
                    break;
                
                case 3:
                    printf("11 - Alto.\n");
                    break;
                
                default:
                    printf("Nivel de bateria invalido!\n");
                    break;
                }
                break;

            case 9:
                float current_temperature = get_current_temperature();
                printf("\nTemperatura atual em celsius: %.1f ºC.\n", current_temperature);

                break;

            case 10:
                unsigned short sliding_message_times = get_sliding_message_times();
                printf("\nNumero de vezes que a mensagem apareceu: %hu.\n", sliding_message_times);

                break;

            case 11:
                printf("\n------- DISPLAY CHARACTERS -------\n");
                char current_display_characters[24];
                get_display_characters(current_display_characters);
                printf("\nEstado atual dos caracteres do display: %s.\n", current_display_characters);

                char new_display_characters[24];
                printf("\nDefina a mensagem do display (24 caracteres): ");
                fgets(new_display_characters, sizeof(new_display_characters), stdin); 
                scanf("%[^\n]s", new_display_characters);
                set_display_characters(new_display_characters);

                break;
            case 12:
                print_registers();

                break;

            default:
                printf("\nOperacao invalida!");
                break;
        }
    } while (operation != 0);

    return map_release();
}