#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define min(a, b) a < b ? a : b

int menor(int *v, int ini, int fim){
    int m, a, b;

    if((fim - ini) <= 1)
        return min(v[ini], v[fim]);
    else{
        m = (ini + fim) / 2;
        a = menor(v, ini, m);
        b = menor(v, m + 1, fim);
    }

    return min(a, b);
}

int main() {
    int i, n;
    int *v;

    scanf("%d", &n);

    v = (int*)malloc(sizeof(int) * n);

    for(i = 0; i < n; i++)
        scanf("%d", &v[i]);
    
    printf("%d", menor(v, 0, n - 1));
   
    return 0;
}