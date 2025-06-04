#include <stdio.h>
#include <math.h>

int terminaCom(int a, int b) {
    int digitos = 0;
    int temp = b;


    while (temp > 0) {
        digitos++;
        temp /= 10;
    }

    int divisor = pow(10, digitos);
    if ((a % divisor) == b)
        return 1;
    else
        return 0;
}

int main() {
    int a, b;

    printf("Digite o valor de a: ");
    scanf("%d", &a);

    printf("Digite o valor de b: ");
    scanf("%d", &b);

    if (terminaCom(a, b))
        printf("1 (sim)\n");
    else
        printf("0 (nao)\n");

    return 0;
}
