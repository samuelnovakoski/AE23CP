#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define max(a, b) a > b ? a : b

int maior(int *v, int ini, int fim){
    int m, a, b;

    if ((fim - ini) <= 1)
        return max(v[ini], v[fim]);
    else{
        m = (ini + fim) / 2;
        a = maior(v, ini, m);
        b = maior(v, m + 1, fim);
    }

    return max(a, b);
}

int main() {
    int i, n;
    int *v;

    scanf("%d", &n);

    v = (int*) malloc(sizeof(int) * n);

    for(i = 0; i < n; i++)
        scanf("%d", &v[i]);
    
    printf("%d", maior(v, 0, n - 1));
   
    return 0;
}