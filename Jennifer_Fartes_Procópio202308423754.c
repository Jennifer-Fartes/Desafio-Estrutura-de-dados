/*
 * Trabalho: Sistema de Priorização e Montagem da Torre de Resgate
 * ------------------------------------------------------------------

/* Cabeçalho com identificação do aluno*/
/*
  Nome: Jennifer Fartes Procópio
  Matrícula: 202308423754
*/

#include <stdio.h>    // Funções de Input/Output
#include <stdlib.h>   // Funções utilitárias (atoi)
#include <string.h>   // Operações com strings
#include <time.h>     // Medição de tempo (clock)

/* Definições de constantes */
#define MAX_COMPONENTES 20
#define MAX_NOME 30
#define MAX_TIPO 20

// Tipo para contagem de comparações: unsigned long (mais robusto que long long em alguns compiladores)
typedef unsigned long Contador;

/* ---------- 1. Struct Componente ---------- */
typedef struct {
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int prioridade;
} Componente;

/* ---------- Protótipos das Funções Obrigatórias ---------- */
// Os algoritmos de ordenação agora recebem um ponteiro para Contador (unsigned long)
void selectionSortPrioridade(Componente vetor[], int n, Contador *comparacoes);
void insertionSortTipo(Componente vetor[], int n, Contador *comparacoes);
void bubbleSortNome(Componente vetor[], int n, Contador *comparacoes);
int buscaBinariaPorNome(Componente vetor[], int n, const char chave[], Contador *comparacoes);
void mostrarComponentes(Componente vetor[], int n);
void medirTempo(void (*algoritmo)(Componente[], int, Contador*),
                Componente vetor[], int n,
                Contador *comparacoes, double *segundos);

/* ---------- Funções Utilitárias ---------- */

// Remove o '\n' do final da string (necessário após fgets)
void removerNovaLinha(char *s) {
    size_t len = strlen(s);
    if (len > 0 && s[len - 1] == '\n') {
        s[len - 1] = '\0';
    }
}

// Troca (swap) entre dois structs Componente
void trocaComponentes(Componente *a, Componente *b) {
    Componente tmp = *a;
    *a = *b;
    *b = tmp;
}

// Copia o vetor para garantir que a ordenação não afete os dados principais
void copiarVetor(Componente origem[], Componente destino[], int n) {
    for (int i = 0; i < n; i++) {
        destino[i] = origem[i];
    }
}

/* ---------- 3. Implementação dos Algoritmos de Ordenação  ---------- */

// Selection Sort: Ordena por Prioridade (int)
void selectionSortPrioridade(Componente vetor[], int n, Contador *comparacoes) {
    *comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        int idxMin = i;
        for (int j = i + 1; j < n; j++) {
            (*comparacoes)++; // Contagem de comparações de prioridade
            if (vetor[j].prioridade < vetor[idxMin].prioridade) {
                idxMin = j;
            }
        }
        if (idxMin != i) {
            trocaComponentes(&vetor[i], &vetor[idxMin]);
        }
    }
}

// Insertion Sort: Ordena por Tipo (string)
void insertionSortTipo(Componente vetor[], int n, Contador *comparacoes) {
    *comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente chave = vetor[i];
        int j = i - 1;

        while (j >= 0) {
            (*comparacoes)++; // Contagem de comparações de string (strcmp)
            if (strcmp(vetor[j].tipo, chave.tipo) > 0) {
                vetor[j + 1] = vetor[j];
                j--;
            } else {
                break;
            }
        }
        vetor[j + 1] = chave;
    }
}

// Bubble Sort: Ordena por Nome (string)
void bubbleSortNome(Componente vetor[], int n, Contador *comparacoes) {
    *comparacoes = 0;
    int trocou;

    for (int pass = 0; pass < n - 1; pass++) {
        trocou = 0;
        for (int i = 0; i < n - 1 - pass; i++) {
            (*comparacoes)++; // Contagem de comparações de string (strcmp)
            if (strcmp(vetor[i].nome, vetor[i + 1].nome) > 0) {
                trocaComponentes(&vetor[i], &vetor[i + 1]);
                trocou = 1;
            }
        }
        if (!trocou) {
            break; // Otimização
        }
    }
}

/* ---------- 5. Medição de Desempenho  ---------- */
// Recebe o ponteiro da função e mede o tempo e comparações
void medirTempo(void (*algoritmo)(Componente[], int, Contador*),
                Componente vetor[], int n,
                Contador *comparacoes, double *segundos) {
    clock_t t_inicio = clock();
    algoritmo(vetor, n, comparacoes);
    clock_t t_fim = clock();
    // Cálculo do tempo em segundos
    *segundos = ((double)(t_fim - t_inicio)) / (double) CLOCKS_PER_SEC;
}

/* ---------- 4. Busca Binária por Nome  ---------- */
int buscaBinariaPorNome(Componente vetor[], int n, const char chave[], Contador *comparacoes) {
    int inicio = 0;
    int fim = n - 1;
    *comparacoes = 0;

    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        (*comparacoes)++; // Contagem de comparações
        int cmp = strcmp(vetor[meio].nome, chave);

        if (cmp == 0) {
            return meio; // Encontrado
        } else if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    return -1; // Não encontrado
}

/* ---------- 6. Exibir Componentes Formatados  ---------- */
// Garante o alinhamento correto da tabela
void mostrarComponentes(Componente vetor[], int n) {
    printf("\n");
    printf("----- Componentes Atuais (Total = %d) -----\n", n);
    // Cabeçalho da tabela com espaçamentos fixos
    printf("%-4s | %-30s | %-20s | %4s\n", "Idx", "NOME", "TIPO", "PRIOR");
    printf("-----+--------------------------------+----------------------+------\n");

    for (int i = 0; i < n; i++) {
        // Formatação de saída 
        printf("%-4d | %-30s | %-20s | %4d\n",
               i, vetor[i].nome, vetor[i].tipo, vetor[i].prioridade);
    }
    printf("----------------------------------------------\n");
}

/* ---------- Função Principal com Menu Interativo ---------- */
int main() {
    Componente componentes[MAX_COMPONENTES];
    int total = 0;
    char linha[256];
    int ordenadoPorNome = 0; // Flag para garantir a Busca Binária

    printf("=== Torre de Resgate - Sistema de Priorizacao ===\n");

    /* ----- 2. Entrada de Dados  ----- */
    do {
        printf("Quantos componentes deseja cadastrar? (1-%d): ", MAX_COMPONENTES);
        if (!fgets(linha, sizeof(linha), stdin)) return 1;
        total = atoi(linha);
    } while (total < 1 || total > MAX_COMPONENTES);

    for (int i = 0; i < total; i++) {
        printf("\n--- Componente %d de %d ---\n", i + 1, total);

        // Leitura do Nome e Tipo com fgets
        printf("Nome (ex: chip central): ");
        if (!fgets(componentes[i].nome, sizeof(componentes[i].nome), stdin)) componentes[i].nome[0] = '\0';
        removerNovaLinha(componentes[i].nome);

        printf("Tipo (ex: controle, suporte): ");
        if (!fgets(componentes[i].tipo, sizeof(componentes[i].tipo), stdin)) componentes[i].tipo[0] = '\0';
        removerNovaLinha(componentes[i].tipo);

        // Leitura e validação da Prioridade (1-10)
        int prio = 0;
        do {
            printf("Prioridade (1-10): ");
            if (!fgets(linha, sizeof(linha), stdin)) break;
            prio = atoi(linha);
            if (prio < 1 || prio > 10) {
                printf("Valor invalido. Informe um numero entre 1 e 10.\n");
            }
        } while (prio < 1 || prio > 10);
        componentes[i].prioridade = prio;
    }

    /* ----- Menu Principal ----- */
    while (1) {
        printf("\n=== Menu Estrategico ===\n");
        printf("1 - Ordenar por NOME (Bubble Sort)\n");
        printf("2 - Ordenar por TIPO (Insertion Sort)\n");
        printf("3 - Ordenar por PRIORIDADE (Selection Sort)\n");
        printf("4 - Busca binaria por NOME\n");
        printf("5 - Mostrar componentes atuais\n");
        printf("6 - Sair\n");
        printf("Escolha uma opcao: ");

        if (!fgets(linha, sizeof(linha), stdin)) break;
        int opcao = atoi(linha);

        // Buffer e variáveis de medição
        Componente copia[MAX_COMPONENTES];
        Contador comparacoes = 0; // unsigned long 
        double tempo = 0.0;       // double 

        if (opcao >= 1 && opcao <= 3) {
            copiarVetor(componentes, copia, total);
        }

        switch (opcao) {
            case 1:
                // Bubble Sort (Nome)
                medirTempo(bubbleSortNome, copia, total, &comparacoes, &tempo);
                printf("\n--- Bubble Sort por NOME ---\n");
                mostrarComponentes(copia, total);
                // Saída de desempenho 
                printf("Comparacoes: %lu | Tempo: %.6f s\n", comparacoes, tempo);

                printf("Aplicar a ordenacao? (s/n): ");
                if (!fgets(linha, sizeof(linha), stdin)) break;
                removerNovaLinha(linha);
                if (linha[0] == 's' || linha[0] == 'S') {
                    copiarVetor(copia, componentes, total);
                    ordenadoPorNome = 1;
                    printf("Ordenacao por nome aplicada.\n");
                }
                break;

            case 2:
                // Insertion Sort (Tipo)
                medirTempo(insertionSortTipo, copia, total, &comparacoes, &tempo);
                printf("\n--- Insertion Sort por TIPO ---\n");
                mostrarComponentes(copia, total);
                printf("Comparacoes: %lu | Tempo: %.6f s\n", comparacoes, tempo);

                printf("Aplicar a ordenacao? (s/n): ");
                if (!fgets(linha, sizeof(linha), stdin)) break;
                removerNovaLinha(linha);
                if (linha[0] == 's' || linha[0] == 'S') {
                    copiarVetor(copia, componentes, total);
                    ordenadoPorNome = 0; // Perde a ordem por nome
                    printf("Ordenacao por tipo aplicada.\n");
                }
                break;

            case 3:
                // Selection Sort (Prioridade)
                medirTempo(selectionSortPrioridade, copia, total, &comparacoes, &tempo);
                printf("\n--- Selection Sort por PRIORIDADE ---\n");
                mostrarComponentes(copia, total);
                printf("Comparacoes: %lu | Tempo: %.6f s\n", comparacoes, tempo);

                printf("Aplicar a ordenacao? (s/n): ");
                if (!fgets(linha, sizeof(linha), stdin)) break;
                removerNovaLinha(linha);
                if (linha[0] == 's' || linha[0] == 'S') {
                    copiarVetor(copia, componentes, total);
                    ordenadoPorNome = 0; // Perde a ordem por nome
                    printf("Ordenacao por prioridade aplicada.\n");
                }
                break;

            case 4:
                // Busca Binária 
                if (!ordenadoPorNome) {
                    printf("\nATENÇÃO: A busca binária exige que o vetor esteja ordenado por NOME. Use a Opção 1.\n");
                } else {
                    char chave[MAX_NOME];
                    printf("Digite o NOME exato do componente-chave: ");
                    if (!fgets(chave, sizeof(chave), stdin)) break;
                    removerNovaLinha(chave);

                    int idx = buscaBinariaPorNome(componentes, total, chave, &comparacoes);

                    if (idx >= 0) {
                        printf("\n>>> Componente-chave presente: SIM (Pronto para montar a torre!)\n");
                    } else {
                        printf("\n>>> Componente-chave presente: NAO\n");
                    }
                    printf("Comparações na busca: %lu\n", comparacoes);
                }
                break;

            case 5:
                mostrarComponentes(componentes, total);
                break;

            case 6:
                printf("Encerrando o sistema. Boa sorte na missão!\n");
                return 0;

            default:
                printf("Opcao invalida. Digite um numero de 1 a 6.\n");
        }
    }

    return 0;
}
