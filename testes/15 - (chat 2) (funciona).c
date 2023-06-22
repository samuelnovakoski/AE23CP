#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


typedef struct Cell Cell;

struct Cell {
    int key;
    int weight;
    Cell *next;
};

typedef struct {
    int V; 
    int A; 
    Cell **adj; 
} GrafoLA;

typedef struct {
    int *parent;
    int *key;
    int *inMST;
} MinHeap;


Cell *newCell(int key, int weight) {
    Cell *cell = (Cell *)malloc(sizeof(Cell));
    cell->key = key;
    cell->weight = weight;
    cell->next = NULL;
    return cell;
}

GrafoLA *criarGrafo(int V, int A) {
    GrafoLA *grafo = (GrafoLA *)malloc(sizeof(GrafoLA));
    grafo->V = V;
    grafo->A = A;
    grafo->adj = (Cell **)malloc(V * sizeof(Cell *));
    int i;
    for (i = 0; i < V; i++) {
        grafo->adj[i] = NULL;
    }
    return grafo;
}

void adicionarAresta(GrafoLA *grafo, int u, int v, int peso) {
    Cell *cell = newCell(v, peso);
    cell->next = grafo->adj[u];
    grafo->adj[u] = cell;

    cell = newCell(u, peso);
    cell->next = grafo->adj[v];
    grafo->adj[v] = cell;
}

int encontrarMenorChave(MinHeap *minHeap, int V) {
    int menorChave = INT_MAX;
    int menorIndice = -1;
    int i;
    for (i = 0; i < V; i++) {
        if (minHeap->inMST[i] == 0 && minHeap->key[i] < menorChave) {
            menorChave = minHeap->key[i];
            menorIndice = i;
        }
    }
    return menorIndice;
}

void imprimirArvoreGeradoraMinima(int *parent, int V) {
    printf("0: -\n");
    int i;
    for (i = 1; i < V; i++) {
        printf("%d: %d\n", i, parent[i]);
    }
}


void prim(GrafoLA *grafo) {
    int V = grafo->V;
    int *parent = (int *)malloc(V * sizeof(int));
    int *key = (int *)malloc(V * sizeof(int));
    int *inMST = (int *)malloc(V * sizeof(int));

    
    int i;
    for (i = 0; i < V; i++) {
        key[i] = INT_MAX;
        inMST[i] = 0;
    }

    MinHeap *minHeap = (MinHeap *)malloc(sizeof(MinHeap));
    minHeap->parent = parent;
    minHeap->key = key;
    minHeap->inMST = inMST;

    key[0] = 0; 
    parent[0] = -1; 

    int count;
    for (count = 0; count < V - 1; count++) {
        int u = encontrarMenorChave(minHeap, V); 
        inMST[u] = 1; 

        
        Cell *cell = grafo->adj[u];
        while (cell != NULL) {
            int v = cell->key;
            int peso = cell->weight;
            if (inMST[v] == 0 && peso < key[v]) {
                parent[v] = u;
                key[v] = peso;
            }
            cell = cell->next;
        }
    }

    imprimirArvoreGeradoraMinima(parent, V);
}


int main() {
    int V, A;
    scanf("%d", &V);
    scanf("%d", &A);

    GrafoLA *grafo = criarGrafo(V, A);

    int i;
    for (i = 0; i < A; i++) {
        int u, v, peso;
        scanf("%d %d %d", &u, &v, &peso);
        adicionarAresta(grafo, u, v, peso);
    }

    prim(grafo);

    return 0;
}
