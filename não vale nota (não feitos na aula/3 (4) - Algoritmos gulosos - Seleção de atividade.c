#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void ordenar(int *ini, int *fim, int n){
    int i, j, auxI, auxF;

    for(i = 1; i < n; i++){
        auxI = ini[i];
        auxF = fim[i];

        for(j = i - 1; (j >= 0) && (auxF < fim[j]); j--){
            ini[j + 1] = ini[j];
            fim[j + 1] = fim[j];
        }
        ini[j + 1] = auxI;
        fim[j + 1] = auxF;
    }
}

void atividades(int *ini, int *fim, int n){
    int i, ultimaAula, n_atividades;
    int *aulas = (int*) malloc(n * sizeof(int));

    aulas[0] = 0;
    ultimaAula = 0;
    n_atividades = 1;

    for(i = 1; i < n; i++)
        if(ini[i] >= fim[ultimaAula]){
            aulas[n_atividades] = i;
            n_atividades++;
            ultimaAula = i;
        }

    printf("Aulas alocadas: ");

    for(i = 0; i < n_atividades; i++)
        printf("%d ", aulas[i]);
}

int main() {
    int i, n;
    int *ini, *fim;

    scanf("%d", &n);

    ini = (int *) malloc(sizeof(int) * n);
    fim = (int *) malloc(sizeof(int) * n);

    for(i = 0; i < n; i++)
        scanf("%d %d", &ini[i], &fim[i]);

    if(n > 0){
        ordenar(ini, fim, n);

        atividades(ini, fim, n);
    }
    
    return 0;
}