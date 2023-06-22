#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void ordenar(int *vetor, int n){
    int i, j, aux;

    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (vetor[j] > vetor[j + 1]){
                aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
            }
}

int retornarPokemons(int n, int *pokemons, int *pokebolas){
    int i, tempo, maiorTempo = 0;

    ordenar(pokemons, n);
    ordenar(pokebolas, n);

    for(i = 0; i < n; i++){
        tempo = pokemons[i] - pokebolas[i];
        if(tempo < 0)
            tempo = -tempo;
        if(tempo > maiorTempo)
            maiorTempo = tempo;
    }

    return maiorTempo;
}

int main() {
    int n, i, tempo;
    int *pokemon, *pokebolas;

    scanf("%d", &n);

    pokemon = (int *)malloc(sizeof(int) * n);
    pokebolas = (int *)malloc(sizeof(int) * n);

    for(i = 0; i < n; i++)
        scanf("%d", &pokemon[i]);
    
    for(i = 0; i < n; i++){
        scanf("%d", &pokebolas[i]);
    }

    tempo = retornarPokemons(n, pokemon, pokebolas);

    printf("%d\n", tempo);

    free(pokemon);
    free(pokebolas);

    return 0;
}