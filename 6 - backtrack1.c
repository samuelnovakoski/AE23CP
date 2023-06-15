#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int palindromo(char *str, int ini, int fim){
    int i;
    for(i = ini; i < fim; i++){
        if(str[i] != str[fim]){
            return 0;
        }
        fim--;
    }
    return 1;
}

int maiorPalindromo(char *str, int tam, int ini, int fim){
    int str1, str2;
    if(ini == fim || palindromo(str, ini, fim)){
        return fim - ini + 1;
    } else {
        str1 = maiorPalindromo(str, tam, ini + 1, fim);
        str2 = maiorPalindromo(str, tam, ini, fim - 1);

        return str1 > str2 ? str1 : str2;
    } 
}

int main(){
    char *str;
    int i, j, tam, max;
    
    str = (char*)malloc(sizeof(char));
    
    scanf("%s", str);

    tam = strlen(str);
    max = maiorPalindromo(str, tam, 0, tam - 1);

    for(i = 0; i < tam; i++){
        if(palindromo(str, i, i + max - 1)){
            for(j = i; j < i + max; j++){
                printf("%c", str[j]);
            }
            printf("\n");
            break;
        }
    }

    free(str);
    
    return 0;
}