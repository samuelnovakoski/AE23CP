#include <stdio.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>

typedef struct Cell Cell;

typedef struct FilaE FilaE;

struct Cell {
    int key;
    Cell* next;
};

struct FilaE {
    Cell* inicio;
    Cell* fim;
};

Cell* criar_celula(int key) {
    Cell* c = (Cell*)malloc(sizeof(Cell));
    c->key = key;
    c->next = NULL;
    return c;
}

FilaE* criar_filaE() {
    FilaE* f = (FilaE*)malloc(sizeof(FilaE));
    f->inicio = NULL;
    f->fim = NULL;
    return f;
}

int filaE_vazia(FilaE* f) {
    return (f == NULL) || (f->inicio == NULL);
}

void enfileirar(int key, FilaE* f) {
    Cell* aux;
    if (f == NULL)
        f = criar_filaE();
    aux = criar_celula(key);
    if (f->inicio == NULL)
        f->inicio = f->fim = aux;
    else {
        f->fim->next = aux;
        f->fim = f->fim->next;
    }
}

int desenfileirar(FilaE* f) {
    Cell* aux;
    int item = INT_MIN;
    if (!filaE_vazia(f)) {
        aux = f->inicio;
        f->inicio = aux->next;
        item = aux->key;
        free(aux);
    }
    return item;
}

void imprimir_fila(FilaE* f) {
    Cell* aux;
    if (!filaE_vazia(f)) {
        aux = f->inicio;
        while (aux != NULL) {
            printf("%d ", aux->key);
            aux = aux->next;
        }
        printf("\n");
    }
}

int liberar_filaE(FilaE* f) {
    if (!filaE_vazia(f)) {
        while (f->inicio != NULL)
            desenfileirar(f);
        free(f);
        return 1;
    }
    return 0;
}

typedef struct Lista Lista;
typedef struct GrafoLA GrafoLA;




struct Lista {
    Cell* head;
};

struct GrafoLA {
    int V; // numero de vertices
    int A; // numero de arestas
    Lista** adj; // lista de adjacencias
};

Lista* criar_lista() {
    Lista* l = (Lista*)malloc(sizeof(Lista));
    l->head = NULL;
    return l;
}



void inserir_elemento(Lista* lista, int key) {
    Cell* novo = criar_celula(key);
    if (lista->head == NULL) {
        lista->head = novo;
    } else {
        Cell* atual = lista->head;
        while (atual->next != NULL) {
            atual = atual->next;
        }
        atual->next = novo;
    }
}

GrafoLA* criar_grafoLA(int V) {
    GrafoLA* grafo = (GrafoLA*)malloc(sizeof(GrafoLA));
    grafo->V = V;
    grafo->A = 0;
    grafo->adj = (Lista**)malloc(V * sizeof(Lista*));
    for (int i = 0; i < V; i++) {
        grafo->adj[i] = criar_lista();
    }
    return grafo;
}

void inserir_aresta(GrafoLA* grafo, int v1, int v2) {
    inserir_elemento(grafo->adj[v1], v2);
    inserir_elemento(grafo->adj[v2], v1);
    grafo->A++;
}

void busca_largura(GrafoLA* G, int s) {
    if (s < 0 || s >= G->V) {
        printf("Vertice raiz invalido.\n");
        return;
    }

    int* pai = (int*)malloc(G->V * sizeof(int));
    int* distancia = (int*)malloc(G->V * sizeof(int));
    int* visitado = (int*)malloc(G->V * sizeof(int));
    for (int v = 0; v < G->V; v++) {
        pai[v] = -1;
        distancia[v] = -1;
        visitado[v] = 0;
    }

    FilaE* fila = criar_filaE();
    enfileirar(s, fila);
    visitado[s] = 1;
    distancia[s] = 0;

    printf("v d p\n");

    while (!filaE_vazia(fila)) {
        int u = desenfileirar(fila);
        

        Cell* atual = G->adj[u]->head;
        while (atual != NULL) {
            int v = atual->key;
            if (visitado[v] == 0) {
                enfileirar(v, fila);
                visitado[v] = 1;
                pai[v] = u;
                distancia[v] = distancia[u] + 1;
            }
            atual = atual->next;
        }

        
    }

    for(int i = 0; i < G->V; i++){
        printf("%d ", i);
        if(distancia[i] > -1)
            printf("%d ", distancia[i]);
        else
            printf("- ");
        if (pai[i] != -1) {
            printf("%d\n", pai[i]);
        } else {
            printf("-\n");
        }
    }

    liberar_filaE(fila);
    free(pai);
    free(distancia);
    free(visitado);
}

void liberar_grafoLA(GrafoLA* G) {
    if (G != NULL) {
        for (int v = 0; v < G->V; v++) {
            free(G->adj[v]);
        }
        free(G->adj);
        free(G);
    }
}

int main() {
    int V;
    scanf("%d", &V);

    GrafoLA* grafo = criar_grafoLA(V);

    for (int i = 0; i < V; i++) {
        int adjacente;
        scanf("%d", &adjacente);
        while (adjacente != -1) {
            inserir_aresta(grafo, i, adjacente);
            scanf("%d", &adjacente);
        }
    }

    int raiz;
    scanf("%d", &raiz);

    busca_largura(grafo, raiz);

    liberar_grafoLA(grafo);

    return 0;
}
