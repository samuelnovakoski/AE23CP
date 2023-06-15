#include <stdio.h>
#include <stdlib.h>

typedef struct Cell Cell;

struct Cell {
    int key;
    Cell *next;
};

typedef struct {
    int V; // numero de vertices
    int A; // numero de arestas
    Cell **adj; // lista de adjacencias
} GrafoLA;

// Funcao para criar uma nova celula na lista de adjacencias
Cell* criarCelula(int v) {
    Cell* nova = (Cell*)malloc(sizeof(Cell));
    nova->key = v;
    nova->next = NULL;
    return nova;
}

// Funcao para adicionar uma aresta entre os vertices v e w
void adicionarAresta(GrafoLA* grafo, int v, int w) {
    Cell* nova = criarCelula(w);
    nova->next = grafo->adj[v];
    grafo->adj[v] = nova;
    grafo->A++;
}

// Funcao para criar um grafo com V vertices
GrafoLA* criarGrafo(int V) {
    GrafoLA* grafo = (GrafoLA*)malloc(sizeof(GrafoLA));
    grafo->V = V;
    grafo->A = 0;
    grafo->adj = (Cell**)malloc(V * sizeof(Cell*));

    int i;
    for (i = 0; i < V; i++) {
        grafo->adj[i] = NULL;
    }

    return grafo;
}

// Funcao para verificar se um grafo e k-regular
int verificarRegularidade(GrafoLA* grafo) {
    int i, k;
    k = -1;

    for (i = 0; i < grafo->V; i++) {
        Cell* atual = grafo->adj[i];
        int count = 0;

        while (atual != NULL) {
            count++;
            atual = atual->next;
        }

        if (k == -1)
            k = count;
        else if (k != count)
            return 0;
    }

    return k;
}

// Funcao para liberar a memoria alocada pelo grafo
void liberarGrafo(GrafoLA* grafo) {
    int i;

    for (i = 0; i < grafo->V; i++) {
        Cell* atual = grafo->adj[i];

        while (atual != NULL) {
            Cell* temp = atual;
            atual = atual->next;
            free(temp);
        }
    }

    free(grafo->adj);
    free(grafo);
}

int main() {
    int V, i, v;
    scanf("%d", &V);

    GrafoLA* grafo = criarGrafo(V);

    for (i = 0; i < V; i++) {
        while (1) {
            scanf("%d", &v);

            if (v == -1)
                break;

            adicionarAresta(grafo, i, v);
        }
    }

    int k = verificarRegularidade(grafo);

    if (k != 0)
        printf("grafo k-regular com k=%d\n", k);
    else
        printf("grafo nao k-regular\n");

    liberarGrafo(grafo);

    return 0;
}
