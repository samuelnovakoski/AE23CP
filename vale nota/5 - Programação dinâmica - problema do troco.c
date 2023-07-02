#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int troco(int *moedas, int n, int v){
    int i, j, x, y, mat[v + 1][n + 1];

    for(i = 0; i < n; i++)
        mat[0][i] = 1;

    for(i = 1; i <= v; i++){
        for(j = 0; j < n; j++){
            x = y = 0;
            if(i - moedas[j] >= 0)
                x = mat[i - moedas[j]][j];
            if(j >= 1)
                y = mat[i][j - 1];
            mat[i][j] = x + y;
        }
    }

    return mat[v][n - 1];
}

int main() {
    int valor, n, i, *moedas;

    scanf("%d", &valor);
    scanf("%d", &n);

    moedas = (int *)malloc(sizeof(int) * valor);

    for (i = 0; i < valor; i++) {
        scanf("%d", &moedas[i]);
    }

    printf("%d\n", troco(moedas, n, valor));

    return 0;
}