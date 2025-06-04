#include <stdio.h>

#define MAX 10

int main() {
    int n, i, j;
    int matriz[MAX][MAX];
    int somaDiag1 = 0, somaDiag2 = 0;
    int somaReferencia;
    int somaLinha, somaColuna;
    int ehMagico = 1;

    printf("Digite a ordem da matriz quadrada (ex: 3 para 3x3): ");
    scanf("%d", &n);

    if (n > MAX) {
        printf("Tamanho máximo excedido.\n");
        return 1;
    }

    printf("Digite os elementos da matriz (%dx%d):\n", n, n);
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &matriz[i][j]);


    for (i = 0; i < n; i++)
        somaDiag1 += matriz[i][i];


    for (i = 0; i < n; i++)
        somaDiag2 += matriz[i][n - 1 - i];


    somaReferencia = 0;
    for (j = 0; j < n; j++)
        somaReferencia += matriz[0][j];

    for (i = 0; i < n; i++) {
        somaLinha = 0;
        somaColuna = 0;
        for (j = 0; j < n; j++) {
            somaLinha += matriz[i][j];
            somaColuna += matriz[j][i];
        }
        if (somaLinha != somaReferencia || somaColuna != somaReferencia) {
            ehMagico = 0;
            break;
        }
    }

  
    if (somaDiag1 != somaReferencia || somaDiag2 != somaReferencia)
        ehMagico = 0;

    if (ehMagico)
        printf("É um quadrado mágico.\n");
    else
        printf("NÃO é um quadrado mágico.\n");

    return 0;
}
