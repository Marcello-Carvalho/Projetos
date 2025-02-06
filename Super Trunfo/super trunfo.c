#include <stdio.h>

int main(){

    // Declaracao de variaveis
    char cod1[4], cod2[4], nom1[40], nom2[40];
    float pop1 = 0, pop2 =0, area1 = 0, area2 = 0, pibcid1 = 0, pibcid2 = 0, pibcap1 = 0, pibcap2 = 0, densi1 = 0, densi2 = 0, suppod1 = 0, suppod2 = 0;
    int ntur1 = 0, ntur2 = 0, opcao;

    // Entrada e armazenamento dos dados da primeira carta
    printf("Informe o código da carta: ");
    scanf("%s", &cod1);
    printf("Informe o nome da cidade: ");
    scanf("%s", &nom1);
    printf("Informe a população da cidade: ");
    scanf("%f", &pop1);
    printf("Informe a área da cidade em km²: ");
    scanf("%f", &area1);
    printf("Informe o PIB da cidade: ");
    scanf("%f", &pibcid1);
    printf("Informe o número de pontos turísticos da cidade: ");
    scanf("%i", &ntur1);

    // Calculo PIB per capita, densidade populacional e super poder da primeira carta
    pibcap1 = pibcid1/pop1;
    densi1 = pop1/area1;
    suppod1 = pop1 + area1 + pibcid1 + pibcap1 - densi1 + ntur1;

    // Apresentacao dos dados da primeira carta
    printf("\n\n*  Carta cadastrada com sucesso!  *");
    printf("\n\nCódigo da carta: %s\n", cod1);
    printf("Nome da cidade: %s\n", nom1);
    printf("População da cidade: %.2f\n", pop1);
    printf("Área da cidade: %.2f km²\n", area1);
    printf("Densidade populacional: %.2f pessoas/km²\n", densi1);
    printf("PIB da cidade: %.2f\n", pibcid1);
    printf("PIB per capita: %.2f reais\n", pibcap1);
    printf("Número de pontos turísticos: %i\n", ntur1);
    printf("Super poder: %f \n\n", suppod1);

    // Opção de cadastrar nova carta
    printf("\n*** Cadastre a segunda carta para comparação ***\n");

    // Entrada e armazenamento dos dados da segunda carta
    printf("Informe o código da carta: ");
    scanf("%s", &cod2);
    printf("Informe o nome da cidade: ");
    scanf("%s", &nom2);
    printf("Informe a população da cidade: ");
    scanf("%f", &pop2);
    printf("Informe a área da cidade em km²: ");
    scanf("%f", &area2);
    printf("Informe o PIB da cidade: ");
    scanf("%f", &pibcid2);
    printf("Informe o número de pontos turísticos da cidade: ");
    scanf("%i", &ntur2);

    // Calculo PIB per capita, densidade populacional e super poder da segunda carta
    pibcap2 = pibcid2/pop2;
    densi2 = pop2/area2;
    suppod2 = pop2 + area2 + pibcid2 + pibcap2 - densi2 + ntur2;

    // Apresentacao dos dados da segunda carta
    printf("\n\n*  Carta cadastrada com sucesso!  *");
    printf("\n\nCódigo da carta: %s\n", cod2);
    printf("Nome da cidade: %s\n", nom2);
    printf("População da cidade: %.2f\n", pop2);
    printf("Área da cidade: %.2f km²\n", area2);
    printf("Densidade populacional: %.2f pessoas/km²\n", densi2);
    printf("PIB da cidade: %.2f\n", pibcid2);
    printf("PIB per capita: %.2f reais\n", pibcap2);
    printf("Número de pontos turísticos: %i\n", ntur2);
    printf("Super poder: %f \n\n", suppod2);

    //Menu para escolha da propriedade a ser comparada
    do {
    printf("*     Escolha a propriedade a ser utilizada na comparação     *\n\n");
    
    printf("1. População\n");
    printf("2. Área\n");
    printf("3. Densidade Populacional\n");
    printf("4. PIB\n");
    printf("5. PIB per Capita\n");
    printf("6. Número de Pontos Turísticos\n");
    printf("7. Super Poder\n");
    printf("8. Sair\n\n");
    printf("Qual opção deseja: \n\n");
    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1:
        printf("Carta 1 - Cidade: %s, Código: %s, População: %.2f \n", &nom1, &cod1, (float)pop1);
        printf("Carta 2 - Cidade: %s, Código: %s, População: %.2f \n", &nom2, &cod2, (float)pop2);
        if (pop1 > pop2)
        {
            printf("Resultado: Carta 1 é a vencedora!");
        }else{
            printf("Resultado: Carta 2 é a vencedora!");
        }
        break;

    case 2:
        printf("Carta 1 - Cidade: %s, Código: %s, Área: %.2f \n", &nom1, &cod1, (float)area1);
        printf("Carta 2 - Cidade: %s, Código: %s, Área: %.2f \n", &nom2, &cod2, (float)area2);
        if (area1 > area2)
        {
            printf("Resultado: Carta 1 é a vencedora!");
        }else{
            printf("Resultado: Carta 2 é a vencedora!");
        }
        break;

    case 3:
        printf("Carta 1 - Cidade: %s, Código: %s, Densidade Populacional: %.2f \n", &nom1, &cod1, (float)densi1);
        printf("Carta 2 - Cidade: %s, Código: %s, Densidade Populacional: %.2f \n", &nom2, &cod2, (float)densi2);
        if (densi1 < densi2)
        {
            printf("Resultado: Carta 1 é a vencedora!");
        }else{
            printf("Resultado: Carta 2 é a vencedora!");
        }
        break;

    case 4:
        printf("Carta 1 - Cidade: %s, Código: %s,  PIB: %.2f \n", &nom1, &cod1, (float)pibcid1);
        printf("Carta 2 - Cidade: %s, Código: %s,  PIB: %.2f \n", &nom2, &cod2, (float)pibcid2);
        if (pibcid1 > pibcid2)
        {
            printf("Resultado: Carta 1 é a vencedora!");
        }else{
            printf("Resultado: Carta 2 é a vencedora!");
        }
        break;

    case 5:
        printf("Carta 1 - Cidade: %s, Código: %s,  PIB per Capita: %.2f \n", &nom1, &cod1, (float)pibcap1);
        printf("Carta 2 - Cidade: %s, Código: %s,  PIB per Capita: %.2f \n", &nom2, &cod2, (float)pibcap2);
        if (pibcap1 > pibcap2)
        {
            printf("Resultado: Carta 1 é a vencedora!");
        }else{
            printf("Resultado: Carta 2 é a vencedora!");
        }
        break;

    case 6:
        printf("\nCarta 1 - Cidade: %s, Código: %s,  Número de Pontos Turísticos: %.2f \n", &nom1, &cod1, (float)ntur1);
        printf("Carta 2 - Cidade: %s, Código: %s,  Número de Pontos Turísticos: %.2f \n", &nom2, &cod2, (float)ntur2);
        if (ntur1 > ntur2)
        {
            printf("Resultado: Carta 1 é a vencedora!");
        }else{
            printf("Resultado: Carta 2 é a vencedora!");
        }
        break;

    case 7:
        printf("Carta 1 - Cidade: %s, Código: %s,  Super Poder: %.2f \n", &nom1, &cod1, (float)suppod1);
        printf("Carta 2 - Cidade: %s, Código: %s,  Super Poder: %.2f \n", &nom2, &cod2, (float)suppod2);
        if (suppod1 > suppod2)
        {
            printf("Resultado: Carta 1 é a vencedora!");
        }else{
            printf("Resultado: Carta 2 é a vencedora!");
        }
        break;

    case 8:
        printf("Saindo...\n");
        break;
    
    default:
        printf("Opção inválida\n");
        break;
    }
      } while (opcao != 8);
    
      
    
}