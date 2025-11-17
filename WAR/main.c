#include <stdio.h>
#include <stdlib.h> // Para malloc, free, rand, srand, atoi
#include <string.h> // Para strcpy, strcspn, strcmp
#include <time.h>   // Para srand(time(NULL))

/*
 * 1. Struct Atualizada:
 * Conforme as instruções, esta é a definição da struct.
 */
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

// --- PROTÓTIPOS DAS FUNÇÕES (Modularização) ---

// Função auxiliar para limpar o buffer de entrada após um scanf
void limparBuffer();

// Função para cadastrar os territórios (usa ponteiro para o mapa)
void cadastrarTerritorios(struct Territorio* mapa, int tamanho);

// Função para exibir os territórios
void exibirTerritorios(struct Territorio* mapa, int tamanho);

// Função para simular a rolagem de um dado (1 a 6)
int rolarDado();

// Função de ataque (usa ponteiros para atacante e defensor)
void atacar(struct Territorio* atacante, struct Territorio* defensor);

// Função para liberar a memória alocada dinamicamente
void liberarMemoria(struct Territorio* mapa);


// --- FUNÇÃO PRINCIPAL ---
int main() {
    // Requisito: Inicializar o gerador de números aleatórios
    srand(time(NULL));

    int numTerritorios;
    int indiceAtacante, indiceDefensor;
    char buffer[20]; // Buffer para leitura segura de números

    // Pergunta ao usuário o tamanho do mapa
    printf("Quantos territorios existem no mapa? ");
    fgets(buffer, 20, stdin);
    numTerritorios = atoi(buffer); // Converte string para inteiro

    if (numTerritorios <= 1) {
        printf("E preciso de pelo menos 2 territorios para jogar.\n");
        return 1; // Encerra se não for possível jogar
    }

    /*
     * 2. Alocação Dinâmica de Memória:
     * Aloca memória para o vetor de structs usando calloc.
     * calloc(N, tamanho) aloca N * tamanho bytes e inicializa com zeros.
     */
    struct Territorio* mapa = (struct Territorio*)calloc(numTerritorios, sizeof(struct Territorio));
    
    // Verifica se a alocação de memória falhou
    if (mapa == NULL) {
        printf("Erro fatal! Falha ao alocar memoria.\n");
        return 1;
    }
    printf("Memoria para %d territorios alocada com sucesso.\n", numTerritorios);

    // --- CADASTRO ---
    cadastrarTerritorios(mapa, numTerritorios);

    // --- EXIBIÇÃO INICIAL ---
    exibirTerritorios(mapa, numTerritorios);

    // --- FASE DE ATAQUE ---
    printf("\n--- FASE DE ATAQUE ---\n");
    
    printf("Digite o INDICE do territorio ATACANTE (0 a %d): ", numTerritorios - 1);
    fgets(buffer, 20, stdin);
    indiceAtacante = atoi(buffer);

    printf("Digite o INDICE do territorio DEFENSOR (0 a %d): ", numTerritorios - 1);
    fgets(buffer, 20, stdin);
    indiceDefensor = atoi(buffer);

    /*
     * 3. Validação de Escolhas (Requisitos Técnicos):
     * Verifica se os índices são válidos e se não é um auto-ataque.
     */
    
    // 1. Validação de índices (se estão dentro do mapa)
    if (indiceAtacante < 0 || indiceAtacante >= numTerritorios ||
        indiceDefensor < 0 || indiceDefensor >= numTerritorios) {
        
        printf("Ataque invalido! Indices fora do limite do mapa.\n");
    
    // 2. Validação de suicídio ("atacar o próprio território")
    } else if (indiceAtacante == indiceDefensor) {
        
        printf("Ataque invalido! Um territorio nao pode atacar a si mesmo.\n");
    
    // 3. Se tudo OK, executa o ataque
    } else {
        
        /*
         * 4. Uso de Ponteiros:
         * Passamos o ENDEREÇO de memória (&) do elemento do array
         * para a função de ataque.
         */
        atacar(&mapa[indiceAtacante], &mapa[indiceDefensor]);
    }

    // --- EXIBIÇÃO PÓS-ATAQUE ---
    exibirTerritorios(mapa, numTerritorios);

    // --- LIBERAÇÃO DE MEMÓRIA ---
    liberarMemoria(mapa);
    
    return 0;
}


// --- IMPLEMENTAÇÃO DAS FUNÇÕES ---

/**
 * @brief Limpa o buffer de entrada (stdin).
 * Essencial após um scanf para evitar problemas com fgets.
 */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief Preenche os dados dos territórios.
 * @param mapa Ponteiro para o início do vetor de territórios.
 * @param tamanho O número de territórios a cadastrar.
 */
void cadastrarTerritorios(struct Territorio* mapa, int tamanho) {
    printf("\n--- Cadastro de %d Territorios ---\n", tamanho);
    for (int i = 0; i < tamanho; i++) {
        // Usamos (i+1) apenas para exibição amigável
        printf("\n--- Territorio %d ---\n", i + 1); 
        
        printf("Digite o nome: ");
        fgets(mapa[i].nome, 30, stdin); // Acessa o 'nome' no índice 'i'
        
        printf("Digite a cor: ");
        fgets(mapa[i].cor, 10, stdin); // Acessa a 'cor' no índice 'i'

        printf("Digite a qtd. de tropas: ");
        scanf("%d", &mapa[i].tropas); // Acessa 'tropas' no índice 'i'
        limparBuffer(); // Limpa o '\n' deixado pelo scanf

        // Remove o '\n' capturado pelo fgets
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';
    }
}

/**
 * @brief Exibe todos os territórios e seus status.
 * @param mapa Ponteiro para o início do vetor de territórios.
 * @param tamanho O número de territórios a exibir.
 */
void exibirTerritorios(struct Territorio* mapa, int tamanho) {
    printf("\n\n--- ESTADO ATUAL DO MAPA ---\n");
    for (int i = 0; i < tamanho; i++) {
        // Exibe o índice real (0-based) para o usuário saber
        printf("--- [INDICE %d] ---\n", i); 
        printf("Territorio: %s\n", mapa[i].nome);
        printf("Cor do Exercito: %s\n", mapa[i].cor);
        printf("Numero de Tropas: %d\n", mapa[i].tropas);
    }
    printf("---------------------------\n");
}

/**
 * @brief Simula uma rolagem de dado de 6 lados.
 * @return Um número aleatório entre 1 e 6.
 */
int rolarDado() {
    // (rand() % 6) gera de 0 a 5. Somamos 1.
    return (rand() % 6) + 1;
}

/**
 * @brief Executa a lógica de ataque entre dois territórios.
 * @param atacante Ponteiro para o struct do território atacante.
 * @param defensor Ponteiro para o struct do território defensor.
 */
void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    printf("\n--- INICIO DA BATALHA ---\n");
    // Usamos o operador '->' para acessar membros de um ponteiro de struct
    printf("Atacante: %s (%s)\n", atacante->nome, atacante->cor);
    printf("Defensor: %s (%s)\n", defensor->nome, defensor->cor);

    // Requisito: "validar ... não ataque um território da própria cor."
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Ataque invalido! Nao e permitido atacar um territorio da mesma cor.\n");
        return; // Encerra a função de ataque
    }

    // Simulação da rolagem de dados
    int dadoAtacante = rolarDado();
    int dadoDefensor = rolarDado();

    printf("Rolagem -> Atacante [%d] vs Defensor [%d]\n", dadoAtacante, dadoDefensor);

    // Requisito: "se o atacante vencer (dadoA > dadoD) ... "
    if (dadoAtacante > dadoDefensor) {
        printf("\n*** VITORIA DO ATACANTE! ***\n");
        
        // Requisito: "o território defensor deve mudar de dono (cor)"
        // Usar strcpy para copiar a string da cor
        strcpy(defensor->cor, atacante->cor);

        // Requisito: "suas tropas devem ser atualizadas (perde uma tropa)"
        if (defensor->tropas > 0) {
            defensor->tropas--;
        }
        
        printf("%s foi conquistado e agora pertence a cor %s.\n", defensor->nome, defensor->cor);
        printf("%s agora tem %d tropas.\n", defensor->nome, defensor->tropas);
        
    } else {
        printf("\n*** VITORIA DO DEFENSOR! ***\n");
        printf("O territorio %s conseguiu se defender.\n", defensor->nome);
    }
}

/**
 * @brief Libera a memória alocada dinamicamente para o mapa.
 * @param mapa O ponteiro para o início do vetor alocado.
 */
void liberarMemoria(struct Territorio* mapa) {
    printf("\n--- Liberando memoria alocada... ---\n");
    free(mapa); // 'free' é a função que libera o que foi alocado por 'malloc' ou 'calloc'
    mapa = NULL; // Boa prática para evitar 'dangling pointers'
}