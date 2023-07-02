#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int soma(int *vetor, int ini, int fim){
    int i, meio, esq, dir;

    if(ini == fim)
        return vetor[ini];
    else{
        meio = (ini + fim) / 2;

        for(i = ini; i < fim + 1; i++)
            printf("%d ", vetor[i]);
        printf("\n");
        
        esq = soma(vetor, ini, meio);
        dir = soma(vetor, meio + 1, fim);
        return esq + dir;
    }
}

int main() {
    int n, *vetor, res;

    scanf("%d", &n);
    vetor = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        scanf("%d", &vetor[i]);
    
    res = soma(vetor, 0, n - 1);

    printf("soma: %d\n", res);
   
    return 0;
}