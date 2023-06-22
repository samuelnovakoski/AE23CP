#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
    int pos;
    int cheia;
}Pokebola;

int pokebolaMaisProxima(int n, int pokemon, Pokebola *pokebolas){
    int i, distancia, dist;
    Pokebola aux;

    distancia = pokemon - pokebolas[0].pos;

    for(i = 0; i < n; i++){
        aux = pokebolas[i]
        dist = pokemon - aux.pos;

        if((abs(dist) < abs(distancia)) && (aux.cheia != 0)){
            distancia = dist;
        }
    }

    return aux.pos;
}


int main() {
    int i, n, tempo, item;
    int *pokemons;
    Pokebola *pokebolas;

    scanf("%d", &n);

    pokemons = malloc(n * sizeof(int));
    pokebolas = malloc(n * sizeof(Pokebola));

    for (i = 0; i < n; i++) {
        scanf("%d", &pokemons[i]);
    }

    for(i = 0; i < n; i++){
        scanf("%d", &item);
        pokebolas[i].pos = item;
        pokebolas[i].cheia = 0;
    }

    for(i = 0; i < n; i++){
        tempo = pokebolaMaisProxima(n, pokemons[i], pokebolas);
        printf("%d\n", tempo);
    }

    free(pokemons);
    free(pokebolas);

    return 0;
}