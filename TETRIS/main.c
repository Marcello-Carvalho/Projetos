#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// --- Definições de Constantes ---
#define TAM_FILA 5    // Fila mantém 5 elementos
#define TAM_PILHA 3   // Pilha limitada a 3 elementos (crucial para a troca múltipla)

// --- Estruturas de Dados ---

typedef struct {
    char nome; // 'I', 'O', 'T', 'L'
    int id;
} Peca;

typedef struct {
    Peca itens[TAM_FILA];
    int inicio;
    int fim;
    int qtde;
} FilaCircular;

typedef struct {
    Peca itens[TAM_PILHA];
    int topo; 
} PilhaReserva;

int contadorIds = 0;

// --- Protótipos ---
Peca gerarPeca();
void inicializarFila(FilaCircular *f);
void inicializarPilha(PilhaReserva *p);
int pilhaCheia(PilhaReserva *p);
int pilhaVazia(PilhaReserva *p);
int filaVazia(FilaCircular *f); // Segurança extra
void enfileirar(FilaCircular *f, Peca p);
Peca desenfileirar(FilaCircular *f);
void empilhar(PilhaReserva *p, Peca item);
Peca desempilhar(PilhaReserva *p);
void exibirEstado(FilaCircular *f, PilhaReserva *p);

// Funções Avançadas de Troca
void trocarPecaAtual(FilaCircular *f, PilhaReserva *p);
void trocaMultipla(FilaCircular *f, PilhaReserva *p);

// --- Implementação ---

Peca gerarPeca() {
    Peca p;
    char tipos[] = {'I', 'O', 'T', 'L'};
    p.nome = tipos[rand() % 4];
    p.id = contadorIds++;
    return p;
}

void inicializarFila(FilaCircular *f) {
    f->inicio = 0;
    f->fim = 0;
    f->qtde = 0;
    for(int i = 0; i < TAM_FILA; i++) {
        enfileirar(f, gerarPeca());
    }
}

void inicializarPilha(PilhaReserva *p) {
    p->topo = -1;
}

// Lógica de Fila Circular
void enfileirar(FilaCircular *f, Peca p) {
    if (f->qtde < TAM_FILA) {
        f->itens[f->fim] = p;
        f->fim = (f->fim + 1) % TAM_FILA;
        f->qtde++;
    }
}

Peca desenfileirar(FilaCircular *f) {
    Peca p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->qtde--;
    return p;
}

int pilhaCheia(PilhaReserva *p) { return p->topo == TAM_PILHA - 1; }
int pilhaVazia(PilhaReserva *p) { return p->topo == -1; }
int filaVazia(FilaCircular *f) { return f->qtde == 0; }

void empilhar(PilhaReserva *p, Peca item) {
    if (!pilhaCheia(p)) {
        p->topo++;
        p->itens[p->topo] = item;
    }
}

Peca desempilhar(PilhaReserva *p) {
    Peca pRemovida = p->itens[p->topo];
    p->topo--;
    return pRemovida;
}

// --- NOVAS FUNÇÕES (REQUISITOS AVANÇADOS) ---

// Opção 4: Troca a peça da frente da fila com o topo da pilha
void trocarPecaAtual(FilaCircular *f, PilhaReserva *p) {
    if (pilhaVazia(p)) {
        printf("\n[!] ERRO: Impossivel trocar. A pilha esta vazia.\n");
        return;
    }
    if (filaVazia(f)) {
        printf("\n[!] ERRO: Impossivel trocar. A fila esta vazia.\n");
        return;
    }

    // Realiza a troca (Swap)
    Peca temp = f->itens[f->inicio]; // Salva a da fila
    f->itens[f->inicio] = p->itens[p->topo]; // Fila recebe da Pilha
    p->itens[p->topo] = temp; // Pilha recebe a antiga da Fila
    
    printf("\n>> TROCA REALIZADA: Frente da fila <-> Topo da pilha.\n");
}

// Opção 5: Troca os 3 primeiros da fila com os 3 da pilha
void trocaMultipla(FilaCircular *f, PilhaReserva *p) {
    // Validação: Pilha precisa ter 3 peças e Fila pelo menos 3
    if (p->topo < 2) { // Índices 0, 1, 2 devem existir
        printf("\n[!] ERRO: A pilha precisa ter 3 pecas para a troca multipla.\n");
        return;
    }
    if (f->qtde < 3) {
        printf("\n[!] ERRO: A fila precisa ter pelo menos 3 pecas.\n");
        return;
    }

    printf("\n>> REALIZANDO TROCA MULTIPLA (BLOCO DE 3)...\n");

    // Loop para trocar 3 elementos
    // i=0 é o primeiro da fila/topo da pilha
    // i=1 é o segundo da fila/segundo da pilha, etc.
    for (int i = 0; i < 3; i++) {
        // Cálculo do índice circular na fila
        int idxFila = (f->inicio + i) % TAM_FILA;
        
        // Cálculo do índice na pilha (Topo, Topo-1, Topo-2)
        int idxPilha = p->topo - i;

        // Swap
        Peca temp = f->itens[idxFila];
        f->itens[idxFila] = p->itens[idxPilha];
        p->itens[idxPilha] = temp;
    }
    printf(">> Troca multipla concluida com sucesso!\n");
}

// --- Visualização ---

void exibirEstado(FilaCircular *f, PilhaReserva *p) {
    printf("\n========================================\n");
    printf("ESTADO ATUAL:\n");
    
    printf("Fila de pecas:  [ ");
    int count = 0;
    int i = f->inicio;
    while(count < f->qtde) {
        printf("[%c %d] ", f->itens[i].nome, f->itens[i].id);
        i = (i + 1) % TAM_FILA;
        count++;
    }
    printf("]\n");

    printf("Pilha reserva:  (Topo -> Base): [ ");
    if (pilhaVazia(p)) {
        printf("Vazia ");
    } else {
        // Exibe do topo para a base
        for (int k = p->topo; k >= 0; k--) {
            printf("[%c %d] ", p->itens[k].nome, p->itens[k].id);
        }
    }
    printf("]\n");
    printf("========================================\n");
}

// --- Main ---

int main() {
    srand(time(NULL));
    FilaCircular fila;
    PilhaReserva pilha;
    int opcao;

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    do {
        exibirEstado(&fila, &pilha);

        printf("\nOpcoes disponiveis:\n");
        printf("1 - Jogar peca (Remove da fila)\n");
        printf("2 - Reservar peca (Envia para pilha)\n");
        printf("3 - Usar peca da pilha de reserva\n");
        printf("4 - Trocar peca da frente da fila com o topo da pilha\n");
        printf("5 - Trocar os 3 primeiros da fila com as 3 pecas da pilha\n");
        printf("0 - Sair\n");
        printf("Opcao escolhida: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: // Jogar
                {
                    Peca p = desenfileirar(&fila);
                    printf("\n>> JOGAR: Voce usou a peca [%c %d]\n", p.nome, p.id);
                    enfileirar(&fila, gerarPeca()); // Auto-refill
                }
                break;

            case 2: // Reservar
                {
                    if (pilhaCheia(&pilha)) {
                        printf("\n[!] A Pilha esta cheia! Nao e possivel reservar.\n");
                    } else {
                        Peca p = desenfileirar(&fila);
                        empilhar(&pilha, p);
                        printf("\n>> RESERVAR: Peca [%c %d] movida para a pilha.\n", p.nome, p.id);
                        enfileirar(&fila, gerarPeca()); // Auto-refill
                    }
                }
                break;

            case 3: // Usar Reserva
                {
                    if (pilhaVazia(&pilha)) {
                        printf("\n[!] A Pilha esta vazia!\n");
                    } else {
                        Peca p = desempilhar(&pilha);
                        printf("\n>> USAR RESERVA: Peca [%c %d] trazida ao jogo.\n", p.nome, p.id);
                    }
                }
                break;
            
            case 4: // Troca Simples
                trocarPecaAtual(&fila, &pilha);
                break;

            case 5: // Troca Múltipla
                trocaMultipla(&fila, &pilha);
                break;

            case 0:
                printf("\nEncerrando programa...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}