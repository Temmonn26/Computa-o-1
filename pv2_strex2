#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

void intercalarFrases(char *frase1, char *frase2, char *frase3) {
    char *palavra1, *palavra2;
    char temp1[MAX], temp2[MAX];
    
    
    strcpy(temp1, frase1);
    strcpy(temp2, frase2);
    
    palavra1 = strtok(temp1, " ");
    palavra2 = strtok(temp2, " ");
    
    frase3[0] = '\0';  
    
  
    while (palavra1 != NULL || palavra2 != NULL) {
        if (palavra1 != NULL) {
            strcat(frase3, palavra1);
            strcat(frase3, " ");
            palavra1 = strtok(NULL, " ");
        }
        if (palavra2 != NULL) {
            strcat(frase3, palavra2);
            strcat(frase3, " ");
            palavra2 = strtok(NULL, " ");
        }
    }
    
   
    int len = strlen(frase3);
    if (len > 0 && frase3[len - 1] == ' ')
        frase3[len - 1] = '\0';
}

int main() {
    char frase1[MAX], frase2[MAX], frase3[2 * MAX];

    printf("Digite a Frase 1: ");
    fgets(frase1, MAX, stdin);
    frase1[strcspn(frase1, "\n")] = '\0';
    printf("Digite a Frase 2: ");
    fgets(frase2, MAX, stdin);
    frase2[strcspn(frase2, "\n")] = '\0'; 

    intercalarFrases(frase1, frase2, frase3);

    printf("Frase 3: %s\n", frase3);

    return 0;
}
