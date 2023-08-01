#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int labirintoBacktracking(int **lab, int m, int n, int *movX, int *movY, int li, int ci, int lf, int cf){
    int l, c, i, passos;

    if ((li == lf) && (ci == cf)) return lab[li][ci];

    for (i = 0; i < 4; i++){
        l = li + movX[i];
        c = ci + movY[i];

        if ((l >= 0) && (l < m) && (c >= 0) && (c < n) && (lab[l][c] == -1)){
            lab[l][c] = lab[li][ci] + 1; 

            passos = labirintoBacktracking(lab, m, n, movX, movY, l, c, lf, cf);
        
            if (passos > 0) return passos;
            else lab[l][c] = -1;
        }
    }
    return -1;
}

int main(){
    int i, j, n, m, li, ci, lf, cf, resp;
	int **lab;

    scanf("%d %d ", &n, &m);

	lab = (int**)malloc(sizeof(int*) * n);
	for(i = 0; i < n; i++)
		lab[i] = (int*)malloc(sizeof(int) * m);
	
    scanf("%d %d", &li, &ci);
    scanf("%d %d", &lf, &cf);

    int movX[] = {0, 1, 0, -1}; 
    int movY[] = {1, 0, -1, 0};

    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            scanf("%d", &lab[i][j]);
    
    lab[li][ci] = 0;
    
    resp = labirintoBacktracking(lab, n, m, movX, movY, li, ci, lf, cf);
    
    printf("%d\n", resp);

    return 0;
}