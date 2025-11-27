#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_HASH 13 // Tamanho da tabela hash (número primo para melhor distribuição)

// --- ESTRUTURAS DE DADOS ---

// 1. MAPA (Árvore Binária)
typedef struct Sala {
    char nome[50];
    char pista[50]; // Pista encontrada neste local
    struct Sala *esq;
    struct Sala *dir;
} Sala;

// 2. INVENTÁRIO (BST - Árvore Binária de Busca)
typedef struct NoPista {
    char pista[50];
    struct NoPista *esq;
    struct NoPista *dir;
} NoPista;

// 3. CONHECIMENTO (Tabela Hash - Encadeamento para colisões)
typedef struct HashNode {
    char pista[50];
    char suspeito[50];
    struct HashNode *prox;
} HashNode;

// Variável global para a tabela hash
HashNode* tabelaHash[TAM_HASH];

// --- PROTÓTIPOS ---
// Funções de Mapa
Sala* criarSala(char *nome, char *pista);
void explorarSalas(Sala *mapa);

// Funções de BST (Pistas)
NoPista* inserirPista(NoPista *raiz, char *pista);
void listarPistas(NoPista *raiz);

// Funções de Hash (Associações)
int funcaoHash(char *chave);
void inserirNaHash(char *pista, char *suspeito);
char* encontrarSuspeito(char *pista);
void inicializarHash();

// Funções de Jogo (Lógica Final)
void verificarSuspeitoFinal(NoPista *inventario);
int contarEvidencias(NoPista *raiz, char *acusado);

// --- IMPLEMENTAÇÃO ---

// --- 1. Funções da Tabela Hash ---

void inicializarHash() {
    for (int i = 0; i < TAM_HASH; i++) {
        tabelaHash[i] = NULL;
    }
}

// Calcula índice baseado na soma ASCII dos caracteres
int funcaoHash(char *chave) {
    int soma = 0;
    for (int i = 0; chave[i] != '\0'; i++) {
        soma += chave[i];
    }
    return soma % TAM_HASH;
}

// Associa uma pista a um suspeito na tabela
void inserirNaHash(char *pista, char *suspeito) {
    int indice = funcaoHash(pista);
    HashNode *novo = (HashNode*) malloc(sizeof(HashNode));
    strcpy(novo->pista, pista);
    strcpy(novo->suspeito, suspeito);
    novo->prox = tabelaHash[indice]; // Insere no início da lista (encadeamento)
    tabelaHash[indice] = novo;
}

// Consulta quem é o suspeito ligado a uma pista
char* encontrarSuspeito(char *pista) {
    int indice = funcaoHash(pista);
    HashNode *atual = tabelaHash[indice];
    while (atual != NULL) {
        if (strcmp(atual->pista, pista) == 0) {
            return atual->suspeito;
        }
        atual = atual->prox;
    }
    return "Desconhecido";
}

// --- 2. Funções da BST (Inventário) ---

NoPista* inserirPista(NoPista *raiz, char *pista) {
    if (raiz == NULL) {
        NoPista *novo = (NoPista*) malloc(sizeof(NoPista));
        strcpy(novo->pista, pista);
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    }
    // Ordena alfabeticamente
    if (strcmp(pista, raiz->pista) < 0) {
        raiz->esq = inserirPista(raiz->esq, pista);
    } else if (strcmp(pista, raiz->pista) > 0) {
        raiz->dir = inserirPista(raiz->dir, pista);
    }
    return raiz;
}

void listarPistas(NoPista *raiz) {
    if (raiz != NULL) {
        listarPistas(raiz->esq);
        printf("- %s (Aponta para: %s)\n", raiz->pista, encontrarSuspeito(raiz->pista));
        listarPistas(raiz->dir);
    }
}

// --- 3. Funções do Mapa (Árvore) ---

Sala* criarSala(char *nome, char *pista) {
    Sala *nova = (Sala*) malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    strcpy(nova->pista, pista);
    nova->esq = NULL;
    nova->dir = NULL;
    return nova;
}

// --- 4. Motor do Jogo ---

// Função auxiliar recursiva para contar provas na BST contra um suspeito
int contarEvidencias(NoPista *raiz, char *acusado) {
    if (raiz == NULL) return 0;
    
    int count = 0;
    char *suspeitoDaPista = encontrarSuspeito(raiz->pista);
    
    // Compara o suspeito desta pista com o acusado (case sensitive simples)
    if (strcmp(suspeitoDaPista, acusado) == 0) {
        count = 1;
    }
    
    return count + contarEvidencias(raiz->esq, acusado) + contarEvidencias(raiz->dir, acusado);
}

void verificarSuspeitoFinal(NoPista *inventario) {
    char acusado[50];
    printf("\n=== FASE DE ACUSACAO ===\n");
    printf("Baseado nas pistas coletadas:\n");
    listarPistas(inventario);
    
    printf("\nQuem e o culpado? (Digite o nome exato, ex: Mordomo): ");
    scanf(" %s", acusado);

    int provas = contarEvidencias(inventario, acusado);

    printf("\n>> Analisando evidencias contra %s...\n", acusado);
    printf(">> Total de provas encontradas: %d\n", provas);

    if (provas >= 2) {
        printf("\n[SUCESSO] Parabens! Voce reuniu provas suficientes e prendeu o culpado!\n");
    } else {
        printf("\n[FRACASSO] Provas insuficientes. O advogado de defesa anulou o caso.\n");
        printf("(Dica: Voce precisa de pelo menos 2 pistas que apontem para o mesmo suspeito).\n");
    }
}

void explorarSalas(Sala *mapa) {
    Sala *atual = mapa;
    NoPista *meuInventario = NULL;
    char escolha;

    printf("\n--- DETECTIVE QUEST: MASTER EDITION ---\n");

    while (atual != NULL) {
        printf("\n-----------------------------------\n");
        printf("VOCE ESTA EM: [%s]\n", atual->nome);

        // Coleta automática
        if (strlen(atual->pista) > 0) {
            // Verifica se já temos essa pista (simplificado: insere sempre, a BST trata dups ou ignora)
            printf(">> ENCONTRADO: Pista \"%s\"\n", atual->pista);
            meuInventario = inserirPista(meuInventario, atual->pista);
            
            // Truque de jogo: remove a pista da sala para não pegar de novo
            strcpy(atual->pista, ""); 
        }

        printf("Opcoes: (e)squerda, (d)ireita, (s)air para acusar: ");
        scanf(" %c", &escolha);

        if (escolha == 's' || escolha == 'S') {
            break;
        } else if ((escolha == 'e' || escolha == 'E') && atual->esq) {
            atual = atual->esq;
        } else if ((escolha == 'd' || escolha == 'D') && atual->dir) {
            atual = atual->dir;
        } else {
            printf("[!] Caminho invalido.\n");
        }
    }

    verificarSuspeitoFinal(meuInventario);
}

// --- MAIN ---

int main() {
    inicializarHash();

    // 1. Configurar "Banco de Dados" (Pista -> Suspeito)
    // O Mordomo é o culpado neste cenário (tem 2 pistas)
    inserirNaHash("Relogio", "Mordomo");
    inserirNaHash("Luvas", "Mordomo");
    inserirNaHash("Pegadas", "Jardineiro");
    inserirNaHash("Veneno", "Governanta");

    // 2. Construir o Mapa (Árvore)
    Sala *hall = criarSala("Hall", "");
    
    // Caminho Esquerda
    hall->esq = criarSala("Sala de Estar", "Relogio");
    hall->esq->esq = criarSala("Biblioteca", "Luvas");
    
    // Caminho Direita
    hall->dir = criarSala("Cozinha", "Veneno");
    hall->dir->dir = criarSala("Jardim", "Pegadas");

    // 3. Iniciar Jogo
    explorarSalas(hall);

    return 0;
}