#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int mochila_fb(int p[], int c[], int n, int b, int i, int custo){
    int c1, c2;
    
    if(i >= n){
        if(b < 0)
            return 0;
        else
            return custo;
    }else {
        c1 = mochila_fb(p, c, n, b, i + 1, custo);
        c2 = mochila_fb(p, c, n, b - p[i], i + 1, custo + c[i]);
        
        return (c1 > c2) ? c1 : c2;
    }
}

int main() {
    int n, i, b;
    int *p, *c;
    
    scanf("%d", &b);
    scanf("%d", &n);
    
    p = malloc(sizeof(int) * n);
    c = malloc(sizeof(int) * n);
    
    for(i = 0; i < n; i++)
        scanf("%d %d", &p[i], &c[i]);
    
    
    printf("%d", mochila_fb(p, c, n, b, 0, 0));
           
    free(p);
    free(c);
    
    return 0;
}
