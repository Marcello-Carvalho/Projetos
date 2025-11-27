#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// --- Definições de Constantes ---
#define TAM_FILA 5    // Tamanho fixo da fila de peças
#define TAM_PILHA 3   // Capacidade máxima da reserva

// --- Estruturas de Dados ---

// Representa uma peça individual
typedef struct {
    char nome; // Tipo da peça: 'I', 'O', 'T', 'L'
    int id;    // Identificador único
} Peca;

// Estrutura para a Fila Circular
typedef struct {
    Peca itens[TAM_FILA];
    int inicio;
    int fim;
    int qtde; // Quantidade atual de elementos
} FilaCircular;

// Estrutura para a Pilha (Reserva)
typedef struct {
    Peca itens[TAM_PILHA];
    int topo; // Índice do elemento no topo (-1 se vazia)
} PilhaReserva;

// Variável global para controlar o ID único das peças
int contadorIds = 0;

// --- Protótipos das Funções ---
Peca gerarPeca();
void inicializarFila(FilaCircular *f);
void inicializarPilha(PilhaReserva *p);
int filaCheia(FilaCircular *f);
int pilhaCheia(PilhaReserva *p);
int pilhaVazia(PilhaReserva *p);
void enfileirar(FilaCircular *f, Peca p);
Peca desenfileirar(FilaCircular *f);
void empilhar(PilhaReserva *p, Peca item);
Peca desempilhar(PilhaReserva *p);
void exibirEstado(FilaCircular *f, PilhaReserva *p);

// --- Funções Principais do Jogo ---

// Gera uma peça aleatória ('I', 'O', 'T', 'L') com ID sequencial
Peca gerarPeca() {
    Peca p;
    char tipos[] = {'I', 'O', 'T', 'L'};
    p.nome = tipos[rand() % 4];
    p.id = contadorIds++;
    return p;
}

// Inicializa a Fila e já a preenche (conforme requisito)
void inicializarFila(FilaCircular *f) {
    f->inicio = 0;
    f->fim = 0;
    f->qtde = 0;
    
    // Preenche a fila inicial
    for(int i = 0; i < TAM_FILA; i++) {
        enfileirar(f, gerarPeca());
    }
}

// Inicializa a Pilha com topo -1 (vazia)
void inicializarPilha(PilhaReserva *p) {
    p->topo = -1;
}

// --- Operações de Estrutura de Dados ---

// Adiciona peça ao final da fila (Lógica Circular)
void enfileirar(FilaCircular *f, Peca p) {
    if (f->qtde < TAM_FILA) {
        f->itens[f->fim] = p;
        // O operador % (módulo) garante o comportamento circular
        f->fim = (f->fim + 1) % TAM_FILA;
        f->qtde++;
    }
}

// Remove e retorna a peça do início da fila
Peca desenfileirar(FilaCircular *f) {
    Peca p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->qtde--;
    return p;
}

int pilhaCheia(PilhaReserva *p) {
    return p->topo == TAM_PILHA - 1;
}

int pilhaVazia(PilhaReserva *p) {
    return p->topo == -1;
}

// Adiciona peça ao topo da pilha
void empilhar(PilhaReserva *p, Peca item) {
    if (!pilhaCheia(p)) {
        p->topo++;
        p->itens[p->topo] = item;
    }
}

// Remove peça do topo da pilha
Peca desempilhar(PilhaReserva *p) {
    Peca pRemovida = p->itens[p->topo];
    p->topo--;
    return pRemovida;
}

// --- Visualização ---

void exibirEstado(FilaCircular *f, PilhaReserva *p) {
    printf("\n========================================\n");
    printf("ESTADO ATUAL DO JOGO:\n");
    
    // Exibir Fila
    printf("Fila de pecas:  [ ");
    int count = 0;
    int i = f->inicio;
    while(count < f->qtde) {
        printf("[%c %d] ", f->itens[i].nome, f->itens[i].id);
        i = (i + 1) % TAM_FILA;
        count++;
    }
    printf("]\n");

    // Exibir Pilha
    printf("Pilha reserva:  (Topo -> Base): [ ");
    if (pilhaVazia(p)) {
        printf("Vazia ");
    } else {
        for (int k = p->topo; k >= 0; k--) {
            printf("[%c %d] ", p->itens[k].nome, p->itens[k].id);
        }
    }
    printf("]\n");
    printf("========================================\n");
}

// --- Main e Controle ---

int main() {
    // Semente para gerar números aleatórios diferentes a cada execução
    srand(time(NULL));

    FilaCircular fila;
    PilhaReserva pilha;
    int opcao;

    // Inicialização
    inicializarFila(&fila);
    inicializarPilha(&pilha);

    do {
        exibirEstado(&fila, &pilha);

        printf("\nOpcoes de Acao:\n");
        printf("1 - Jogar peca (Da fila para o jogo)\n");
        printf("2 - Reservar peca (Da fila para a pilha)\n");
        printf("3 - Usar peca reservada (Da pilha para o jogo)\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: // Jogar peça
                {
                    Peca p = desenfileirar(&fila);
                    printf("\n>> Voce JOGOU a peca: [%c %d]\n", p.nome, p.id);
                    
                    // Regra: Uma nova peça é gerada automaticamente
                    Peca nova = gerarPeca();
                    enfileirar(&fila, nova);
                    printf(">> Nova peca gerada e adicionada a fila.\n");
                }
                break;

            case 2: // Reservar peça
                {
                    if (pilhaCheia(&pilha)) {
                        printf("\n[!] ERRO: A Pilha de reserva esta cheia! Jogue ou use uma peca.\n");
                    } else {
                        Peca p = desenfileirar(&fila);
                        empilhar(&pilha, p);
                        printf("\n>> Voce RESERVOU a peca: [%c %d]\n", p.nome, p.id);
                        
                        // Regra: Uma nova peça é gerada automaticamente na fila
                        Peca nova = gerarPeca();
                        enfileirar(&fila, nova);
                    }
                }
                break;

            case 3: // Usar peça reservada
                {
                    if (pilhaVazia(&pilha)) {
                        printf("\n[!] ERRO: Nao ha pecas na reserva para usar.\n");
                    } else {
                        Peca p = desempilhar(&pilha);
                        printf("\n>> Voce USOU a peca da reserva: [%c %d]\n", p.nome, p.id);
                    }
                }
                break;

            case 0:
                printf("\nSaindo do jogo...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}