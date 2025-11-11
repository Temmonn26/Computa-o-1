#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define _CTR_SECURE_NO_WARNINGS

// --- Definições de Estruturas e Constantes ---
#define PI 3.14159265358979323846  
#define NUM_CARACTERISTICAS 451 // Número de colunas (características)
#define NUM_CLASSES 2      // Número de classes (0 e 1)

// Estrutura para armazenar os parâmetros estatísticos do GNB  
typedef struct {
    double mu[NUM_CLASSES][NUM_CARACTERISTICAS];
    double sigma_sq[NUM_CLASSES][NUM_CARACTERISTICAS];
    double prior_prob[NUM_CLASSES]; // Probabilidade de cada classe (P(Classe))
} GNB_Modelo;

// --- Funções Estatísticas Fundamentais ---
double calcular_media(double valores[], int n) {
    double soma = 0.0;
    for (int i = 0; i < n; i++) {
        soma += valores[i];
    }
    return soma / n;
}

double calcular_variancia(double valores[], int n, double media) {
    double soma_quadrados = 0.0;
    for (int i = 0; i < n; i++) {
        soma_quadrados += pow(valores[i] - media, 2);
    }
    return soma_quadrados / n;
}

double calcular_gaussiana(double x, double mu, double sigma_sq) {
    if (sigma_sq < 1e-6) {
        sigma_sq = 1e-6;
    }
    double termo_exp = exp(-(pow(x - mu, 2) / (2 * sigma_sq)));
    double termo_frente = 1.0 / sqrt(2.0 * PI * sigma_sq);
    return termo_frente * termo_exp;
}

// --- Funções de Treinamento e Classificação ---
void treinar_gnb(double dados[][NUM_CARACTERISTICAS], int classes[], int num_dados, GNB_Modelo * modelo) {
    int contadores_classe[NUM_CLASSES] = { 0 };
    double soma_caracteristica[NUM_CLASSES][NUM_CARACTERISTICAS] = { {0.0} };

    // Alocação dinâmica para evitar uso excessivo da pilha
    #define MAX_DADOS_CLASSE 1000
    double*** valores_classe_carac = (double***)malloc(NUM_CLASSES * sizeof(double**));
    if (valores_classe_carac == NULL) {
        printf("Erro ao alocar memória para valores_classe_carac!\n");
        exit(1);
    }
    for (int c = 0; c < NUM_CLASSES; c++) {
        valores_classe_carac[c] = (double**)malloc(NUM_CARACTERISTICAS * sizeof(double*));
        if (valores_classe_carac[c] == NULL) {
            printf("Erro ao alocar memória para valores_classe_carac[%d]!\n", c);
            // Libera memória já alocada antes de sair
            for (int cc = 0; cc < c; cc++) {
                free(valores_classe_carac[cc]);
            }
            free(valores_classe_carac);
            exit(1);
        }
        for (int j = 0; j < NUM_CARACTERISTICAS; j++) {
            valores_classe_carac[c][j] = (double*)malloc(MAX_DADOS_CLASSE * sizeof(double));
            if (valores_classe_carac[c][j] == NULL) {
                printf("Erro ao alocar memória para valores_classe_carac[%d][%d]!\n", c, j);
                // Libera memória já alocada antes de sair
                for (int jj = 0; jj < j; jj++) {
                    free(valores_classe_carac[c][jj]);
                }
                for (int cc = 0; cc <= c; cc++) {
                    if (cc < c) {
                        for (int jj = 0; jj < NUM_CARACTERISTICAS; jj++) {
                            free(valores_classe_carac[cc][jj]);
                        }
                    }
                    free(valores_classe_carac[cc]);
                }
                free(valores_classe_carac);
                exit(1);
            }
            for (int k = 0; k < MAX_DADOS_CLASSE; k++) {
                valores_classe_carac[c][j][k] = 0.0;
            }
        }
    }
    int idx_por_classe[NUM_CLASSES] = { 0 };

    for (int i = 0; i < num_dados; i++) {
        int classe = classes[i];
        contadores_classe[classe]++;

        for (int j = 0; j < NUM_CARACTERISTICAS; j++) {
            valores_classe_carac[classe][j][idx_por_classe[classe]] = dados[i][j];
        }
        idx_por_classe[classe]++;
    }

    for (int c = 0; c < NUM_CLASSES; c++) {
        int n_c = contadores_classe[c];
        modelo->prior_prob[c] = (double)n_c / num_dados;

        for (int j = 0; j < NUM_CARACTERISTICAS; j++) {
            modelo->mu[c][j] = calcular_media(valores_classe_carac[c][j], n_c);
            modelo->sigma_sq[c][j] = calcular_variancia(valores_classe_carac[c][j], n_c, modelo->mu[c][j]);
        }
    }

    // Libera memória alocada dinamicamente
    for (int c = 0; c < NUM_CLASSES; c++) {
        for (int j = 0; j < NUM_CARACTERISTICAS; j++) {
            free(valores_classe_carac[c][j]);
        }
        free(valores_classe_carac[c]);
    }
    free(valores_classe_carac);
}

int classificar_gnb(GNB_Modelo * modelo, double novo_dado[]) {
    double log_probabilidade_maxima = -INFINITY;
    int classe_prevista = -1;

    for (int c = 0; c < NUM_CLASSES; c++) {
        double log_prob_classe = log(modelo->prior_prob[c]);

        for (int j = 0; j < NUM_CARACTERISTICAS; j++) {
            double likelihood = calcular_gaussiana(novo_dado[j], modelo->mu[c][j], modelo->sigma_sq[c][j]);
            log_prob_classe += log(likelihood);
        }

        if (log_prob_classe > log_probabilidade_maxima) {
            log_probabilidade_maxima = log_prob_classe;
            classe_prevista = c;
        }
    }

    return classe_prevista;
}

int ler_dados(const char* nome_arquivo, double dados[][NUM_CARACTERISTICAS], int* classes) {
    FILE* arquivo;
    if (fopen_s(&arquivo, "DARWIN.csv", "r") != 0) {
        printf("Erro ao abrir o arquivo!\n");
        return -1;
    }

    int num_dados = 0;
    int items;
    while ((items = fscanf_s(arquivo, "%lf,%lf,%d", &dados[num_dados][0], &dados[num_dados][1], &classes[num_dados])) == 3) {
        num_dados++;
        if (num_dados >= 1000) break;
    }
    fclose(arquivo);
    return num_dados;
}

int main(){
    printf("--- Implementação Gaussian Naive Bayes (GNB) em C ---\n");

    // Alocar no heap em vez da pilha
    double (*dados_treinamento)[NUM_CARACTERISTICAS] = malloc(1000 * sizeof *dados_treinamento);
    if (!dados_treinamento) { perror("malloc"); return 1; }

    int *classes_treinamento = malloc(1000 * sizeof *classes_treinamento);
    if (!classes_treinamento) { free(dados_treinamento); perror("malloc"); return 1; }

    int num_dados = ler_dados("dados.csv", dados_treinamento, classes_treinamento);
    if (num_dados < 0) {
        return 1; // Erro ao ler os dados  
    }

    GNB_Modelo modelo;

    printf("\n[FASE DE TREINAMENTO: Calculando mu e sigma^2 por Classe/Caract.]\n");
    treinar_gnb(dados_treinamento, classes_treinamento, num_dados, &modelo);

    printf("\n[FASE DE CLASSIFICAÇÃO: Testando um Novo Dado]\n");
    double novo_dado[NUM_CARACTERISTICAS] = { 2.5, 3.0 }; // Dado de teste: x1=2.5, x2=3.0

    printf("Novo Dado: (%.2f, %.2f)\n", novo_dado[0], novo_dado[1]);
    int previsao = classificar_gnb(&modelo, novo_dado);

    printf("\n--- RESULTADO FINAL ---\n");
    printf("A classe prevista para (%.2f, %.2f) é: Classe %d\n", novo_dado[0], novo_dado[1], previsao);
    printf("-------------------------\n");

    free(dados_treinamento);
    free(classes_treinamento);

    return 0;
}
