#include <stdio.h>

int main(){

    float N1 = 0, N2 = 0, N3 = 0, media = 0;

    printf("Digite a primeira nota:\n ");
    scanf("%f", &N1);
    printf("Digite a segunda nota:\n ");
    scanf("%f", &N2);
    printf("Digite a terceira nota:\n ");
    scanf("%f", &N3);

    media = (N1 + N2 + N3)/3;

    printf("Sua média é: %.4f\n", media);

}