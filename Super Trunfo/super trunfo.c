#include <stdio.h>

int main(){

    // Declaracao de variaveis
    char resp = 'n', estado, cod[4], nom[20];
    float pop = 0, area = 0, pibcid = 0, pibcap = 0, densi = 0, suppod = 0;
    int ntur = 0;

    // Repetição para cadastro de cartas
    do{    
    // Entrada e armazenamento dos dados
    printf("\nInforme o código da carta: ");
    scanf("%s", &cod);
    printf("Informe o nome da cidade: ");
    scanf("%s", &nom);
    printf("Informe a população da cidade: ");
    scanf("%f", &pop);
    printf("Informe a área da cidade em km²: ");
    scanf("%f", &area);
    printf("Informe o PIB da cidade: ");
    scanf("%f", &pibcid);
    printf("Informe o número de pontos turísticos da cidade: ");
    scanf("%i", &ntur);

    // Calculo PIB per capita, densidade populacional e super poder
    pibcap = pibcid/pop;
    densi = pop/area;
    suppod = pop + area + pibcid + pibcap - densi;

    // Apresentacao dos dados da carta
    printf("\n\nCódigo da carta: %s\n", cod);
    printf("Nome da cidade: %s\n", nom);
    printf("População da cidade: %.2f\n", pop);
    printf("Área da cidade: %.2f km²\n", area);
    printf("Densidade populacional: %f pessoas/km²\n", densi);
    printf("PIB da cidade: %.2f\n", pibcid);
    printf("PIB per capita: %f reais\n", pibcap);
    printf("Número de pontos turísticos: %i\n", ntur);

    printf("\nDeseja cadastrar outra carta? (s ou n) \n");
    scanf("%s", &resp);

    } while (resp == 's');
    
}