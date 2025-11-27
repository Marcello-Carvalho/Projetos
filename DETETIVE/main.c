#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Definição da Estrutura (Struct) ---
// Representa um nó da árvore binária (um cômodo da mansão)
typedef struct Sala {
    char nome[50];          // Nome do cômodo
    struct Sala *esquerda;  // Caminho à esquerda
    struct Sala *direita;   // Caminho à direita
} Sala;

// --- Protótipos das Funções ---
Sala* criarSala(char *nome);
void explorarSalas(Sala *raiz);

// --- Função: criarSala ---
// Objetivo: Alocar memória dinamicamente para uma nova sala e inicializar seus valores.
Sala* criarSala(char *nome) {
    // Alocação dinâmica usando malloc
    Sala *novaSala = (Sala*) malloc(sizeof(Sala));
    
    if (novaSala == NULL) {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }

    // Copia o nome recebido para a estrutura
    strcpy(novaSala->nome, nome);
    
    // Inicializa os ponteiros como NULL (sem caminhos inicialmente)
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;

    return novaSala;
}

// --- Função: explorarSalas ---
// Objetivo: Permitir a navegação do jogador pela árvore até encontrar um nó folha.
void explorarSalas(Sala *raiz) {
    Sala *atual = raiz;
    char escolha;

    printf("\n=== BEM-VINDO AO DETECTIVE QUEST ===\n");
    printf("Sua missao e investigar a mansao.\n");

    // Loop de navegação: continua enquanto houver uma sala válida
    while (atual != NULL) {
        printf("\n------------------------------------------------\n");
        printf("VOCE ESTA EM: [%s]\n", atual->nome);

        // Verifica se é um nó-folha (sem filhos/saídas)
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("\n>> Fim da linha! Este comodo nao tem mais saidas.\n");
            printf(">> Investigacao concluida neste local.\n");
            break; // Sai do loop
        }

        // Menu de opções para o jogador
        printf("Caminhos disponiveis:\n");
        if (atual->esquerda != NULL) printf(" (e) Ir para a esquerda\n");
        if (atual->direita != NULL)  printf(" (d) Ir para a direita\n");
        
        printf("\nEscolha sua direcao (e/d) ou (s) para sair: ");
        scanf(" %c", &escolha); // O espaço antes de %c limpa o buffer do teclado

        // Lógica de movimentação
        if (escolha == 'e' || escolha == 'E') {
            if (atual->esquerda != NULL) {
                atual = atual->esquerda; // Move o ponteiro para o nó da esquerda
            } else {
                printf("\n[!] Nao ha passagem para a esquerda!\n");
            }
        } 
        else if (escolha == 'd' || escolha == 'D') {
            if (atual->direita != NULL) {
                atual = atual->direita; // Move o ponteiro para o nó da direita
            } else {
                printf("\n[!] Nao ha passagem para a direita!\n");
            }
        }
        else if (escolha == 's' || escolha == 'S') {
            printf("\nEncerrando a investigacao...\n");
            break;
        }
        else {
            printf("\n[!] Opcao invalida.\n");
        }
    }
}

// --- Função: main ---
// Objetivo: Montar o mapa inicial e dar início à exploração.
int main() {
    // 1. Criação da Raiz (Entrada)
    Sala *mapa = criarSala("Hall de Entrada");

    // 2. Construção manual da Árvore (Mapa da Mansão)
    // Nível 1
    mapa->esquerda = criarSala("Sala de Estar");
    mapa->direita = criarSala("Cozinha");

    // Nível 2 (Filhos da Sala de Estar)
    mapa->esquerda->esquerda = criarSala("Biblioteca");
    mapa->esquerda->direita = criarSala("Jardim de Inverno");

    // Nível 2 (Filhos da Cozinha)
    mapa->direita->esquerda = criarSala("Despensa");
    // A Cozinha não terá caminho à direita (será NULL)

    // Nível 3 (Um esconderijo secreto na Biblioteca)
    mapa->esquerda->esquerda->esquerda = criarSala("Passagem Secreta");

    // 3. Iniciar o Jogo
    explorarSalas(mapa);

    // Nota: Em um programa real, deveríamos ter uma função para liberar 
    // a memória (free) de todos os nós antes de sair, mas para o nível 
    // novato, o sistema operacional fará isso ao encerrar o programa.
    
    return 0;
}