#include <stdio.h>
#include <string.h>

#define MAX_TERRITORIOS 5 // tamanho máximo de territórios

struct Territorio {
        char nome[30];
        char cor[10];
        int tropas;
    };
    

int main() {
    struct Territorio pais[MAX_TERRITORIOS];
    
    for (int i = 1; i <= MAX_TERRITORIOS; i++)
    {
        printf("--- Cadastro do território %d ---\n\n", i);
        printf("Nome do território: ");
        scanf("%s", &pais[i].nome);
        printf("Cor do exército: ");
        scanf("%s", &pais[i].cor);
        printf("Quantidade de tropas: ");
        scanf("%d", &pais[i].tropas);
        printf("\n\n");
    }

        printf("==============================================\n");
        printf("                MAPA DO MUNDO                 \n");
        printf("==============================================\n\n");

    for (int j = 1; j <= MAX_TERRITORIOS; j++)
    {
        printf("\nTerritório %d\n", j);
        printf("- Nome: %s\n", pais[j].nome);
        printf("- Exército: %s\n", pais[j].cor);
        printf("- Tropas: %d\n", pais[j].tropas);
    }
    
    return 0;
}