#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20

// 1. Criação de Structs
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// Protótipos das funções
void carregarDados(Componente arr[], int *n);
void mostrarComponentes(Componente arr[], int n);
long bubbleSortNome(Componente arr[], int n);
long insertionSortTipo(Componente arr[], int n);
long selectionSortPrioridade(Componente arr[], int n);
int buscaBinariaPorNome(Componente arr[], int n, char chave[]);

int main() {
    Componente lista[MAX_COMPONENTES];
    int qtd = 0;
    int opcao;
    int ordenadoPorNome = 0; // Flag para controlar regra da busca binária
    clock_t inicio, fim;
    double tempo_gasto;
    long comparacoes;


    do {
        printf("\n=== SISTEMA DE MONTAGEM DA TORRE DE FUGA ===\n");
        printf("1. Cadastrar Componentes (Manual)\n");
        printf("2. Mostrar Componentes Atuais\n");
        printf("3. Ordenar por NOME (Bubble Sort)\n");
        printf("4. Ordenar por TIPO (Insertion Sort)\n");
        printf("5. Ordenar por PRIORIDADE (Selection Sort)\n");
        printf("6. Buscar Componente (Busca Binaria - Requer Ordenacao por Nome)\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpar buffer do teclado

        switch(opcao) {
            case 1:
                carregarDados(lista, &qtd);
                ordenadoPorNome = 0; // Novos dados inseridos, perde a ordenação
                break;
            case 2:
                mostrarComponentes(lista, qtd);
                break;
            case 3:
                printf("\nExecutando Bubble Sort por Nome...\n");
                inicio = clock();
                comparacoes = bubbleSortNome(lista, qtd);
                fim = clock();
                tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                
                mostrarComponentes(lista, qtd);
                printf("\n[Performance] Comparacoes: %ld | Tempo: %f segundos\n", comparacoes, tempo_gasto);
                ordenadoPorNome = 1; // Flag ativada
                break;
            case 4:
                printf("\nExecutando Insertion Sort por Tipo...\n");
                inicio = clock();
                comparacoes = insertionSortTipo(lista, qtd);
                fim = clock();
                tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                
                mostrarComponentes(lista, qtd);
                printf("\n[Performance] Comparacoes: %ld | Tempo: %f segundos\n", comparacoes, tempo_gasto);
                ordenadoPorNome = 0;
                break;
            case 5:
                printf("\nExecutando Selection Sort por Prioridade...\n");
                inicio = clock();
                comparacoes = selectionSortPrioridade(lista, qtd);
                fim = clock();
                tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                
                mostrarComponentes(lista, qtd);
                printf("\n[Performance] Comparacoes: %ld | Tempo: %f segundos\n", comparacoes, tempo_gasto);
                ordenadoPorNome = 0;
                break;
            case 6:
                if (!ordenadoPorNome) {
                    printf("\n[ERRO] A Busca Binaria so pode ser realizada apos ordenar por NOME (Opcao 3).\n");
                } else {
                    char chave[30];
                    printf("Digite o nome do componente-chave: ");
                    // Leitura de string com espaços
                    fgets(chave, 30, stdin);
                    chave[strcspn(chave, "\n")] = 0; // Remove o \n do final

                    int pos = buscaBinariaPorNome(lista, qtd, chave);
                    if (pos != -1) {
                        printf("\n[SUCESSO] Componente-chave encontrado na posicao %d!\n", pos + 1);
                        printf("Nome: %s | Tipo: %s | Prioridade: %d\n", lista[pos].nome, lista[pos].tipo, lista[pos].prioridade);
                        printf("Montagem desbloqueada!\n");
                    } else {
                        printf("\n[FALHA] Componente '%s' nao encontrado na lista.\n", chave);
                    }
                }
                break;
            case 0:
                printf("Encerrando sistema...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}

// === IMPLEMENTAÇÃO DAS FUNÇÕES ===

// 2. Entrada de Dados
void carregarDados(Componente arr[], int *n) {
    if (*n >= MAX_COMPONENTES) {
        printf("Limite de componentes atingido!\n");
        return;
    }
    
    printf("Nome do Componente: ");
    fgets(arr[*n].nome, 30, stdin);
    arr[*n].nome[strcspn(arr[*n].nome, "\n")] = 0; // Remove newline

    printf("Tipo do Componente: ");
    fgets(arr[*n].tipo, 20, stdin);
    arr[*n].tipo[strcspn(arr[*n].tipo, "\n")] = 0;

    printf("Prioridade (1-10): ");
    scanf("%d", &arr[*n].prioridade);
    getchar(); // Consumir newline do buffer

    (*n)++;
    printf("Componente cadastrado com sucesso!\n");
}

void mostrarComponentes(Componente arr[], int n) {
    if (n == 0) {
        printf("\nNenhum componente cadastrado.\n");
        return;
    }
    printf("\n%-30s | %-20s | %s\n", "NOME", "TIPO", "PRIORIDADE");
    printf("-------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-30s | %-20s | %d\n", arr[i].nome, arr[i].tipo, arr[i].prioridade);
    }
}

// 3. Opções de Ordenação e 5. Medição de desempenho

// Bubble Sort: Ordenar por NOME
long bubbleSortNome(Componente arr[], int n) {
    long comps = 0;
    Componente temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comps++; // Contabiliza comparação
            if (strcmp(arr[j].nome, arr[j+1].nome) > 0) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    return comps;
}

// Insertion Sort: Ordenar por TIPO
long insertionSortTipo(Componente arr[], int n) {
    long comps = 0;
    int i, j;
    Componente key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        // Loop do insertion (conta comparações dentro do while)
        while (j >= 0) {
            comps++;
            if (strcmp(arr[j].tipo, key.tipo) > 0) {
                arr[j + 1] = arr[j];
                j = j - 1;
            } else {
                break;
            }
        }
        arr[j + 1] = key;
    }
    return comps;
}

// Selection Sort: Ordenar por PRIORIDADE
long selectionSortPrioridade(Componente arr[], int n) {
    long comps = 0;
    int i, j, min_idx;
    Componente temp;

    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            comps++; // Contabiliza comparação
            if (arr[j].prioridade < arr[min_idx].prioridade) {
                min_idx = j;
            }
        }
        // Troca
        temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
    return comps;
}

// 4. Busca Binária
int buscaBinariaPorNome(Componente arr[], int n, char chave[]) {
    int inicio = 0;
    int fim = n - 1;
    
    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        int res = strcmp(arr[meio].nome, chave);

        if (res == 0) return meio; // Encontrou
        if (res < 0) inicio = meio + 1; // Está na metade superior
        else fim = meio - 1; // Está na metade inferior
    }
    return -1; // Não encontrou
}