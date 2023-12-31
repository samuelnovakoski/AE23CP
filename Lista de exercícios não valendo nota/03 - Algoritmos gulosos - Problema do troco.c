#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void ordenar(int *moedas, int n){
    int i, j, x;

    for(i = 0; i < n - 1; i++){
        for(j = 0; j < n - i - 1; j++){
            if(moedas[j] < moedas[j + 1]){
                x = moedas[j];
                moedas[j] = moedas[j + 1];
                moedas[j + 1] = x;
            }
        }
    }
}

void qtd_moedas(int *moedas, int n, int troco){
    int i, qtd = 0; 
    int moedasTroco[n];

    for(i = 0; (i < n) && (troco > 0); i++){
        while(troco >= moedas[i]){
            moedasTroco[qtd] = moedas[i];
            troco = troco - moedas[i];
            qtd++;
        }
    }
    
    if(troco == 0)
        for(i = 0; i < qtd; i++)
            printf("%d\n", moedasTroco[i]);
}

int main() {
    int i, troco, n;
    int *moedas;

    scanf("%d %d", &troco, &n);

    moedas = (int*)malloc(sizeof(int) * n);

    for(i = 0; i < n; i++){
        scanf("%d", &moedas[i]);
    }

    ordenar(moedas, n);

    qtd_moedas(moedas, n, troco);
   
    return 0;
}