int main() {
    toggleDisplay();
    defineExhibitionMode(2);

    short int operation;

    do {
        printf("\n-- CONTROLADOR DE HARDWARE --\n");
        printf("\n1 - Ligar/Desligar o display\n");
        printf("2 - Selecionar modo de exibição\n");
        printf("3 - Definir velocidade de atualização\n");
        printf("4 - Ligar/Desligar o LED de operação\n");
        printf("5 - Ligar/Desligar e definir a cor do LED de status\n");
        printf("6 - Resetar registradores para padrão de fábrica\n");
        printf("\n0 - Finalizar o programa\n");

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
}