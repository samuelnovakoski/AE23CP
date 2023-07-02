#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int palindromo(char *str, int ini, int fim){
    if(ini >= fim)
        return 1;
    if(str[ini] != str[fim])
        return 0;
    return palindromo(str, ini + 1, fim - 1);
}

int maiorPalindromo(char *str, int tam){
    int i, j, max = 1, ini = 0, fim = 0, tamP;

    for(i = 0; i < tam; i++){
        for(j = i; j < tam; j++){
            if(palindromo(str, i, j)){
                tamP = j - i + 1;
                if(tamP > max){
                    max = tamP;
                    ini = i;
                    fim = j;
                }
            }
        }
    }

    for(i = ini; i < fim + 1; i++)
        printf("%c", str[i]);

    return 1;
}

int main() {
    int tam;
    char *str;

    str = (char *)malloc(sizeof(char));

    scanf("%s", str);

    tam = strlen(str);

    maiorPalindromo(str, tam);
    
    free(str);
    
    return 0;
}