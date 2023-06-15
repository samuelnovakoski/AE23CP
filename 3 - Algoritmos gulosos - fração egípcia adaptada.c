#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void frac(int n, int d){
    int aux; 

    if((n > 0) && (d > 0)){
        if((d % n) == 0)
            printf("1/%d", d / n);
        else if((n % d) == 0)
            printf("%d", n / d);
        else if(n > d){
            printf("%d + ", n / d);
            frac(n % d, d);
        }else {
            aux = d / n + 1;

            printf("1/%d + ", aux);

            frac(n * aux - d, d * aux);
        }
    }
}

int main() {
    int n, d;

    scanf("%d %d", &n, &d);

    frac(n, d);
  
    return 0;
}
