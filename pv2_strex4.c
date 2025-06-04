#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

void abreviarNome(char *nome, char *abreviado) {
    char *palavra;
    char temp[MAX];
    abreviado[0] = '\0'; 

    strcpy(temp, nome); 
    palavra = strtok(temp, " ");

    while (palavra != NULL) {
        if (strlen(palavra) <= 2) {
            strcat(abreviado, palavra);
            strcat(abreviado, " ");
        } else {
            char abreviacao[4];
            abreviacao[0] = toupper(palavra[0]);
            abreviacao[1] = '.';
            abreviacao[2] = '\0';
            strcat(abreviado, abreviacao);
            strcat(abreviado, " ");
        }
        palavra = strtok(NULL, " ");
    }

   
    int len = strlen(abreviado);
    if (len > 0 && abreviado[len - 1] == ' ')
        abreviado[len - 1] = '\0';
}

int main() {
    char nome[MAX], abreviado[MAX];

    printf("Digite o nome completo: ");
    fgets(nome, MAX, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    abreviarNome(nome, abreviado);

    printf("Abreviatura: %s\n", abreviado);

    return 0;
}
