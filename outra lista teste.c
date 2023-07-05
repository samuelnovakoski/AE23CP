#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

/*
int funcoes(){
    int n = 0, a = 0, b = 0;

    while(a >= b){
        a = 2 * pow(n, 2) + n + 1;
        b = (5 * pow(n, 2)) / 2;
        
        printf("a = %d: %d\n", n, a);
        printf("b = %d: %d\n", n, b);
        
        if(a < b)
            return n;
        else
            n++;
    }
    return 0;
}

void sort(int v[], int n){
    int k, j, aux;
    for(k = 1; k < n; k++)
        for(j = 0; j < n; j++)
        if(v[j] > v[j + 1]){
            aux = v[j];
            v[j] = v[j + 1];
            v[j + 1] = aux;
        }
}
*/

int bits(int n){
    int i;

    for(i = 0; i < n; i++)
}

int main() {
    int i, n;

    n = funcoes();

    printf("%d\n", n);

    
   
    return 0;
}




void resolver_labirintoBnB(int lab[MAX][MAX], int m, int n, int movX[], int movY[], int li, int ci, int lf, int cf, int *min){
	int l, c, i;

	if ((li == lf) && (ci == cf)){
		if (lab[lf][cf] < *min)
			*min = lab[lf][cf];
	}else{
		/*Todos os movimentos a partir da posição inicial são testados*/
		for (i = 0; i < 4; i++){
			l = li + movX[i];
			c = ci + movY[i];

			/*O movimento é verificado e caso seja válido, uma solução é gerada*/
			if ((l >= 0) && (l < m) && (c >= 0) && (c < n) && ((lab[l][c] == -1) || (lab[l][c] > lab[li][ci] + 1))){
				lab[l][c] = lab[li][ci] + 1;

				// Aqui são definidos os limitantes
				if (lab[l][c] + abs(l - lf) + abs(c - cf) < *min)
					resolver_labirintoBnB(lab, m, n, movX, movY, l, c, lf, cf, min);
			}
		}
	}
}




#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
   
    return 0;
}