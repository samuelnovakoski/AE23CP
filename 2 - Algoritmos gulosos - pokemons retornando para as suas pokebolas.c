#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int pokebolaProxima(int n, int pokemon, int *pokebolas){
    int i, tempo, menorTempo, pokebolaproxima;

    pokebolaproxima = pokebolas[0];
    menorTempo = pokemon - pokebolaproxima;

    for(i = 1; i < n; i++){
        tempo = pokemon - pokebolas[i];
        if(abs(tempo) < menorTempo){
            menorTempo = abs(tempo);
            pokebolaproxima = pokebolas[i];
        }
    }

    return pokebolaproxima;
}

int retornarPokemons(int n, int *pokemons, int *pokebolas){
    int i, tempoTotal = 0, tempo, pokebolaproxima;

    for(i = 0; i < n; i++){
        pokebolaproxima = pokebolaProxima(n, pokemons[i], pokebolas);
        tempo = pokebolaproxima - pokemons[i];
        if(abs(tempo) > tempoTotal){
            tempoTotal = abs(tempo);
        }
    }
    return tempoTotal;
}




int main() {
    int n, i, tempo;
    int *pokemon, *pokebola;

    scanf("%d", &n);

    pokemon = (int *)malloc(sizeof(int) * n);
    pokebola = (int *)malloc(sizeof(int) * n);

    for(i = 0; i < n; i++)
        scanf("%d", &pokemon[i]);
    
    for(i = 0; i < n; i++)
        scanf("%d", &pokebola[i]);

    tempo = retornarPokemons(n, pokemon, pokebola);

    printf("%d", tempo);

    free(pokemon);
    free(pokebola);

    return 0;
}