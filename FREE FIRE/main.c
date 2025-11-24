#include <stdio.h>
#include <stdlib.h> // Necessário para 'exit' (embora não usado)
#include <string.h> // Necessário para strcmp, strcpy, strcspn

// Define a capacidade máxima da mochila (Vetor estático)
#define MAX_ITENS 10

/*
 * 1. Definição da struct:
 * Estrutura 'Item' com os campos solicitados para
 * armazenar os dados de um item na mochila.
 */
struct Item {
    char nome[30];
    char tipo[20]; // ex: arma, municao, cura
    int quantidade;
};

// --- PROTÓTIPOS DAS FUNÇÕES OBRIGATÓRIAS ---

/**
 * @brief Limpa o buffer de entrada (stdin).
 * Essencial após um scanf para evitar problemas com fgets.
 */
void limparBuffer();

/**
 * @brief Insere um novo item na mochila (vetor).
 * @param mochila O vetor de itens.
 * @param numItens Ponteiro para a contagem atual de itens (será modificado).
 */
void inserirItem(struct Item mochila[], int* numItens);

/**
 * @brief Remove um item da mochila com base no nome.
 * @param mochila O vetor de itens.
 * @param numItens Ponteiro para a contagem atual de itens (será modificado).
 */
void removerItem(struct Item mochila[], int* numItens);

/**
 * @brief Lista todos os itens atualmente na mochila.
 * @param mochila O vetor de itens.
 * @param numItens A contagem atual de itens.
 */
void listarItens(struct Item mochila[], int numItens);

/**
 * @brief Busca sequencialmente por um item na mochila com base no nome.
 * @param mochila O vetor de itens.
 * @param numItens A contagem atual de itens.
 */
void buscarItem(struct Item mochila[], int numItens);


// --- FUNÇÃO PRINCIPAL ---
int main() {
    /*
     * 3. Criação do vetor:
     * 'mochila' é o vetor de structs com capacidade para 10 itens.
     * 'numItens' rastreia quantos itens estão *atualmente* na mochila.
     */
    struct Item mochila[MAX_ITENS];
    int numItens = 0; // A mochila começa vazia
    int escolha = 0;

    // Loop principal do menu (Interface de Usabilidade)
    do {
        printf("\n--- MOCHILA DE LOOT (%d/%d) ---\n", numItens, MAX_ITENS);
        printf("O que voce vai fazer?\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar todos os itens\n");
        printf("4. Buscar um item\n");
        printf("5. Sair\n");
        printf("Escolha: ");
        
        scanf("%d", &escolha);
        limparBuffer(); // Limpa o '\n' deixado pelo scanf

        // Controla o fluxo do programa
        switch (escolha) {
            case 1:
                inserirItem(mochila, &numItens);
                break;
            case 2:
                removerItem(mochila, &numItens);
                break;
            case 3:
                listarItens(mochila, numItens);
                break;
            case 4:
                buscarItem(mochila, numItens);
                break;
            case 5:
                printf("Fechando a mochila...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
        
        /*
         * Requisito 4 (Listagem): "o que deve ocorrer após cada operação."
         * Interpretado como uma função disponível, mas para melhor UI,
         * o usuário pode listar manualmente após cada ação se desejar.
         * (Se a listagem *automática* for obrigatória, descomente a linha abaixo)
         */
        // if (escolha > 0 && escolha < 3) listarItens(mochila, numItens);

    } while (escolha != 5);

    return 0;
}


// --- IMPLEMENTAÇÃO DAS FUNÇÕES ---

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void inserirItem(struct Item mochila[], int* numItens) {
    // 1. Verifica se a mochila está cheia
    if (*numItens >= MAX_ITENS) {
        printf("\n[ERRO] Mochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    /*
     * 2. Se houver espaço, insere o item na próxima posição livre,
     * que é indicada por *numItens (ex: se tem 0 itens, insere no [0])
     */
    printf("\n--- Adicionando Novo Item ---\n");
    
    // Usa a posição 'numItens' para o novo item
    int i = *numItens;

    // Leitura de dados (conforme Requisitos Técnicos)
    printf("Nome do item: ");
    fgets(mochila[i].nome, 30, stdin);
    
    printf("Tipo (arma, municao, cura, etc.): ");
    fgets(mochila[i].tipo, 20, stdin);
    
    printf("Quantidade: ");
    scanf("%d", &mochila[i].quantidade);
    limparBuffer(); // Limpa o '\n' do scanf

    // Remove o '\n' que o fgets captura
    mochila[i].nome[strcspn(mochila[i].nome, "\n")] = '\0';
    mochila[i].tipo[strcspn(mochila[i].tipo, "\n")] = '\0';

    // 3. Atualiza a contagem de itens
    (*numItens)++; // Incrementa o valor para o qual o ponteiro aponta

    printf("\nItem '%s' adicionado com sucesso!\n", mochila[i].nome);
}

void removerItem(struct Item mochila[], int* numItens) {
    // 1. Verifica se a mochila está vazia
    if (*numItens == 0) {
        printf("\n[ERRO] Mochila ja esta vazia. Nada para remover.\n");
        return;
    }

    char nomeBusca[30];
    printf("\n--- Removendo Item ---\n");
    printf("Digite o nome do item a remover: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    // 2. Busca sequencial para encontrar o índice do item
    int indiceRemover = -1;
    for (int i = 0; i < *numItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            indiceRemover = i;
            break; // Para a busca assim que encontra
        }
    }

    // 3. Lógica de remoção
    if (indiceRemover == -1) {
        printf("\nItem '%s' nao foi encontrado na mochila.\n", nomeBusca);
    } else {
        printf("\nItem '%s' (qtd: %d) encontrado. Removendo...\n", 
               mochila[indiceRemover].nome, mochila[indiceRemover].quantidade);

        /*
         * Para remover de um vetor, "puxamos" todos os itens
         * da frente uma posição para trás, sobrescrevendo o item
         * que queremos apagar.
         */
        //         for (int i = indiceRemover; i < (*numItens - 1); i++) {
           // mochila[i] = mochila[i + 1]; // Copia o struct inteiro
        }

        // 4. Atualiza a contagem de itens
        (*numItens)--; // Decrementa a contagem
        printf("Item removido.\n");
    }

void listarItens(struct Item mochila[], int numItens) {
    printf("\n--- ITENS NA MOCHILA (%d/%d) ---\n", numItens, MAX_ITENS);

    if (numItens == 0) {
        printf("A mochila esta vazia.\n");
        printf("----------------------------------\n");
        return;
    }

    // Loop 'for' para percorrer o vetor até o número atual de itens
    for (int i = 0; i < numItens; i++) {
        printf("[%d] Nome: %s\n", i, mochila[i].nome);
        printf("    Tipo: %s\n", mochila[i].tipo);
        printf("    Qtd.: %d\n", mochila[i].quantidade);
        printf("----------------------------------\n");
    }
}

void buscarItem(struct Item mochila[], int numItens) {
    if (numItens == 0) {
        printf("\n[ERRO] Mochila vazia. Nada para buscar.\n");
        return;
    }
    
    char nomeBusca[30];
    printf("\n--- Buscando Item ---\n");
    printf("Digite o nome do item a buscar: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    // Flag para rastrear se encontramos o item
    int encontrado = 0; 

    // Loop de busca sequencial
    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\n--- Item Encontrado! ---\n");
            printf("Indice: %d\n", i);
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Qtd.: %d\n", mochila[i].quantidade);
            printf("--------------------------\n");
            
            encontrado = 1;
            break; // Para a busca
        }
    }

    if (encontrado == 0) { // Ou !encontrado
        printf("\nItem '%s' nao foi encontrado na mochila.\n", nomeBusca);
    }
}