#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
    int inicio, fim;
}Aulas;

void ordenar(Aulas *aulas, int n){
    int i, j;
    Aulas aux;

    for(i = 1; i < n; i++){
        aux = aulas[i];

        for(j = i - 1; (j >= 0) && (aux.fim < aulas[j].fim); j--){
            aulas[j + 1] = aulas[j]; 
        }
        aulas[j + 1] = aux;
    }
}

void atividades(Aulas *aulas, int n){
    int i, ultima = 0, m = 1;
    int *v = (int *)malloc(sizeof(int) * n);

    v[0] = 0;

    for(i = 1; i < n; i++){
        if(aulas[i].inicio >= aulas[ultima].fim){
            v[m] = i;
            m++;
            ultima = i;
        }
    }

    printf("Aulas alocadas: ");

    for(i = 0; i < m; i++)
        printf("%d ", v[i]);
}

int main() {
    int i, n;
    Aulas *aulas;

    scanf("%d", &n);

    aulas = (Aulas *) malloc(sizeof(Aulas) * n);

    for(i = 0; i < n; i++)
        scanf("%d %d", &aulas[i].inicio, &aulas[i].fim);

    ordenar(aulas, n);

    atividades(aulas, n);

    return 0;
}