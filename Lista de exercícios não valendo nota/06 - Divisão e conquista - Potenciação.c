#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int pot(int a, int n){
    int x;
    
    if(n == 0)
        return 1;
    else if(n == 1)
        return a;
    else if(n % 2 == 0){
        x = pot(a, n / 2);
        return x * x;
    }else{
        x = pot(a, (n - 1) / 2);
        return a * x * x;
    }
}

int main() {
    int a, b;
    
    scanf("%d %d", &a, &b);
    
    printf("%d", pot(a, b));
  
    return 0;
}
