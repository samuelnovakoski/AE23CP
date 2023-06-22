#include <stdio.h>
#include <stdlib.h>

typedef struct Cell Cell;
typedef struct Lista Lista;
typedef struct GrafoLA GrafoLA;

struct Cell {
    int key;
    Cell *next;
};

struct Lista {
    Cell *head;
};

struct GrafoLA {
    int V;      // numero de vertices
    int A;      // numero de arestas
    Lista **adj; // lista de adjacencias
    int *cor;   // vetor de cores
    int *d;     // vetor de tempo de descoberta
    int *f;     // vetor de tempo de finalizacao
    int *pai;   // vetor de pais
    int tempo;  // variavel de controle de tempo
};

Cell* criar_celula(int key) {
    Cell *c = (Cell*)malloc(sizeof(Cell));
    c->key = key;
    c->next = NULL;
    return c;
}

Lista* criar_lista() {
    Lista *l = (Lista*)malloc(sizeof(Lista));
    l->head = NULL;
    return l;
}

GrafoLA* criar_grafoLA(int V) {
    int i;
    GrafoLA *G = (GrafoLA*)malloc(sizeof(GrafoLA));
    G->V = V;
    G->A = 0;
    G->adj = (Lista**)malloc(V * sizeof(Lista*));
    G->cor = (int*)malloc(V * sizeof(int));
    G->d = (int*)malloc(V * sizeof(int));
    G->f = (int*)malloc(V * sizeof(int));
    G->pai = (int*)malloc(V * sizeof(int));
    G->tempo = 0;

    for (i = 0; i < V; i++) {
        G->adj[i] = criar_lista();
        G->cor[i] = 0;
        G->pai[i] = -1;
    }

    return G;
}

void inserir_arestaLA(GrafoLA *G, int v1, int v2) {
    if (v1 >= 0 && v1 < G->V && v2 >= 0 && v2 < G->V) {
        Cell *nova = criar_celula(v2);
        nova->next = G->adj[v1]->head;
        G->adj[v1]->head = nova;
        G->A++;
    }
}

void visitar_vertice(GrafoLA *G, int u) {
    G->cor[u] = 1;
    G->tempo++;
    G->d[u] = G->tempo;

    Cell *v = G->adj[u]->head;
    while (v != NULL) {
        if (G->cor[v->key] == 0) {
            G->pai[v->key] = u;
            visitar_vertice(G, v->key);
        }
        v = v->next;
    }

    G->cor[u] = 2;
    G->tempo++;
    G->f[u] = G->tempo;
}

void busca_profundidade(GrafoLA *G) {
    int u;

    for (u = 0; u < G->V; u++) {
        if (G->cor[u] == 0) {
            visitar_vertice(G, u);
        }
    }
}

void imprimir(GrafoLA *G) {
    int v;

    printf("v d f p\n");
    for (v = 0; v < G->V; v++) {
        printf("%d %d %d ", v, G->d[v], G->f[v]);
        if (G->pai[v] == -1) {
            printf("-\n");
        } else {
            printf("%d\n", G->pai[v]);
        }
    }
}

void liberar_grafoLA(GrafoLA *G) {
    int i;
    for (i = 0; i < G->V; i++) {
        Cell *atual = G->adj[i]->head;
        while (atual != NULL) {
            Cell *tmp = atual;
            atual = atual->next;
            free(tmp);
        }
        free(G->adj[i]);
    }
    free(G->adj);
    free(G->cor);
    free(G->d);
    free(G->f);
    free(G->pai);
    free(G);
}

int main() {
    int V, v, adj;

    scanf("%d", &V);
    GrafoLA *G = criar_grafoLA(V);

    for (v = 0; v < V; v++) {
        scanf("%d", &adj);
        while (adj != -1) {
            inserir_arestaLA(G, v, adj);
            scanf("%d", &adj);
        }
    }

    busca_profundidade(G);
    imprimir(G);

    liberar_grafoLA(G);

    return 0;
}
