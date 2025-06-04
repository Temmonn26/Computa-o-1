#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

int ehVogal(char c) {
    c = toupper(c);  
    return (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
}

void extrairVogais(char *origem, char *destino) {
    int i, j = 0;
    for (i = 0; origem[i] != '\0'; i++) {
        if (ehVogal(origem[i])) {
            destino[j++] = origem[i];
        }
    }
    destino[j] = '\0';
}

int main() {
    char nome[MAX], bairro[MAX];
    char vogaisNome[MAX], vogaisBairro[MAX];
    char senha[2 * MAX];

    printf("Digite o nome: ");
    fgets(nome, MAX, stdin);
    nome[strcspn(nome, "\n")] = '\0'; 

    printf("Digite o bairro: ");
    fgets(bairro, MAX, stdin);
    bairro[strcspn(bairro, "\n")] = '\0';  

    extrairVogais(nome, vogaisNome);
    extrairVogais(bairro, vogaisBairro);

    strcpy(senha, vogaisNome);
    strcat(senha, vogaisBairro);

    printf("Senha gerada: %s\n", senha);

    return 0;
}
