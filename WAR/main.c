#include <stdio.h>
#include <stdlib.h> // Para malloc, free, rand, srand, atoi
#include <string.h> // Para strcpy, strcspn, strcmp
#include <time.h>   // Para srand(time(NULL))

/*
 * 1. Estrutura dos Territórios:
 * Define a struct Territorio conforme solicitado.
 */
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

// --- PROTÓTIPOS DAS FUNÇÕES (Modularização) ---

// Funções do Módulo de Jogo
void limparBuffer();
int rolarDado();

// Funções de Gerenciamento de Território
void cadastrarTerritorios(struct Territorio* mapa, int tamanho);
void exibirTerritorios(struct Territorio* mapa, int tamanho);
void atacar(struct Territorio* atacante, struct Territorio* defensor);

// Funções do Novo Módulo de Missões
void atribuirMissao(char* destino, const char* missoes[], int totalMissoes);
int verificarMissao(char* missao, const char* corDoJogador, struct Territorio* mapa, int tamanho);

// Função de Gerenciamento de Memória
void liberarMemoria(struct Territorio* mapa, char* missaoP1, char* missaoP2);


// --- CONSTANTES GLOBAIS ---
const char* COR_JOGADOR_1 = "Vermelho";
const char* COR_JOGADOR_2 = "Azul";

/*
 * 2. Criação do vetor de missões:
 * Define a lista de missões estratégicas disponíveis.
 */
const char* LISTA_DE_MISSOES[] = {
    "Possuir 3 territorios",
    "Eliminar a cor Azul",
    "Eliminar a cor Vermelho"
};
const int TOTAL_MISSOES = 3;


// --- FUNÇÃO PRINCIPAL ---
int main() {
    // Requisito: Inicializar o gerador de números aleatórios
    srand(time(NULL));

    int numTerritorios;
    int indiceAtacante, indiceDefensor;
    char buffer[20];
    
    // Ponteiros para a memória dinâmica
    struct Territorio* mapa = NULL;
    char* missaoP1 = NULL;
    char* missaoP2 = NULL;

    // --- SETUP DO JOGO ---
    printf("Quantos territorios existem no mapa (min. 2)? ");
    fgets(buffer, 20, stdin);
    numTerritorios = atoi(buffer);

    if (numTerritorios <= 1) {
        printf("E preciso de pelo menos 2 territorios para jogar.\n");
        return 1;
    }

    /*
     * 3. Alocação Dinâmica de Memória (Territórios e Missões):
     */
    mapa = (struct Territorio*)calloc(numTerritorios, sizeof(struct Territorio));
    missaoP1 = (char*)malloc(100 * sizeof(char)); // 100 chars para a string da missão
    missaoP2 = (char*)malloc(100 * sizeof(char));

    if (mapa == NULL || missaoP1 == NULL || missaoP2 == NULL) {
        printf("Erro fatal! Falha ao alocar memoria.\a\n");
        liberarMemoria(mapa, missaoP1, missaoP2); // Libera o que foi alocado
        return 1;
    }
    printf("Memoria alocada com sucesso.\n");


    /*
     * 4. Sorteio e Armazenamento da Missão:
     * Atribui uma missão aleatória para cada jogador.
     */
    atribuirMissao(missaoP1, LISTA_DE_MISSOES, TOTAL_MISSOES);
    atribuirMissao(missaoP2, LISTA_DE_MISSOES, TOTAL_MISSOES);


    // --- CADASTRO ---
    printf("\n--- GUIA DE CADASTRO ---\n");
    printf("Para o jogo funcionar, use as cores '%s' e '%s' ao cadastrar.\n", COR_JOGADOR_1, COR_JOGADOR_2);
    cadastrarTerritorios(mapa, numTerritorios);


    /*
     * 5. Exibição Condicional (Interface Amigável):
     * Mostra a missão secreta de cada jogador apenas uma vez.
     */
    printf("\n\n--- MISSOES SECRETAS ---");
    printf("\nJogador 1 (%s), sua missao e: %s", COR_JOGADOR_1, missaoP1);
    printf("\nJogador 2 (%s), sua missao e: %s", COR_JOGADOR_2, missaoP2);
    printf("\n--------------------------\n");
    
    exibirTerritorios(mapa, numTerritorios);

    // --- FASE DE ATAQUE (Simulação de 1 turno) ---
    printf("\n--- FASE DE ATAQUE ---\n");
    printf("Digite o INDICE do territorio ATACANTE (0 a %d): ", numTerritorios - 1);
    fgets(buffer, 20, stdin);
    indiceAtacante = atoi(buffer);

    printf("Digite o INDICE do territorio DEFENSOR (0 a %d): ", numTerritorios - 1);
    fgets(buffer, 20, stdin);
    indiceDefensor = atoi(buffer);

    // Validação de Escolhas (Requisitos Técnicos)
    if (indiceAtacante < 0 || indiceAtacante >= numTerritorios ||
        indiceDefensor < 0 || indiceDefensor >= numTerritorios) {
        printf("Ataque invalido! Indices fora do limite do mapa.\n");
    } else if (indiceAtacante == indiceDefensor) {
        printf("Ataque invalido! Um territorio nao pode atacar a si mesmo.\n");
    } else {
        atacar(&mapa[indiceAtacante], &mapa[indiceDefensor]);
    }

    // --- EXIBIÇÃO PÓS-ATAQUE ---
    exibirTerritorios(mapa, numTerritorios);

    /*
     * 6. Verificação de Missão (Fim do Turno):
     * Verifica se algum jogador completou sua missão.
     */
    printf("\n--- VERIFICACAO DE VITORIA ---\n");
    int vitoriaP1 = verificarMissao(missaoP1, COR_JOGADOR_1, mapa, numTerritorios);
    int vitoriaP2 = verificarMissao(missaoP2, COR_JOGADOR_2, mapa, numTerritorios);

    if (vitoriaP1) {
        printf("Parabens! Jogador 1 (%s) completou a missao!\n", COR_JOGADOR_1);
    }
    if (vitoriaP2) {
        printf("Parabens! Jogador 2 (%s) completou a missao!\n", COR_JOGADOR_2);
    }
    if (!vitoriaP1 && !vitoriaP2) {
        printf("Nenhum jogador venceu neste turno.\n");
    }

    // --- 7. LIBERAÇÃO DE MEMÓRIA ---
    liberarMemoria(mapa, missaoP1, missaoP2);
    
    return 0;
}


// --- IMPLEMENTAÇÃO DAS FUNÇÕES ---

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int rolarDado() {
    return (rand() % 6) + 1;
}

void cadastrarTerritorios(struct Territorio* mapa, int tamanho) {
    printf("\n--- Cadastro de %d Territorios ---\n", tamanho);
    for (int i = 0; i < tamanho; i++) {
        printf("\n--- Territorio [INDICE %d] ---\n", i);
        
        printf("Digite o nome: ");
        fgets(mapa[i].nome, 30, stdin);
        
        printf("Digite a cor: ");
        fgets(mapa[i].cor, 10, stdin);

        printf("Digite a qtd. de tropas: ");
        scanf("%d", &mapa[i].tropas);
        limparBuffer(); // Essencial após o scanf

        // Remove o '\n' capturado pelo fgets
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';
    }
}

void exibirTerritorios(struct Territorio* mapa, int tamanho) {
    printf("\n\n--- ESTADO ATUAL DO MAPA ---\n");
    for (int i = 0; i < tamanho; i++) {
        printf("--- [INDICE %d] ---\n", i); 
        printf("Territorio: %s\n", mapa[i].nome);
        printf("Cor do Exercito: %s\n", mapa[i].cor);
        printf("Numero de Tropas: %d\n", mapa[i].tropas);
    }
    printf("---------------------------\n");
}

void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    printf("\n--- INICIO DA BATALHA ---\n");
    printf("Atacante: %s (%s)\n", atacante->nome, atacante->cor);
    printf("Defensor: %s (%s)\n", defensor->nome, defensor->cor);

    // Requisito: "validar ... não ataque um território da própria cor."
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Ataque invalido! Nao e permitido atacar um territorio da mesma cor.\n");
        return;
    }

    int dadoAtacante = rolarDado();
    int dadoDefensor = rolarDado();

    printf("Rolagem -> Atacante [%d] vs Defensor [%d]\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("\n*** VITORIA DO ATACANTE! ***\n");
        
        // Atualização dos campos (Passagem por Referência)
        strcpy(defensor->cor, atacante->cor);
        if (defensor->tropas > 0) {
            defensor->tropas--;
        }
        
        printf("%s foi conquistado e agora pertence a cor %s.\n", defensor->nome, defensor->cor);
        
    } else {
        printf("\n*** VITORIA DO DEFENSOR! ***\n");
        printf("O territorio %s conseguiu se defender.\n", defensor->nome);
    }
}

/**
 * @brief Sorteia uma missão e a copia para o destino.
 * @param destino Ponteiro para a string de destino (já alocada).
 * @param missoes O vetor (array) de missões disponíveis.
 * @param totalMissoes O tamanho do vetor 'missoes'.
 */
void atribuirMissao(char* destino, const char* missoes[], int totalMissoes) {
    // Sorteia um índice aleatório (0 até totalMissoes-1)
    int indiceSorteado = rand() % totalMissoes;
    
    // Copia a string da missão sorteada para o 'destino'
    strcpy(destino, missoes[indiceSorteado]);
}

/**
 * @brief Verifica se a condição de vitória de uma missão foi atingida.
 * @param missao A string da missão do jogador.
 * @param corDoJogador A cor do jogador ("Vermelho" ou "Azul").
 * @param mapa O ponteiro para o vetor de territórios.
 * @param tamanho O número total de territórios no mapa.
 * @return 1 (verdadeiro) se a missão foi cumprida, 0 (falso) caso contrário.
 */
int verificarMissao(char* missao, const char* corDoJogador, struct Territorio* mapa, int tamanho) {
    
    // Lógica para a Missão 1
    if (strcmp(missao, "Possuir 3 territorios") == 0) {
        int contagem = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corDoJogador) == 0) {
                contagem++;
            }
        }
        return (contagem >= 3); // Retorna 1 (true) se tiver 3 ou mais
    }
    
    // Lógica para a Missão 2
    if (strcmp(missao, "Eliminar a cor Azul") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Azul") == 0) {
                return 0; // Se encontrar 1, a missão falhou
            }
        }
        return 1; // Se o loop terminar sem achar 'Azul', venceu
    }
    
    // Lógica para a Missão 3
    if (strcmp(missao, "Eliminar a cor Vermelho") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Vermelho") == 0) {
                return 0; // Se encontrar 1, a missão falhou
            }
        }
        return 1; // Se o loop terminar sem achar 'Vermelho', venceu
    }

    // Se a missão não for reconhecida, não foi cumprida
    return 0;
}


/**
 * @brief Libera toda a memória alocada dinamicamente (mapa e missões).
 */
void liberarMemoria(struct Territorio* mapa, char* missaoP1, char* missaoP2) {
    printf("\n--- Liberando memoria alocada... ---\n");
    
    // A função 'free' pode lidar com ponteiros NULL com segurança.
    free(mapa);
    free(missaoP1);
    free(missaoP2);
    
    printf("Memoria liberada. Fim do programa.\n");
}