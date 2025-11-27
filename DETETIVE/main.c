#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Estruturas de Dados ---

// 1. Estrutura para o MAPA (Árvore Binária Comum)
typedef struct Sala {
    char nome[50];
    char pista[100];        // Texto da pista (pode ser vazio se não houver)
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// 2. Estrutura para o INVENTÁRIO DE PISTAS (Árvore Binária de Busca - BST)
typedef struct NoPista {
    char texto[100];
    struct NoPista *esquerda;
    struct NoPista *direita;
} NoPista;

// --- Protótipos ---
Sala* criarSala(char *nome, char *pista);
NoPista* inserirPista(NoPista *raiz, char *texto);
void exibirPistas(NoPista *raiz);
void explorarSalasComPistas(Sala *mapa);

// --- Implementação das Funções ---

// Cria uma sala do mapa (Alocação Dinâmica)
Sala* criarSala(char *nome, char *pista) {
    Sala *nova = (Sala*) malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    strcpy(nova->pista, pista); // Copia a pista (pode ser string vazia "")
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

// Insere uma pista na BST mantendo a ordem alfabética
NoPista* inserirPista(NoPista *raiz, char *texto) {
    // Caso base: Se o nó for vazio, cria um novo aqui
    if (raiz == NULL) {
        NoPista *novo = (NoPista*) malloc(sizeof(NoPista));
        strcpy(novo->texto, texto);
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    }

    // Comparação alfabética (strcmp)
    // Se texto < raiz->texto (retorno negativo), vai para esquerda
    if (strcmp(texto, raiz->texto) < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, texto);
    }
    // Se texto > raiz->texto (retorno positivo), vai para direita
    else if (strcmp(texto, raiz->texto) > 0) {
        raiz->direita = inserirPista(raiz->direita, texto);
    }
    // Se for igual (= 0), não faz nada (evita duplicatas na lista)

    return raiz;
}

// Exibe as pistas usando percurso Em-Ordem (In-Order) para sair alfabético
void exibirPistas(NoPista *raiz) {
    if (raiz != NULL) {
        exibirPistas(raiz->esquerda);      // 1. Visita subárvore esquerda (menores)
        printf("- %s\n", raiz->texto);     // 2. Visita a raiz (atual)
        exibirPistas(raiz->direita);       // 3. Visita subárvore direita (maiores)
    }
}

// Controla a navegação e a coleta
void explorarSalasComPistas(Sala *mapa) {
    Sala *atual = mapa;
    NoPista *inventarioPistas = NULL; // Começamos sem pistas
    char escolha;

    printf("\n=== DETECTIVE QUEST: NIVEL AVENTUREIRO ===\n");
    printf("Colete pistas e encontre o culpado!\n");

    while (atual != NULL) {
        printf("\n------------------------------------------------\n");
        printf("LOCAL: [%s]\n", atual->nome);

        // --- Coleta Automática de Pistas ---
        // Verifica se a sala tem uma pista (string não vazia)
        if (strlen(atual->pista) > 0) {
            printf(">> PISTA ENCONTRADA: \"%s\"\n", atual->pista);
            // Insere na BST
            inventarioPistas = inserirPista(inventarioPistas, atual->pista);
        } else {
            printf("(Nenhuma pista neste local)\n");
        }

        // --- Menu de Navegação ---
        printf("\nCaminhos:\n");
        if (atual->esquerda) printf(" (e) %s\n", atual->esquerda->nome);
        if (atual->direita)  printf(" (d) %s\n", atual->direita->nome);
        
        printf("\nDigite (e/d) para mover ou (s) para encerrar e ver relatorio: ");
        scanf(" %c", &escolha);

        if (escolha == 's' || escolha == 'S') {
            break; // Sai do loop
        }
        else if ((escolha == 'e' || escolha == 'E') && atual->esquerda) {
            atual = atual->esquerda;
        }
        else if ((escolha == 'd' || escolha == 'D') && atual->direita) {
            atual = atual->direita;
        }
        else {
            printf("\n[!] Direcao invalida ou caminho sem saida!\n");
        }
    }

    // --- Fim do Jogo: Exibição do Relatório ---
    printf("\n================================================\n");
    printf("RELATORIO FINAL - PISTAS COLETADAS (Ordem Alfabetica)\n");
    printf("================================================\n");
    
    if (inventarioPistas == NULL) {
        printf("Nenhuma pista foi coletada.\n");
    } else {
        exibirPistas(inventarioPistas);
    }
    printf("================================================\n");
}

// --- Main ---
int main() {
    // 1. Construção do Mapa (Árvore Fixa)
    // Estrutura: Nome da Sala, Pista (ou "" se vazio)
    
    Sala *hall = criarSala("Hall de Entrada", ""); // Sem pista no Hall
    
    // Lado Esquerdo da Mansão
    hall->esquerda = criarSala("Sala de Estar", "Relogio parado as 10h");
    hall->esquerda->esquerda = criarSala("Biblioteca", "Livro sobre venenos aberto");
    hall->esquerda->direita = criarSala("Jardim", "Pegadas de lama tamanho 42");

    // Lado Direito da Mansão
    hall->direita = criarSala("Cozinha", "");
    hall->direita->esquerda = criarSala("Despensa", "Garrafa de veneno vazia");
    hall->direita->direita = criarSala("Sotao", "Diario oculto do mordomo");

    // 2. Iniciar Jogo
    explorarSalasComPistas(hall);

    return 0;
}