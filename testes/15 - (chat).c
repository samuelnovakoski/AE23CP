#include <stdio.h>
#include <stdlib.h>
#define INF 999999

typedef struct Cell Cell;
struct Cell{
    int key;
    int weight;
    Cell *next;
};

typedef struct{
    int V; // número de vértices
    int A; // número de arestas
    int *parent; // vetor de pais
    int *visited; // vetor de visitas
    Cell **adj; // lista de adjacências
}GrafoLA;

// Função para alocar um novo nó na lista de adjacências.
Cell* novo_no(int key, int weight){
    Cell *novo = (Cell*) malloc(sizeof(Cell));
    novo->key = key;
    novo->weight = weight;
    novo->next = NULL;
    return novo;
}

// Função para criar um grafo com V vértices e A arestas.
GrafoLA* criar_grafo(int V, int A){
    GrafoLA *grafo = (GrafoLA*) malloc(sizeof(GrafoLA));
    grafo->V = V;
    grafo->A = A;
    grafo->visited = (int*) calloc(V, sizeof(int));
    grafo->parent = (int*) calloc(V, sizeof(int));
    grafo->adj = (Cell**) calloc(V, sizeof(Cell*));
    for(int i = 0; i < V; i++){
        grafo->parent[i] = -1;
        grafo->adj[i] = NULL;
    }
    return grafo;
}

// Função para adicionar uma aresta não-direcionada entre v e w com peso weight no grafo.
void adicionar_aresta(GrafoLA *grafo, int v, int w, int weight){
    Cell *novo1 = novo_no(w, weight);
    Cell *novo2 = novo_no(v, weight);
    novo1->next = grafo->adj[v];
    grafo->adj[v] = novo1;
    novo2->next = grafo->adj[w];
    grafo->adj[w] = novo2;
}

// Função para encontrar o vértice com a menor distância que ainda não foi visitado.
int encontrar_minimo(GrafoLA *grafo){
    int minimo = INF;
    int indice_minimo;
    for(int i = 0; i < grafo->V; i++){
        if(!grafo->visited[i] && minimo > grafo->parent[i]){
            minimo = grafo->parent[i];
            indice_minimo = i;
        }
    }
    return indice_minimo;
}

// Função para executar o algoritmo de Prim no grafo a partir do vértice 0.
void prim(GrafoLA *grafo){
    grafo->parent[0] = -1;
    grafo->parent[1] = INF;
    for(int i = 2; i < grafo->V; i++){
        grafo->parent[i] = INF;
    }
    for(int i = 0; i < grafo->V - 1; i++){
        int u = encontrar_minimo(grafo);
        grafo->visited[u] = 1;
        for(Cell *v = grafo->adj[u]; v != NULL; v = v->next){
            if(!grafo->visited[v->key] && v->weight < grafo->parent[v->key]){
                grafo->parent[v->key] = v->weight;
            }
        }
    }
}

// Função para imprimir a árvore geradora mínima encontrada.
void imprimir_arvore(GrafoLA *grafo){
    printf("0: -\n");
    for(int i = 1; i < grafo->V; i++){
        if(grafo->parent[i] == INF){
            printf("%d: -\n", i);
        }else{
            printf("%d: %d\n", i, grafo->parent[i]);
        }
    }
}

// Função principal.
int main(){
    int V, A, v, w, weight;
    scanf("%d %d", &V, &A);
    GrafoLA *grafo = criar_grafo(V, A);
    for(int i = 0; i < A; i++){
        scanf("%d %d %d", &v, &w, &weight);
        adicionar_aresta(grafo, v, w, weight);
    }
    prim(grafo);
    imprimir_arvore(grafo);
    return 0;
}
