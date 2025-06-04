#include <stdio.h>
#include <string.h>
#include <ctype.h>

void contarVogais(const char *frase) {
    int contagem_a = 0;
    int contagem_e = 0;
    int contagem_i = 0;
    int contagem_o = 0;
    int contagem_u = 0;

    for (int i = 0; frase[i] != '\0'; i++) {
        char caractere = tolower(frase[i]);

        switch (caractere) {
            case 'a':
                contagem_a++;
                break;
            case 'e':
                contagem_e++;
                break;
            case 'i':
                contagem_i++;
                break;
            case 'o':
                contagem_o++;
                break;
            case 'u':
                contagem_u++;
                break;
        }
    }

    printf("\n--- Resultado para a frase: \"%s\" ---\n\n", frase);

    printf("a : ");
    for (int i = 0; i < contagem_a; i++) {
        printf("*");
    }
    printf(" (%d)\n", contagem_a);

    printf("e : ");
    for (int i = 0; i < contagem_e; i++) {
        printf("*");
    }
    printf(" (%d)\n", contagem_e);

    printf("i : ");
    for (int i = 0; i < contagem_i; i++) {
        printf("*");
    }
    printf(" (%d)\n", contagem_i);

    printf("o : ");
    for (int i = 0; i < contagem_o; i++) {
        printf("*");
    }
    printf(" (%d)\n", contagem_o);

    printf("u : ");
    for (int i = 0; i < contagem_u; i++) {
        printf("*");
    }
    printf(" (%d)\n", contagem_u);
    printf("\n-------------------------------------\n");
}

int main() {
    char frase[256];
    printf("Digite uma frase (max 255 caracteres e sem acentos): \n");
    fgets(frase, sizeof(frase), stdin);
    frase[strcspn(frase, "\n")] = '\0';
    contarVogais(frase);
    return 0;
}
