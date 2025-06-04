#include <stdio.h>

#define MAX 10

int main() {
    int n, i, j;
    int matriz[MAX][MAX];
    int ehPermutacao = 1;

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


    for (i = 0; i < n && ehPermutacao; i++) {
        int conta1 = 0;
        for (j = 0; j < n; j++) {
            if (matriz[i][j] == 1)
                conta1++;
            else if (matriz[i][j] != 0)
                ehPermutacao = 0; 
        }
        if (conta1 != 1)
            ehPermutacao = 0;
    }


    for (j = 0; j < n && ehPermutacao; j++) {
        int conta1 = 0;
        for (i = 0; i < n; i++) {
            if (matriz[i][j] == 1)
                conta1++;
        }
        if (conta1 != 1)
            ehPermutacao = 0;
    }

    if (ehPermutacao)
        printf("É uma matriz de permutação.\n");
    else
        printf("NÃO é uma matriz de permutação.\n");

    return 0;
}
