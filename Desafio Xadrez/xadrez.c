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
        printf("4. Sair\n");
        scanf("%d", &resp);

            switch (resp)
            {
            case 1: //movimentação do bispo
                printf("\nMovimentando...\n\n");

                    for (i = 0; i < BISPO; i++)
                    {
                        printf("Cima e Direita\n");
                    }
                break;
            
            default:
                break;
            }
                  
    } while (resp != 4);
}