#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int fibonacci(int n){
    int i, f[n + 1];
    
    f[0] = 0;
    f[1] = 1;
    
    for (i = 2; i <= n; i++)
        f[i] = f[i - 1] + f[i - 2];
        
    return f[n];
}

int main() {
    int n;

    scanf("%d", &n);

    printf("%d", fibonacci(n));
   
    return 0;
}