#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

struct Item mochila[MAX_ITENS];
int totalItens = 0;

// Protótipos
void inserirItem();
void removerItem();
void listarItens();
void buscarItemBinaria(); // Nome alterado para destacar a mudança
void ordenarMochila();    // Nova função necessária
void limparBuffer();

int main() {
    int opcao;
    do {
        printf("\n--- MOCHILA (Ordenada para Busca Binaria) ---\n");
        printf("1. Cadastrar Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Buscar Item (Binaria)\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                inserirItem();
                listarItens();
                break;
            case 2:
                removerItem();
                listarItens();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItemBinaria();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
    return 0;
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Nova Função: Ordena o vetor alfabeticamente (Bubble Sort)
void ordenarMochila() {
    struct Item temp;
    for (int i = 0; i < totalItens - 1; i++) {
        for (int j = 0; j < totalItens - i - 1; j++) {
            // Se o nome atual for "maior" alfabeticamente que o proximo, troca
            if (strcmp(mochila[j].nome, mochila[j+1].nome) > 0) {
                temp = mochila[j];
                mochila[j] = mochila[j+1];
                mochila[j+1] = temp;
            }
        }
    }
}

void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("\n[ERRO] Mochila cheia!\n");
        return;
    }

    printf("\n--- Novo Item ---\n");
    printf("Nome: ");
    fgets(mochila[totalItens].nome, 30, stdin);
    mochila[totalItens].nome[strcspn(mochila[totalItens].nome, "\n")] = 0;

    printf("Tipo: ");
    fgets(mochila[totalItens].tipo, 20, stdin);
    mochila[totalItens].tipo[strcspn(mochila[totalItens].tipo, "\n")] = 0;

    printf("Quantidade: ");
    scanf("%d", &mochila[totalItens].quantidade);
    limparBuffer();

    totalItens++;
    
    // IMPORTANTE: Após inserir, ordenamos a mochila para permitir a busca binária
    ordenarMochila(); 
    printf("[SUCESSO] Item adicionado e mochila reordenada!\n");
}

void removerItem() {
    if (totalItens == 0) {
        printf("\n[AVISO] Mochila vazia.\n");
        return;
    }

    char nomeBusca[30];
    printf("Nome para remover: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    // Podemos usar a busca binária até para achar o item a ser removido
    // Mas manterei o loop simples aqui para focar na função de busca principal
    int encontrado = 0;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            for (int j = i; j < totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            totalItens--;
            encontrado = 1;
            printf("[SUCESSO] Removido.\n");
            break;
        }
    }
    if (!encontrado) printf("[ERRO] Nao encontrado.\n");
}

void listarItens() {
    printf("\n--- Lista de Itens (Ordem Alfabetica) ---\n");
    for (int i = 0; i < totalItens; i++) {
        printf("%02d | %-20s | Qtd: %d\n", i + 1, mochila[i].nome, mochila[i].quantidade);
    }
}

// --- AQUI ESTÁ A BUSCA BINÁRIA ---
void buscarItemBinaria() {
    if (totalItens == 0) {
        printf("\n[AVISO] Mochila vazia.\n");
        return;
    }

    char nomeBusca[30];
    printf("\n--- Busca Binaria ---\n");
    printf("Digite o nome exato: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    int inicio = 0;
    int fim = totalItens - 1;
    int meio;
    int encontrado = 0;

    // Algoritmo de Busca Binária
    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        
        // Compara o nome buscado com o nome do meio
        int comparacao = strcmp(nomeBusca, mochila[meio].nome);

        if (comparacao == 0) {
            // Encontrou (são iguais)
            printf("\n[ENCONTRADO no indice %d]\n", meio);
            printf("Nome: %s\n", mochila[meio].nome);
            printf("Tipo: %s\n", mochila[meio].tipo);
            printf("Quantidade: %d\n", mochila[meio].quantidade);
            encontrado = 1;
            break;
        } 
        else if (comparacao > 0) {
            // Se o que busco é "maior" (vem depois no alfabeto), ignoro a metade esquerda
            inicio = meio + 1;
        } 
        else {
            // Se o que busco é "menor" (vem antes), ignoro a metade direita
            fim = meio - 1;
        }
    }

    if (!encontrado) {
        printf("[INFO] Item nao encontrado via Busca Binaria.\n");
    }
}