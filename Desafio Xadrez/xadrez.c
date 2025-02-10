#include <stdio.h>

const int BISPO = 5, TORRE = 5, RAINHA = 8;

int main(){

    int i = 0, resp = 0;

    do //menu interativo para definir a peça a ser movimentada
    {
        printf("\nQual peça deseja movimentar?\n\n");
        printf("1. Bispo\n");
        printf("2. Torre\n");
        printf("3. Rainha\n");
        printf("4. Sair\n\n");
        scanf("%d", &resp);
        printf("\n");

            switch (resp)
            {
            case 1: //movimentação do bispo
                printf("\nMovimentando...\n\n");

                    for (i = 0; i < BISPO; i++)
                    {
                        printf("Cima e Direita\n");
                    }
                break;

            case 2: //movimentação da torre
                printf("\nMovimentando...\n\n");

                    for (i = 0; i < TORRE; i++)
                    {
                        printf("Direita\n");
                    }
                break;

            case 3: //movimentação da rainha
                printf("\nMovimentando...\n\n");

                    for (i = 0; i < RAINHA; i++)
                    {
                        printf("Esquerda\n");
                    }
                break;

            case 4: //opção de saída

                        printf("Saindo...\n");
                    
                break;
            
            default:

                printf("Opção inválida!\n");
                break;
            }
                  
    } while (resp != 4);
}